#include "frameless_helper.h"

#include <QOperatingSystemVersion>

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#endif

FramelessHelper::FramelessHelper(QQuickItem *parent) : QQuickItem(parent)
{
}

FramelessHelper::~FramelessHelper()
{
    QCoreApplication::instance()->removeNativeEventFilter(this);
}

void FramelessHelper::componentComplete()
{
    QQuickItem::componentComplete();
    m_window = window();
    if (m_window) {
        connect(m_window, &QWindow::visibleChanged, this, [this] {
            auto hwnd = reinterpret_cast<HWND>(m_window->winId());
            if (m_window->isVisible() && hwnd) {
                QCoreApplication::instance()->installNativeEventFilter(this);
                updateWindowStyle();
            }
        });

        connect(m_window, &QWindow::windowStateChanged, this, [this]() {
            HWND hwnd = reinterpret_cast<HWND>(m_window->winId());
            if (!hwnd) return;
            // 在最大化/还原时补一下样式和阴影
            updateWindowStyle();
        });
    }
}

void FramelessHelper::updateWindowStyle()
{
#ifdef Q_OS_WIN
    if (!m_window) return;

    HWND hwnd = reinterpret_cast<HWND>(m_window->winId());

    // 1. 扩展 Frame 到 Client 区域，实现阴影和圆角
    const MARGINS shadow = {1, 1, 1, 1};
    DwmExtendFrameIntoClientArea(hwnd, &shadow);

    // 2. 恢复 WS_THICKFRAME 和 WS_CAPTION
    // Qt 设置 FramelessWindowHint 后会移除这些样式，导致动画丢失。
    // 我们需要手动加回来，但之后通过 WM_NCCALCSIZE 隐藏视觉上的标题栏。
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style |= WS_OVERLAPPEDWINDOW;
    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    // 触发一次刷新，确保样式应用
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
#endif
}

bool FramelessHelper::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
#ifdef Q_OS_WIN
    if (eventType != "windows_generic_MSG")
        return false;

    MSG *msg = static_cast<MSG *>(message);
    HWND hwnd = msg->hwnd;

    if (!m_window || reinterpret_cast<HWND>(m_window->winId()) != hwnd)
        return false;

    switch (msg->message) {
        case WM_NCCALCSIZE: {
            // 拦截计算非客户区大小的消息
            // 如果返回 0 (且 wParam 为 TRUE)，表示整个窗口都是客户区
            // 这样就去掉了系统自带的标题栏，但保留了上面的 Style 带来的动画特性
            if (msg->wParam == TRUE) {
                // 处理最大化时的显示器边界溢出问题
                NCCALCSIZE_PARAMS* params = reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);
                if (IsZoomed(hwnd)) {
                     // 最大化时，Windows 会把窗口边框算到屏幕外，我们需要把这些边距减回来
                     // 否则最大化时内容会被屏幕边缘裁切
                     auto monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
                     MONITORINFO monitorInfo{};
                     monitorInfo.cbSize = sizeof(MONITORINFO);
                     GetMonitorInfoW(monitor, &monitorInfo);

                     params->rgrc[0] = monitorInfo.rcWork;
                     params->rgrc[0].top -= 1; // 稍微调整以避免缝隙，视情况而定
                }
                *result = 0;
                return true;
            }
            break;
        }
        case WM_NCHITTEST: {
            if (canResize) {
                // 处理鼠标点击位置，实现拖拽和缩放
                // 获取鼠标位置
                long x = GET_X_LPARAM(msg->lParam);
                long y = GET_Y_LPARAM(msg->lParam);

                // 转换为窗口坐标
                POINT nativeLocalPos{x, y};
                ScreenToClient(hwnd, &nativeLocalPos);

                // 1. 检测是否在边缘（用于缩放）
                RECT clientRect;
                GetClientRect(hwnd, &clientRect);
                long width = clientRect.right;
                long height = clientRect.bottom;

                bool left = nativeLocalPos.x < m_resizeBorderWidth;
                bool right = nativeLocalPos.x >= width - m_resizeBorderWidth;
                bool top = nativeLocalPos.y < m_resizeBorderWidth;
                bool bottom = nativeLocalPos.y >= height - m_resizeBorderWidth;

                if (top && left) { *result = HTTOPLEFT; return true; }
                if (top && right) { *result = HTTOPRIGHT; return true; }
                if (bottom && left) { *result = HTBOTTOMLEFT; return true; }
                if (bottom && right) { *result = HTBOTTOMRIGHT; return true; }
                if (left) { *result = HTLEFT; return true; }
                if (right) { *result = HTRIGHT; return true; }
                if (top) { *result = HTTOP; return true; }
                if (bottom) { *result = HTBOTTOM; return true; }

                // 否则作为普通客户区内容
                *result = HTCLIENT;
                return true;
            }
        }
    }
#endif
    return false;
}

void FramelessHelper::showMaximized() {
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(m_window->winId());
    ::ShowWindow(hwnd, SW_MAXIMIZE);
#else
    window()->setVisibility(QQuickWindow::Maximized);
#endif
}

void FramelessHelper::showMinimized() {
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(m_window->winId());
    ::ShowWindow(hwnd, SW_MINIMIZE);
#else
    window()->setVisibility(QQuickWindow::Minimized);
#endif
}


void FramelessHelper::showNormal() {
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(m_window->winId());
    ::ShowWindow(hwnd, SW_RESTORE);
#else
    window()->setVisibility(QQuickWindow::Normal);
#endif
}

// static bool isMaximized(const HWND hwnd) {
//     WINDOWPLACEMENT wp;
//     ::GetWindowPlacement(hwnd, &wp);
//     return wp.showCmd == SW_MAXIMIZE;
// }

void FramelessHelper::setCanResize(bool canResize) {
    this->canResize = canResize;
}

bool FramelessHelper::getCanResize() const {
    return canResize;
}

void FramelessHelper::onWindowClosing() {
    QCoreApplication::instance()->removeNativeEventFilter(this);
}
