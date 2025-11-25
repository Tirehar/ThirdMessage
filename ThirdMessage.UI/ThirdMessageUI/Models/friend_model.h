#ifndef FRIEND_MODEL_H
#define FRIEND_MODEL_H
#include <QString>

class FriendModel
{
public:
    FriendModel(int uid, const QString& userName);
    int uid;
    QString userName;
};

#endif // FRIEND_MODEL_H
