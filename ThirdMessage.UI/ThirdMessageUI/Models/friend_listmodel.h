#ifndef FRIEND_LISTMODEL_H
#define FRIEND_LISTMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>

#include "friend_model.h"

class FriendListModel : public QAbstractListModel{
    Q_OBJECT
public:
    explicit FriendListModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void push_back(const FriendModel& model);
    void remove(const QString& uid);
private:
    QList<FriendModel> datas;
};

#endif // FRIEND_LISTMODEL_H
