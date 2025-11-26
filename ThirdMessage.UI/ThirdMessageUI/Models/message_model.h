#ifndef MESSAGE_MODEL_H
#define MESSAGE_MODEL_H
#include <QString>

class MessageModel
{
public:
    MessageModel(int otherId, bool isMy, QString content, int time);
    int otherId;
    bool isMy;
    QString content;
    int time;
};

#endif // MESSAGE_MODEL_H
