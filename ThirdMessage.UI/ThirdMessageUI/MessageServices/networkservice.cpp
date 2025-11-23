#include "networkservice.h"

NetworkService::NetworkService() {
    manager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
}

NetworkService* NetworkService::getInstance() {
    static NetworkService instance;
    return &instance;
}

QNetworkReply* NetworkService::sendGetRequest(const QString &url, const QJsonObject &json) {
    auto request = QNetworkRequest(QUrl(url));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        qDebug()<<json;
        return manager->get(request, jsonData);
    }
    return manager->get(request);
}

QNetworkReply* NetworkService::sendPostRequest(const QString &url, const QJsonObject &json) {
    auto request = QNetworkRequest(QUrl(url));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        qDebug()<<json;
        return manager->post(request, jsonData);
    }
    return manager->post(request, nullptr);
}

