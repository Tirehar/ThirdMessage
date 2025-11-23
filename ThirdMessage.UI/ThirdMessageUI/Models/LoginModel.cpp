//
// Created by Tirehar on 2025/11/23.
//
#include "LoginModel.h"


LoginModel::LoginModel(const QString &account, const QString &password) {
    this->account = account;
    this->password = password;
}

QString LoginModel::getAccount() const
{
    return account;
}

void LoginModel::setAccount(const QString &newAccount)
{
    if (account == newAccount)
        return;
    account = newAccount;
    emit accountChanged();
}

QString LoginModel::getPassword() const
{
    return password;
}

void LoginModel::setPassword(const QString &newPassword)
{
    if (password == newPassword)
        return;
    password = newPassword;
    emit passwordChanged();
}

