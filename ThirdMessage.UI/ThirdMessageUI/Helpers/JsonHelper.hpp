#pragma once
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonValue>
#include <QtCore/QVariant>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QObject>
#include <QtCore/QString>

class JsonHelper {
public:
    static QJsonObject toJsonObject(const QObject *obj) {
        QJsonObject json;
        if (!obj) return json;
        const QMetaObject *mo = obj->metaObject();
        for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
            QMetaProperty prop = mo->property(i);
            QVariant v = prop.read(obj);
            json.insert(QString::fromLatin1(prop.name()), QJsonValue::fromVariant(v));
        }
        // 包含动态属性
        for (const QByteArray &dynName : obj->dynamicPropertyNames()) {
            QVariant v = obj->property(dynName.constData());
            json.insert(QString::fromLatin1(dynName), QJsonValue::fromVariant(v));
        }
        return json;
    }

    static QString toJsonString(const QObject *obj) {
        return QString::fromUtf8(QJsonDocument(toJsonObject(obj)).toJson(QJsonDocument::Compact));
    }

    // 将 json 应用到已有 QObject 对象上（返回是否全部写入成功）
    static bool applyJsonToObject(QObject *obj, const QJsonObject &json) {
        if (!obj) return false;
        const QMetaObject *mo = obj->metaObject();
        bool ok = true;
        for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
            QMetaProperty prop = mo->property(i);
            QString name = QString::fromLatin1(prop.name());
            if (json.contains(name)) {
                QVariant v = json.value(name).toVariant();
                if (!prop.write(obj, v)) ok = false;
            }
        }
        // 写入动态属性
        for (auto it = json.begin(); it != json.end(); ++it) {
            QByteArray bName = it.key().toLatin1();
            // 如果不是现有的元属性，则写为动态属性
            if (mo->indexOfProperty(bName.constData()) < 0) {
                obj->setProperty(bName.constData(), it.value().toVariant());
            }
        }
        return ok;
    }

    static bool applyJsonStringToObject(QObject *obj, const QString &jsonStr) {
        QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
        return applyJsonToObject(obj, doc.object());
    }
};