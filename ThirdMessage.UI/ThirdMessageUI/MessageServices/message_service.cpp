#include "message_service.h"

#include <QJsonObject>

#include "Helpers/JsonHelper.hpp"

MessageService::MessageService() {
    webSocket = WebSocketService::getInstance();
}

MessageService* MessageService::getInstance() {
    static MessageService instance;
    return &instance;
}

void MessageService::sendMessage(const QString &message) {
    auto content = QJsonObject();
    content.insert("Uid", 12345);
    content.insert("Message", message);
    content.insert("Time", 100000000);
    webSocket->sendMessage(JsonHelper::toJsonString(content));
}
