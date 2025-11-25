//
// Created by Tirehar on 2025/11/23.
//

#ifndef THIRDMESSAGEUI_LOGINMODEL_H
#define THIRDMESSAGEUI_LOGINMODEL_H
#include <QObject>


class LoginModel : public QObject {
    Q_OBJECT

public:
    LoginModel(const QString& account, const QString& password);

    QString getAccount() const;
    void setAccount(const QString &newAccount);

    QString getPassword() const;
    void setPassword(const QString &newPassword);

signals:
    void accountChanged();

    void passwordChanged();

private:
    QString account;
    QString password;
    Q_PROPERTY(QString account READ getAccount WRITE setAccount NOTIFY accountChanged FINAL)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged FINAL)
};


#endif //THIRDMESSAGEUI_LOGINMODEL_H
