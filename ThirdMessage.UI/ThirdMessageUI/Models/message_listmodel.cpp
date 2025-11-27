#include "message_listmodel.h"

enum MessageRoles {
    otherIdRole = Qt::UserRole + 1,
    isMy,
    contentRole,
    timeRole
};

MessageListModel::MessageListModel(QObject* parent) : QAbstractListModel(parent) {}

QHash<int, QByteArray> MessageListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[otherIdRole] = "otherId";
    roles[isMy] = "isMy";
    roles[contentRole] = "content";
    roles[timeRole] = "time";
    return roles;
}

int MessageListModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : datas.size();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == otherIdRole)
        return datas.at(index.row()).otherId;
    if (role == isMy)
        return datas.at(index.row()).isMy;
    if (role == contentRole)
        return datas.at(index.row()).content;
    if (role == timeRole)
        return datas.at(index.row()).time;
    return QVariant();
}

void MessageListModel::push_back(const MessageModel &data) {
    const int row = datas.count();
    beginInsertRows(QModelIndex(), row, row);
    datas.push_back(data);
    endInsertRows();
}

void MessageListModel::clear() {
    const int row = datas.count();
    beginRemoveRows(QModelIndex(), 0, row - 1);
    datas.clear();
    endRemoveRows();
}


