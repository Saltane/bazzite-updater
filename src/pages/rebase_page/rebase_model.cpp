// SPDX-FileCopyrightText: 2026 Robert French <frenchrobertm@outlook.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rebase_model.h"
#include "k_config.h"
#include <qcontainerfwd.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qset.h>
#include <qvariant.h>

RebaseModel::RebaseModel()
{
    for (const QVariant &item : appConfig()->rebaseTargets) {
        auto obj = item.toJsonObject();

        auto imgs = obj.value(u"images"_s).toArray();
        auto url = obj.value(u"url"_s).toString();

        for (const QJsonValue &img : imgs) {
            auto imgObj = img.toObject();
            imgObj.insert(u"url"_s, url);
            targets.append(imgObj);
        }
    }

    filtered = targets;
}

// convert set to list
QVariantList RebaseModel::features() const
{
    QVariantList list;
    list.reserve(m_features.size());
    for (const QVariant &item : m_features) {
        list.append(item);
    }
    return list;
}

void RebaseModel::setFeatures(QVariantList features)
{
    m_features.clear();
    for (const QVariant &item : features)
        m_features.insert(item);

    updateFiltered();
    Q_EMIT featuresChanged();
}

void RebaseModel::updateFiltered()
{
    filtered.clear();

    if (m_features.isEmpty()) {
        filtered = targets;
    } else {
        for (const QVariant &img : targets) {
            auto obj = img.toJsonObject();

            QVariantSet img_feats;
            for (const QJsonValue &item : obj.value(u"features"_s).toArray()) {
                img_feats.insert(item.toVariant());
            }

            if (img_feats.contains(m_features)) {
                filtered.append(img);
            }
        }
    }

    Q_EMIT filteredChanged();
}
