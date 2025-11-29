#include "message_service.h"
#include <QSettings>
#include "network_service.h"
#include "Helpers/json_helper.hpp"
#include "Models/message_model.h"

MessageService::MessageService() {
    QSettings settings("Tirehar", "ThirdMessage");
    uid = settings.value("UID").toString();
    connectServer();
    webSocket = WebSocketService::getInstance();
    connect(webSocket, &WebSocketService::response, this, &MessageService::messageResponse);
}

MessageService* MessageService::getInstance() {
    static MessageService instance;
    return &instance;
}

void MessageService::sendMessage(const QString &message, const QString& toUid) const{
    auto content = QJsonObject();
    content.insert("Uid", uid);
    content.insert("ToUid", toUid);
    content.insert("Message", message);
    content.insert("Time", QDateTime::currentSecsSinceEpoch());
    webSocket->sendMessage(JsonHelper::toJsonString(content));
}

void MessageService::connectServer() {
    auto socketService = WebSocketService::getInstance();
    QSettings config("config.ini", QSettings::IniFormat);
    socketService->initialize(QUrl(config.value("BridgeAddress").toByteArray()), NetworkService::getInstance()->getCookies());
}

void MessageService::messageResponse(const QString &message) {
    qDebug() << message.toUtf8();
    auto json = QJsonDocument::fromJson(message.toUtf8());
    if (json["Code"].toInt() == 0) {
        auto data = json["Model"];
        auto content = data["Content"].toString();
        auto fromUid = data["FromUid"].toString();
        auto toUid = data["ToUid"].toString();
        auto time = data["Time"].toInt();
        MessageModel model(toUid, !fromUid.compare(uid), content, time);
        emit messageReceived(model);
    }
}
