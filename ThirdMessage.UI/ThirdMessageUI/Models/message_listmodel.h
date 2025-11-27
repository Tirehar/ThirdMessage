#ifndef MESSAGE_LISTMODEL_H
#define MESSAGE_LISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

#include "message_model.h"

class MessageListModel : public QAbstractListModel{
    Q_OBJECT
public:
    explicit MessageListModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void push_back(const MessageModel& data);
    void clear();
private:
    QList<MessageModel> datas;
};

#endif // MESSAGE_LISTMODEL_H
