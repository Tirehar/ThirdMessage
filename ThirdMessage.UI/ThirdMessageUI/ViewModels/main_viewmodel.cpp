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
            qDebug()<<"Get"<<obj["userName"].toString();
            friendListModel->push_back(FriendModel(obj["uid"].toString(), obj["userName"].toString()));
        }
    });
}

void MainViewModel::friendAdd(const QString &uid) {
    auto reply = NetworkService::getInstance()->sendPostRequest("https://localhost:7034/api/Friend/FriendRequest?otheruid=" + uid);
    connect(reply, &QNetworkReply::finished,[reply, this] {
        qDebug()<<"Error:"<<reply->error();
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        if (jsonDoc["code"].toInt() == 0) {
            messageListModel->clear();
            loadFriendList();
        }
    });
}

void MainViewModel::loadMessageList(QString otherUid) {
    messageListModel->clear();
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Message/GetMessage?otheruid=" + otherUid);
    connect(reply, &QNetworkReply::finished,[reply, this, otherUid] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        qDebug()<<"Code is"<<jsonDoc["message"].toString();
        for (auto messageModel: jsonDoc["model"].toArray()) {
            qDebug()<<"Get";
            auto message = messageModel.toObject();
            messageListModel->push_back(MessageModel(otherUid, message["fromUid"].toString() == uid,  message["content"].toString(), message["time"].toInt()));
        }
    });
}
