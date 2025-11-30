#include <qqmlcontext.h>
#include <QSettings>

#include "Helpers/frameless_helper.h"
#include "MessageServices/message_service.h"
#include "MessageServices/network_service.h"
#include "MessageServices/websocket_service.h"
#include "ViewModels/login_viewmodel.h"
#include "ViewModels/main_viewmodel.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    app.setWindowIcon(QIcon(":/AppLogo.png"));

    qmlRegisterType<FramelessHelper>("ThirdMessageUI.Helpers", 1, 0, "FramelessHelper");
    qmlRegisterType<MainViewModel>("ThirdMessageUI.ViewModels", 1, 0, "MainViewModel");
    qmlRegisterType<LoginVIewModel>("ThirdMessageUI.ViewModels", 1, 0, "LoginViewModel");

    QSettings settings("Tirehar", "ThirdMessage");
    settings.clear();
    if (settings.contains("UID")) {
        auto cookieData = settings.value("Cookie").toByteArray();
        auto cookies = QNetworkCookie::parseCookies(cookieData);
        NetworkService::getInstance()->setCookie(cookies);
        engine.loadFromModule("ThirdMessageUI", "Main");
    }else {
        engine.loadFromModule("ThirdMessageUI", "LoginWindow");
    }

    qmlRegisterSingletonType<WebSocketService>("ThirdMessageUI.WebSocket", 1, 0, "WebSocketService", [](QQmlEngine *qmlEngine, QJSEngine *jsEngine) -> QObject* {
        return WebSocketService::getInstance();
    });
    qmlRegisterSingletonType<WebSocketService>("ThirdMessageUI.Message", 1, 0, "MessageService", [](QQmlEngine *qmlEngine, QJSEngine *jsEngine) -> QObject* {
        return MessageService::getInstance();
    });

    return app.exec();
}
