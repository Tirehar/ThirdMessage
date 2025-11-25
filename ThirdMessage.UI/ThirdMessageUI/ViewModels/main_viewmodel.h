//
// Created by Tirehar on 2025/11/23.
//

#ifndef THIRDMESSAGEUI_MAINVIEWMODEL_H
#define THIRDMESSAGEUI_MAINVIEWMODEL_H
#include <QObject>

#include "Models/friend_listmodel.h"


class MainViewModel : public QObject{
    Q_OBJECT
    Q_PROPERTY(FriendListModel* friendListModel READ getFriendListModel NOTIFY friendListModelChanged FINAL)

public:
    explicit MainViewModel(QObject *parent = nullptr);
    FriendListModel* getFriendListModel() const;
    Q_INVOKABLE void loadFriendList();

signals:
    void friendListModelChanged();

private:
    FriendListModel* friendListModel;

};


#endif //THIRDMESSAGEUI_MAINVIEWMODEL_H
