#ifndef NETWORK_SERVICE_H
#define NETWORK_SERVICE_H
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QJsonObject>

class NetworkService : public QObject
{
    Q_OBJECT
public:
    QNetworkReply* sendGetRequest(const QString &url, const QJsonObject &json = QJsonObject());
    QNetworkReply* sendPostRequest(const QString &url, const QJsonObject &json = QJsonObject());
    static NetworkService* getInstance();
private:
    QSharedPointer<QNetworkAccessManager> manager;
    NetworkService();
};

#endif // NETWORK_SERVICE_H
