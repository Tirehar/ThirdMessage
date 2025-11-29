#ifndef THIRDMESSAGEUI_MAINVIEWMODEL_H
#define THIRDMESSAGEUI_MAINVIEWMODEL_H

#include "Models/friend_listmodel.h"
#include "Models/message_listmodel.h"
#include <QStringListModel>

#include "MessageServices/message_service.h"


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
    Q_INVOKABLE void friendAdd(const QString& uid);
    Q_INVOKABLE void sendMessage(const QString& text, const QString& toUid);
public slots:
    void loadMessageList(const QString& otherUid);
    void loadFriendSearchList(const QString& searchText);
    void loadFriendList();
signals:
    void friendListModelChanged();
    void messageListModelChanged();
    void friendSearchListModelChanged();
private:
    QMap<QString, MessageListModel*> messageListModels;
    Q_INVOKABLE void setMessageListModel(const QString& friendUid);
    FriendListModel* friendListModel;
    QStringListModel* friendSearchListModel;
    MessageListModel* messageListModel;
    const MessageService* messageService;
    QString uid;
    void messageResponse(const MessageModel& model);
};


#endif //THIRDMESSAGEUI_MAINVIEWMODEL_H
