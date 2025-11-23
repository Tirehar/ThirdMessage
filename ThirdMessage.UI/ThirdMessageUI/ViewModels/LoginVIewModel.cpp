//
// Created by Tirehar on 2025/11/23.
//

#include "LoginVIewModel.h"

#include <QNetworkReply>

#include "Helpers/JsonHelper.hpp"
#include "MessageServices/networkservice.h"
#include "Models/LoginModel.h"

void LoginVIewModel::login(const QString &account, const QString &password) {
    auto model = LoginModel(account, password);
    auto content = JsonHelper::toJsonObject(&model);
    auto reply = NetworkService::getInstance()->sendPostRequest("https://localhost:7034/api/Login/Login", content);
    connect(reply, &QNetworkReply::finished, [reply, account, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto bytes = reply->readAll();
            auto jsonDoc = QJsonDocument::fromJson(bytes);
            auto jsonObj = jsonDoc.object();
            auto code = jsonObj.value("code").toInt();
            if (code == 0) {
                loginResponse(true);
                qDebug() << "Login successful for account:" << account;
            } else {
                loginResponse(false);
                qDebug() << "Login failed for account:" << account << "Code:" << code;
            }
        } else {
            loginResponse(false);
            qDebug() << "Network error during login for account:" << account << "Error:" << reply->errorString();
        }
        reply->deleteLater();

    });
}
