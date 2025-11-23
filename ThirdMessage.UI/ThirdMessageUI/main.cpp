#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "MessageServices/websocket_service.h"

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

    auto socketService = WebSocketService::getInstance();
    socketService->initialize(QUrl("ws://localhost:8080"));
    socketService->connectServer();

    qmlRegisterSingletonType<WebSocketService>("ThirdMessageUI.WebSocket", 1, 0, "WebSocketService", [](QQmlEngine *qmlEngine, QJSEngine *jsEngine) -> QObject* {
        return WebSocketService::getInstance();
    });

    engine.loadFromModule("ThirdMessageUI", "LoginWindow");

    return app.exec();
}
