#include "websocket_service.h"

WebSocketService* WebSocketService::getInstance() {
    static WebSocketService instance;
    return &instance;
}

WebSocketService::WebSocketService() = default;

void WebSocketService::initialize(const QUrl& url, const QList<QNetworkCookie>& cookies) {
    socket = QSharedPointer<QWebSocket>(new QWebSocket());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    connectServer(request);
    connect(socket.get(), &QWebSocket::connected, this, &WebSocketService::onConnected);
    connect(socket.get(), &QWebSocket::textMessageReceived, this, &WebSocketService::onMessageReceived);
    connect(socket.get(), &QWebSocket::errorOccurred, this, &WebSocketService::onError);
    qDebug()<<"initialize";
}

void WebSocketService::connectServer(const QNetworkRequest& request) {
    socket->open(request);
    qDebug()<<"open";
}

Q_INVOKABLE void WebSocketService::sendMessage(const QString &message) {
    socket->sendTextMessage(message);
}

void WebSocketService::onMessageReceived(const QString &message) {
    emit response(message);
    qDebug()<<"Received";
}


void WebSocketService::onConnected() {
    qDebug()<<"Connected";
}

void WebSocketService::onError(QAbstractSocket::SocketError error) {
    qDebug()<<"Error:"<<error;
}
