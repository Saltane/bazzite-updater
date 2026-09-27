// SPDX-FileCopyrightText: 2026 Robert French <frenchrobertm@outlook.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <qcontainerfwd.h>
#include <qjsengine.h>
#include <qobject.h>
#include <qqmlengine.h>
#include <qqmlintegration.h>
#include <qtclasshelpermacros.h>
#include <qtmetamacros.h>

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
    Q_PROPERTY(QVariantList targets MEMBER targets NOTIFY targetsChanged)
    Q_SIGNAL void targetsChanged();

    QVariantList filtered;
    Q_PROPERTY(QVariantList filtered MEMBER filtered NOTIFY filteredChanged)
    Q_SIGNAL void filteredChanged();

    // change this to update filtered
    QVariantList features;
    Q_PROPERTY(QVariantList features MEMBER features NOTIFY featuresChanged)
    Q_SIGNAL void featuresChanged();
};
