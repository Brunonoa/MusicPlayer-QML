import QtQuick 2.6
import QtQuick.Controls 2.0
import "." // QTBUG-34418, singletons require explicit import to load qmldir file

import "./menu"
import "./camera"
import VideocameraLib 1.0

ApplicationWindow {

    readonly property alias pageStack: stackView
    readonly property alias stackBusy: busyIndicator

    id: app
    visible: true
    width: 768
    height: 1360
    color: Style.windowBackground

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Menu {}
    }

    BusyIndicator {
        id: busyIndicator
        width: 100
        height: 100
        anchors.centerIn: parent
        running: false
    }

    onClosing: {
        if (Qt.platform.os == "android") {
            if (stackView.depth > 1) {
                close.accepted = false
                stackView.pop()
            }
        }
    }
}
