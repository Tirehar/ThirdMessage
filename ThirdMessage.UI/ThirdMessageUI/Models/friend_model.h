#ifndef FRIEND_MODEL_H
#define FRIEND_MODEL_H
#include <QString>

class FriendModel
{
public:
    FriendModel(const QString& uid, const QString& userName);
    QString uid;
    QString userName;
};

#endif // FRIEND_MODEL_H
