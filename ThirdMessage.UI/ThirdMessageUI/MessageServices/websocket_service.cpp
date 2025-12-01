#include "websocket_service.h"

WebSocketService* WebSocketService::getInstance() {
    static WebSocketService instance;
    return &instance;
}

WebSocketService::WebSocketService() = default;

void WebSocketService::initialize(const QUrl& url, const QList<QNetworkCookie>& cookies) {
    socket = QSharedPointer<QWebSocket>(new QWebSocket());
    connectServer(url, cookies);
    connect(socket.get(), &QWebSocket::connected, this, &WebSocketService::onConnected);
    connect(socket.get(), &QWebSocket::textMessageReceived, this, &WebSocketService::onMessageReceived);
    connect(socket.get(), &QWebSocket::errorOccurred, this, &WebSocketService::onError);
    qDebug()<<"initialize";
}

void WebSocketService::connectServer(const QUrl& url, const QList<QNetworkCookie>& cookies) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    socket->open(request);
    qDebug()<<"open";
}

void WebSocketService::disconnectServer() {
    socket->close();
    qDebug()<<"close";
}

bool WebSocketService::getConnected() {
    return isConnected;
}

Q_INVOKABLE void WebSocketService::sendMessage(const QString &message) {
    socket->sendTextMessage(message);
}

void WebSocketService::onMessageReceived(const QString &message) {
    qDebug()<<"Received";
    emit response(message);
    qDebug()<<"Received";
}


void WebSocketService::onConnected() {
    isConnected = true;
    qDebug()<<"Connected";
}

void WebSocketService::onError(QAbstractSocket::SocketError error) {
    qDebug()<<"Error:"<<error;
}
