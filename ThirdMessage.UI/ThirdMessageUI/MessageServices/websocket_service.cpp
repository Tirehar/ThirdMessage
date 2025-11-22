#include "websocket_service.h"

WebSocketService* WebSocketService::getInstance() {
    static WebSocketService instance;
    return &instance;
}

WebSocketService::WebSocketService() = default;

void WebSocketService::initialize(const QUrl& url) {
    server_url = url;
    socket = QSharedPointer<QWebSocket>(new QWebSocket());
    connect(socket.get(), &QWebSocket::connected, this, &WebSocketService::onConnected);
    connect(socket.get(), &QWebSocket::textMessageReceived, this, &WebSocketService::onMessageReceived);
    connect(socket.get(), &QWebSocket::errorOccurred, this, &WebSocketService::onError);
    qDebug()<<"initialize";
}

void WebSocketService::connectServer() {
    socket->open(server_url);
    qDebug()<<"open";
}

Q_INVOKABLE void WebSocketService::sendMessage(const QString &message) {
    socket->sendTextMessage(message);
}

void WebSocketService::onMessageReceived(const QString &message) {
    response(message);
    qDebug()<<"Received:"<<message;
}


void WebSocketService::onConnected() {
    qDebug()<<"Connected";
}

void WebSocketService::onError(QAbstractSocket::SocketError error) {
    qDebug()<<"Error:"<<error;
}
