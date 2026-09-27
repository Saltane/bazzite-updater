// SPDX-FileCopyrightText: 2026 Robert French <frenchrobertm@outlook.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rebase_model.h"
#include "k_config.h"
#include <qcontainerfwd.h>
#include <qjsonarray.h>

RebaseModel::RebaseModel()
{
    targets = appConfig()->rebaseTargets;
}
