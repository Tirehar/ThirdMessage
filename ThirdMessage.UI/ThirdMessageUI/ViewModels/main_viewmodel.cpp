//
// Created by Tirehar on 2025/11/23.
//

#include "main_viewmodel.h"

#include <QNetworkReply>
#include <QJsonArray>

#include "MessageServices/network_service.h"


MainViewModel::MainViewModel(QObject *parent) : QObject(parent) {
    friendListModel = new FriendListModel(this);
    messageListModel = new MessageListModel(this);
    loadFriendList();
    messageListModel->push_back(MessageModel(1, false, "Hello World", 11111));
    messageListModel->push_back(MessageModel(1, true, "Hello World", 11112));
}

FriendListModel* MainViewModel::getFriendListModel() const{
    return friendListModel;
}

MessageListModel* MainViewModel::getMessageListModel() const {
    return messageListModel;
}

void MainViewModel::loadFriendList() {
    qDebug()<<"Load FriendListItem";
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Friend/GetFriends?uid=4fa0850b-cf18-4e3d-bd5a-47330900d621");
    connect(reply, &QNetworkReply::finished,[reply, this] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        qDebug()<<"FriendListItem"<<jsonDoc["model"]["friends"].toArray().count();
        for (auto friendModel: jsonDoc["model"]["friends"].toArray()) {
            QJsonObject obj = friendModel.toObject();
            qDebug()<<obj["userName"].toString();
            friendListModel->push_back(FriendModel("null", obj["userName"].toString()));
        }
    });
}
