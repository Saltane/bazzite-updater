// SPDX-FileCopyrightText: 2026 Robert French <frenchrobertm@outlook.com>
// SPDX-License-Identifier: GPL-2.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

ColumnLayout {
    id: root

    Repeater {
        model: SystemUpdateBackend.updateStepsModel

        delegate: RowLayout {
            id: del
            required property string modelData

            visible: modelData

            readonly property string module: modelData.split(" ")[0]
            readonly property int progress: parseInt(modelData.split(" ")[1])
            readonly property int total: parseInt(modelData.split(" ")[2])
            readonly property int finished: parseInt(modelData.split(" ")[3])

            spacing: Kirigami.Units.gridUnit

            Label {
                text: del.module
            }

            ProgressBar {
                Layout.fillWidth: true
                indeterminate: del.progress === -1
                value: del.progress
                to: del.total
            }

            Loader {
                sourceComponent: {
                    if (del.finished === 0)
                        return busyComponent;
                    if (del.finished === 1)
                        return checkmarkComponent;
                    return errorComponent;
                }

                Component {
                    id: busyComponent
                    BusyIndicator {
                        id: busyIndicator
                    }
                }

                Component {
                    id: checkmarkComponent
                    Kirigami.Icon {
                        source: "checkmark-symbolic"
                    }
                }

                Component {
                    id: errorComponent
                    Kirigami.Icon {
                        source: "error-symbolic"
                    }
                }
            }

            // Smooth fade-in animation
            opacity: 0
            Component.onCompleted: {
                opacity = 1;
            }
            Behavior on opacity {
                NumberAnimation {
                    duration: Kirigami.Units.longDuration
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
