//
// Created by Tirehar on 2025/11/23.
//

#include "main_viewmodel.h"

#include <QNetworkReply>
#include <QJsonArray>
#include <QSettings>

#include "MessageServices/network_service.h"

MainViewModel::MainViewModel(QObject *parent) : QObject(parent) {
    friendListModel = new FriendListModel(this);
    messageListModel = new MessageListModel(this);
    QSettings settings("Tirehar", "ThirdMessage");
    uid = settings.value("UID").toString();
    loadFriendList();
    messageListModel->push_back(MessageModel(1, false, "Hello World", 11111));
    messageListModel->push_back(MessageModel(1, true, "Hello World", 11112));
}

MainViewModel::~MainViewModel() {
    deleteLater();
    delete friendListModel;
    delete messageListModel;
}

FriendListModel* MainViewModel::getFriendListModel() const{
    return friendListModel;
}

MessageListModel* MainViewModel::getMessageListModel() const {
    return messageListModel;
}

void MainViewModel::loadFriendList() {
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Friend/GetFriends");
    connect(reply, &QNetworkReply::finished,[reply, this] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        for (auto friendModel: jsonDoc["model"]["friends"].toArray()) {
            QJsonObject obj = friendModel.toObject();
            friendListModel->push_back(FriendModel("null", obj["userName"].toString()));
        }
    });
}
