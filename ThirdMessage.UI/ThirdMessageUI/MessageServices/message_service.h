#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include <QObject>

#include "websocket_service.h"

class MessageService : public QObject
{
    Q_OBJECT
public:
    MessageService();
    static MessageService* getInstance();
    Q_INVOKABLE  void sendMessage(const QString &message);
private:
    WebSocketService *webSocket;
};

#endif // MESSAGE_SERVICE_H
