#ifndef WEBSOCKET_SERVICE_H
#define WEBSOCKET_SERVICE_H

#include <QObject>
#include <QWebSocket>

class WebSocketService : public QObject
{
    Q_OBJECT
public:
    static WebSocketService* getInstance();
    void initialize(const QUrl& url);
    void connectServer();
    Q_INVOKABLE void sendMessage(const QString& message);

    signals:
        Q_SIGNAL void response(const QString& response);
private:
    QUrl server_url;
    QSharedPointer<QWebSocket> socket;
    WebSocketService();
    void onConnected();
    void onMessageReceived(const QString &message);
    void onError(QAbstractSocket::SocketError error);
};

#endif // WEBSOCKET_SERVICE_H
