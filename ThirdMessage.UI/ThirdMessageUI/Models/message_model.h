#ifndef MESSAGE_MODEL_H
#define MESSAGE_MODEL_H
#include <QString>

class MessageModel
{
public:
    MessageModel(QString otherId, bool isMy, QString content, int time);
    QString otherId;
    bool isMy;
    QString content;
    int time;
};

#endif // MESSAGE_MODEL_H
