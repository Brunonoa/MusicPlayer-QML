import QtQuick 2.0
import QtQuick.Layouts 1.1
import "."

import "../menu"

PageTheme {

    function splitTime(lista, separator, index) {
        const words = lista.split(separator);
        return parseInt(words[index], 10);
    }

    // Background
    TimeBackground {
        anchors.fill: parent
        timeDuration: 360000
    }

    Connections {
        target: systemcore
        onUpdateTime: {
            spinnerLayout.hours = splitTime(currentTimeValue, ":", 0);
            spinnerLayout.minutes = splitTime(currentTimeValue, ":", 1);
            spinnerLayout.seconds = splitTime(currentTimeValue, ":", 2);
        }
    }

    Item {
        id: timeList
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -spinnerLayout.width/2
        anchors.verticalCenterOffset: -spinnerLayout.height/2
        RowLayout {
            id : spinnerLayout
            spacing: 2

            property int hours
            property int minutes
            property int seconds

            Spinner { max: 24; value: parent.hours; }
            Rectangle { color : "white"; width: 10; height: 250 }
            Spinner { max: 60; value: parent.minutes; }
            Rectangle { color : "white"; width: 10; height: 250 }
            Spinner { max: 60; value: parent.seconds; }
        }
    }
}
