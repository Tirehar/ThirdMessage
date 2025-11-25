//
// Created by Tirehar on 2025/11/23.
//

#include "main_viewmodel.h"


MainViewModel::MainViewModel(QObject *parent) : QObject(parent) {
    friendListModel = new FriendListModel(this);
    friendListModel->push_back(FriendModel(001, "Tirehar1"));
    friendListModel->push_back(FriendModel(002, "Tirehar2"));
    friendListModel->push_back(FriendModel(003, "Tirehar3"));
}

FriendListModel* MainViewModel::getFriendListModel() const{
    return friendListModel;
}
