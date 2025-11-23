#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>

#include "MessageServices/websocket_service.h"
#include "ViewModels/LoginVIewModel.h"
#include "ViewModels/MainViewModel.h"

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


    engine.rootContext()->setContextProperty("mainViewModel", new MainViewModel);
    engine.rootContext()->setContextProperty("loginViewModel", new LoginVIewModel);

    if (false) {
        engine.loadFromModule("ThirdMessageUI", "Main");
    }else {
        engine.loadFromModule("ThirdMessageUI", "LoginWindow");
    }



    auto socketService = WebSocketService::getInstance();
    socketService->initialize(QUrl("ws://localhost:8080"));
    socketService->connectServer();

    qmlRegisterSingletonType<WebSocketService>("ThirdMessageUI.WebSocket", 1, 0, "WebSocketService", [](QQmlEngine *qmlEngine, QJSEngine *jsEngine) -> QObject* {
        return WebSocketService::getInstance();
    });



    return app.exec();
}
