#include "network_service.h"

#include <QNetworkCookieJar>
#include <QSettings>

NetworkService::NetworkService() {
    manager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
}

NetworkService* NetworkService::getInstance() {
    static NetworkService instance;
    return &instance;
}

QNetworkReply* NetworkService::sendGetRequest(const QString &url, const QJsonObject &json) {
    auto request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        return manager->get(request, jsonData);
    }
    return manager->get(request);
}

QNetworkReply* NetworkService::sendPostRequest(const QString &url, const QJsonObject &json) {
    auto request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::CookieHeader,  QVariant::fromValue(cookies));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        return manager->post(request, jsonData);
    }
    return manager->post(request, QByteArray());
}

void NetworkService::setCookie(const QList<QNetworkCookie> &cookies) {
    this->cookies = cookies;
}

QList<QNetworkCookie> NetworkService::getCookies() {
    return cookies;
}

void NetworkService::requestCookie(const QByteArray &uid) {
    auto cookieJar = manager->cookieJar();
    QUrl cookieUrl("https://localhost:7034");
    auto cookies = cookieJar->cookiesForUrl(cookieUrl);
    cookies.append(QNetworkCookie("uid", uid));
    setCookie(cookies);
    saveCookie(cookies);
}

void NetworkService::saveCookie(const QList<QNetworkCookie> &cookies) {
    QSettings settings("Tirehar", "ThirdMessage");
    QByteArray cookieData;
    for (const QNetworkCookie &cookie : cookies) {
        cookieData.append(cookie.toRawForm());
    }
    settings.setValue("Cookie", cookieData);
    settings.sync();
}

