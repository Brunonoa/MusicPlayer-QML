import QtQuick 2.0

import "../menu"
import "."

PageTheme {

    Connections {
        target: systemcore
        onUpdateCpuLoad: console.log("Cpu usata: " + currentCpuLoad)
        onUpdateMemoryUsed: console.log("Memoria usata: " + currentMemoryUsed)
    }
}
