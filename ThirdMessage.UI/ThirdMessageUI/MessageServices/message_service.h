#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "websocket_service.h"
#include "Models/message_model.h"

class MessageService : public QObject
{
    Q_OBJECT
public:
    MessageService();
    static MessageService* getInstance();
    void sendMessage(const QString &message, const QString& toUid) const;
    void connectServer();
    signals:
    Q_SIGNAL void messageReceived(const MessageModel &messageModel);
private:
    WebSocketService *webSocket;
    QString uid;
    void messageResponse(const QString &message);
};

#endif // MESSAGE_SERVICE_H
