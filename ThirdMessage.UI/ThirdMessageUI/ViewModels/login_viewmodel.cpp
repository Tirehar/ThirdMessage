//
// Created by Tirehar on 2025/11/23.
//

#include "login_viewmodel.h"

#include <QNetworkReply>
#include <QSettings>

#include "main_viewmodel.h"
#include "Helpers/json_helper.hpp"
#include "MessageServices/network_service.h"
#include "Models/login_model.h"

void LoginVIewModel::login(const QString &account, const QString &password) {
    auto model = LoginModel(account, password);
    auto content = JsonHelper::toJsonObject(&model);
    auto reply = NetworkService::getInstance()->sendPostRequest("https://localhost:7034/api/Login/Login", content);
    connect(reply, &QNetworkReply::finished, [reply, account, this] {
        if (reply->error() == QNetworkReply::NoError) {
            auto bytes = reply->readAll();
            auto jsonDoc = QJsonDocument::fromJson(bytes);
            auto code = jsonDoc["code"].toInt();
            if (code == 0) {
                auto uid = jsonDoc["model"]["uid"].toString();
                saveData(uid);
                loginResponse(true);
                qDebug() << "Login successful for account:" << account<<";UID:"<<uid;
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

void LoginVIewModel::saveData(const QString& uid) {
    QSettings settings("Tirehar", "ThirdMessage");
    settings.setValue("UID", uid);
    settings.sync();
}
