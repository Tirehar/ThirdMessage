//
// Created by Tirehar on 2025/11/23.
//

#include "main_viewmodel.h"

#include <QNetworkReply>
#include <QJsonArray>

#include "MessageServices/network_service.h"


MainViewModel::MainViewModel(QObject *parent) : QObject(parent) {
    friendListModel = new FriendListModel(this);
    loadFriendList();
}

FriendListModel* MainViewModel::getFriendListModel() const{
    return friendListModel;
}

void MainViewModel::loadFriendList() {
    qDebug()<<"Load FriendListItem";
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Friend/GetFriends?uid=3");
    connect(reply, &QNetworkReply::finished,[reply, this] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        qDebug()<<"FriendListItem"<<jsonDoc["model"]["friends"].toArray().count();
        for (auto friendModel: jsonDoc["model"]["friends"].toArray()) {
            QJsonObject obj = friendModel.toObject();
            qDebug()<<obj["uid"].toInt()<<obj["userName"].toString();
            friendListModel->push_back(FriendModel(obj["uid"].toInt(), obj["userName"].toString()));
        }
    });
}
