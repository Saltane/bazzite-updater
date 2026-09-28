// SPDX-FileCopyrightText: 2026 Robert French <frenchrobertm@outlook.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <qcontainerfwd.h>
#include <qjsengine.h>
#include <qobject.h>
#include <qqmlengine.h>
#include <qqmlintegration.h>
#include <qset.h>
#include <qtclasshelpermacros.h>
#include <qtmetamacros.h>
#include <qvariant.h>

// Required for QVariantSet.contains(other QVariantSet) to work
inline size_t qHash(const QVariant &key, size_t seed = 0) noexcept
{
    if (key.canConvert<QString>()) {
        return qHash(key.toString(), seed);
    }

    return qHash(key.userType(), seed);
}

using QVariantSet = QSet<QVariant>;

// Each QVariant in targets is: { url, name, features[], tags[] }

class RebaseModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_DISABLE_COPY_MOVE(RebaseModel)
    RebaseModel();

public: // singleton methods
    static RebaseModel *instance()
    {
        static RebaseModel *s_instance = new RebaseModel();
        return s_instance;
    }

    static RebaseModel *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        Q_UNUSED(jsEngine)
        RebaseModel *instancePtr = instance();
        qmlEngine->setObjectOwnership(instancePtr, QQmlEngine::CppOwnership);
        return instancePtr;
    }

public:
    QVariantList targets;
    Q_PROPERTY(QVariantList targets MEMBER targets CONSTANT)

    QVariantList filtered;
    Q_PROPERTY(QVariantList filtered MEMBER filtered NOTIFY filteredChanged)
    Q_SIGNAL void filteredChanged();
    void updateFiltered();

    // TODO
    // QVariantSet all_features;
    // QVariantSet current_image_features;

    // change this to update filtered
    QVariantSet m_features;
    Q_PROPERTY(QVariantList features READ features WRITE setFeatures NOTIFY featuresChanged)
    QVariantList features() const;
    void setFeatures(QVariantList val);
    Q_SIGNAL void featuresChanged();
};
