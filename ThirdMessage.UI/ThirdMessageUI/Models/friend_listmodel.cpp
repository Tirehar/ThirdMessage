#include "friend_listmodel.h"

enum FriendRoles {
    UserNameRole = Qt::UserRole + 1,
    UIDRole,
};

FriendListModel::FriendListModel(QObject* parent) : QAbstractListModel(parent) {
}

int FriendListModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : datas.size();
}

QHash<int, QByteArray> FriendListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[UIDRole] = "uid";
    roles[UserNameRole] = "userName";
    return roles;
}

QVariant FriendListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (role == UIDRole)
        return datas.at(index.row()).uid;
    if (role == UserNameRole)
        return datas.at(index.row()).userName;
    return QVariant();
}

void FriendListModel::push_back(const FriendModel &model) {
    const int row = datas.count();
    beginInsertRows(QModelIndex(), row, row);
    datas.push_back(model);
    endInsertRows();
}

void FriendListModel::remove(const QString& uid) {
    datas.removeIf([uid](const FriendModel& model){
        return model.uid == uid;
    });
}

void FriendListModel::clear() {
    const int row = datas.count();
    beginRemoveRows(QModelIndex(), 0, row - 1);
    datas.clear();
    endRemoveRows();
}

void FriendListModel::Refresh(const QList<FriendModel> & models) {
    datas.clear();
    beginInsertRows(QModelIndex(), 0, 0);
    datas = models;
    endInsertRows();
}
