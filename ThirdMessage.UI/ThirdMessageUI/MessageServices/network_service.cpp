#include "network_service.h"

#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QSettings>

NetworkService::NetworkService() {
    manager = QSharedPointer<QNetworkAccessManager>(new QNetworkAccessManager());
    connect(manager.data(), &QNetworkAccessManager::sslErrors, this,
    [](QNetworkReply* reply, const QList<QSslError>&){
        reply->ignoreSslErrors();
    });
}

NetworkService* NetworkService::getInstance() {
    static NetworkService instance;
    return &instance;
}

QNetworkReply* NetworkService::sendGetRequest(const QUrl &url, const QJsonObject &json) {
    auto request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        return manager->get(request, jsonData);
    }
    return manager->get(request);
}

QNetworkReply* NetworkService::sendPostRequest(const QUrl &url, const QJsonObject &json) {
    auto request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::CookieHeader,  QVariant::fromValue(cookies));
    if (!json.isEmpty()) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));
        auto jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
        return manager->post(request, jsonData);
    }
    return manager->post(request, QByteArray());
}

void NetworkService::setCookie(QList<QNetworkCookie>& cookies, const QByteArray& uid) {
    auto cookie = QNetworkCookie("uid", uid);
    cookies.append(cookie);
    this->cookies = cookies;
}

QList<QNetworkCookie> NetworkService::getCookies() {
    return cookies;
}

void NetworkService::requestCookie(const QByteArray &uid) {
    auto cookieJar = manager->cookieJar();
    QSettings settings("config.ini", QSettings::IniFormat);
    auto cookies = cookieJar->cookiesForUrl(QUrl(settings.value("ServerAddress").toByteArray()));
    setCookie(cookies, uid);
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

