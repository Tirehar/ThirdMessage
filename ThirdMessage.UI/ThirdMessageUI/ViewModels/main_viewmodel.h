#ifndef THIRDMESSAGEUI_MAINVIEWMODEL_H
#define THIRDMESSAGEUI_MAINVIEWMODEL_H

#include "Models/friend_listmodel.h"
#include "Models/message_listmodel.h"


class MainViewModel : public QObject{
    Q_OBJECT
    Q_PROPERTY(FriendListModel* friendListModel READ getFriendListModel NOTIFY friendListModelChanged FINAL)
    Q_PROPERTY(MessageListModel* messageListModel READ getMessageListModel NOTIFY messageListModelChanged FINAL)

public:
    explicit MainViewModel(QObject *parent = nullptr);
    FriendListModel* getFriendListModel() const;
    MessageListModel* getMessageListModel() const;
    Q_INVOKABLE void loadFriendList();

signals:
    void friendListModelChanged();
    void messageListModelChanged();

private:
    FriendListModel* friendListModel;
    MessageListModel* messageListModel;
};


#endif //THIRDMESSAGEUI_MAINVIEWMODEL_H
