#ifndef THIRDMESSAGEUI_MAINVIEWMODEL_H
#define THIRDMESSAGEUI_MAINVIEWMODEL_H

#include "Models/friend_listmodel.h"
#include "Models/message_listmodel.h"
#include <QStringListModel>


class MainViewModel : public QObject{
    Q_OBJECT
    Q_PROPERTY(FriendListModel* friendListModel READ getFriendListModel NOTIFY friendListModelChanged FINAL)
    Q_PROPERTY(MessageListModel* messageListModel READ getMessageListModel NOTIFY messageListModelChanged FINAL)
    Q_PROPERTY(QStringListModel* friendSearchListModel READ getFriendSearchListModel NOTIFY friendSearchListModelChanged FINAL)
public:
    explicit MainViewModel(QObject *parent = nullptr);
    ~MainViewModel() override;
    FriendListModel* getFriendListModel() const;
    QStringListModel* getFriendSearchListModel() const;
    MessageListModel* getMessageListModel() const;
    Q_INVOKABLE void loadFriendList();
    Q_INVOKABLE void friendAdd(const QString& uid);
public slots:
    void loadMessageList(const QString& otherUid);
    void loadFriendSearchList(const QString& searchText);
signals:
    void friendListModelChanged();
    void messageListModelChanged();
    void friendSearchListModelChanged();
private:
    FriendListModel* friendListModel;
    QStringListModel* friendSearchListModel;
    MessageListModel* messageListModel;
    QString uid;
};


#endif //THIRDMESSAGEUI_MAINVIEWMODEL_H
