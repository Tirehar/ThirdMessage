#ifndef WEBSOCKET_SERVICE_H
#define WEBSOCKET_SERVICE_H

#include <QNetworkCookie>
#include <QWebSocket>

class WebSocketService : public QObject
{
    Q_OBJECT
public:
    static WebSocketService* getInstance();
    void initialize(const QUrl& url, const QList<QNetworkCookie>& cookies);
    void connectServer(const QUrl& url, const QList<QNetworkCookie>& cookies);
    void disconnectServer();
    bool getConnected();
    Q_INVOKABLE void sendMessage(const QString& message);

    signals:
        Q_SIGNAL void response(const QString& response);
private:
    QSharedPointer<QWebSocket> socket;
    bool isConnected = false;
    WebSocketService();
    void onConnected();
    void onMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);
};

#endif // WEBSOCKET_SERVICE_H
