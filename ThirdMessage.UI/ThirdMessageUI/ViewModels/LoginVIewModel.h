//
// Created by Tirehar on 2025/11/23.
//

#ifndef THIRDMESSAGEUI_LOGINVIEWMODEL_H
#define THIRDMESSAGEUI_LOGINVIEWMODEL_H
#include <QObject>


class LoginVIewModel : public QObject{
    Q_OBJECT
public:
    Q_INVOKABLE void login(const QString& account,const QString& password);
    signals:
        Q_SIGNAL void loginResponse(bool successful);
};


#endif //THIRDMESSAGEUI_LOGINVIEWMODEL_H