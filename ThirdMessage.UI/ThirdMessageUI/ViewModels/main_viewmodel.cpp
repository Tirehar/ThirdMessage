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
    friendSearchListModel = new QStringListModel(this);
    messageListModel = new MessageListModel(this);
    messageService = MessageService::getInstance();
    connect(messageService, &MessageService::messageReceived, this, &MainViewModel::messageResponse);
    QSettings settings("Tirehar", "ThirdMessage");
    uid = settings.value("UID").toString();
    loadFriendList();
}

MainViewModel::~MainViewModel() {
    if (messageService) {
        disconnect(messageService, &MessageService::messageReceived, this, &MainViewModel::messageResponse);
    }
}

FriendListModel* MainViewModel::getFriendListModel() const{
    return friendListModel;
}

QStringListModel * MainViewModel::getFriendSearchListModel() const {
    return friendSearchListModel;
}

MessageListModel* MainViewModel::getMessageListModel() const {
    return messageListModel;
}

void MainViewModel::loadFriendList() {
    friendListModel->clear();
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

void MainViewModel::friendAdd(const QString &userName) {
    auto reply = NetworkService::getInstance()->sendPostRequest("https://localhost:7034/api/Friend/FriendRequest?userName=" + userName);
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

void MainViewModel::sendMessage(const QString& text, const QString& toUid){
    messageService->sendMessage(text, toUid);
}
void MainViewModel::messageResponse(const MessageModel &model) {
    messageListModel->push_back(model);
}

void MainViewModel::loadMessageList(const QString& otherUid) {
    setMessageListModel(otherUid);
    messageListModel->clear();
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Message/GetMessage?otheruid=" + otherUid);
    connect(reply, &QNetworkReply::finished,[reply, this, otherUid] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        for (auto messageModel: jsonDoc["model"].toArray()) {
            auto message = messageModel.toObject();
            messageListModel->push_back(MessageModel(otherUid, message["fromUid"].toString() == uid,  message["content"].toString(), message["time"].toInt()));
        }
    });
}

void MainViewModel::loadFriendSearchList(const QString &searchText) {
    auto reply = NetworkService::getInstance()->sendGetRequest("https://localhost:7034/api/Friend/SearchFriends?keyword=" + searchText);
    connect(reply, &QNetworkReply::finished,[reply, this] {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        QStringList list;
        for (auto friendModel: jsonDoc["model"].toArray()) {
            list.push_back(friendModel.toString());
        }
        friendSearchListModel->setStringList(list);
    });
}

void MainViewModel::setMessageListModel(const QString &friendUid) {
    qDebug()<<"Get"<<friendUid;
    if (!messageListModels.contains(friendUid)) {
        qDebug()<<"Create MessageModel";
        messageListModels[friendUid] = new MessageListModel(this);
    }
    if (messageListModel != messageListModels[friendUid]) {
        messageListModel = messageListModels[friendUid];
        emit messageListModelChanged();
    }
}


