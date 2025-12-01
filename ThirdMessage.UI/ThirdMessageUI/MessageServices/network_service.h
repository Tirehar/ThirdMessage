#ifndef NETWORK_SERVICE_H
#define NETWORK_SERVICE_H
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QJsonObject>

class NetworkService : public QObject
{
    Q_OBJECT
public:
    QNetworkReply* sendGetRequest(const QUrl &url, const QJsonObject &json = QJsonObject());
    QNetworkReply* sendPostRequest(const QUrl &url, const QJsonObject &json = QJsonObject());
    void setCookie(QList<QNetworkCookie>& cookies, const QByteArray& uid);
    void requestCookie(const QByteArray &uid);
    void saveCookie(const QList<QNetworkCookie> &cookies);
    QList<QNetworkCookie> getCookies();
    static NetworkService* getInstance();
private:
    QSharedPointer<QNetworkAccessManager> manager;
    QList<QNetworkCookie> cookies;
    NetworkService();
};

#endif // NETWORK_SERVICE_H
