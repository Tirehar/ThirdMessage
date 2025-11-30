#ifndef FRAMELESS_HELPER_H
#define FRAMELESS_HELPER_H
#include <QQuickItem>
#include <QAbstractNativeEventFilter>
#include <QQuickWindow>

class FramelessHelper : public QQuickItem, public QAbstractNativeEventFilter
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool canResize READ getCanResize WRITE setCanResize NOTIFY canResizeChanged FINAL)
public:
    explicit FramelessHelper(QQuickItem *parent = nullptr);
    ~FramelessHelper() override;

    void componentComplete() override; // QML加载完成后调用
    // 必须实现的事件过滤器接口
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
    void setCanResize(bool canResize);
    bool getCanResize() const;
    Q_INVOKABLE void showMaximized();
    Q_INVOKABLE void showNormal();
    Q_INVOKABLE void showMinimized();
public slots:
    void onWindowClosing();
signals:
    void canResizeChanged();

private:
    int m_resizeBorderWidth = 6; // 边缘调整大小的检测宽度
    bool canResize = true;
    QWindow *m_window = nullptr;

    // 辅助函数
    void updateWindowStyle();
};

#endif // FRAMELESS_HELPER_H
