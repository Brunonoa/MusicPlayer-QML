import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import VideocameraLib 1.0
import PwmLib 1.0

import "../menu"

PageTheme {
    toolbarTitle: "VideoCamera"

    Pwm {
        id: servoMotorX
        Component.onCompleted: {init(0); period = 20000000; duty = 4.6; enable = true;}
        Component.onDestruction: enable = false
        onDutyChanged: { videocamera.onMotorsMoved(servoMotorX.duty, servoMotorY.duty);}
    }

    Pwm {
        id: servoMotorY
        Component.onCompleted: {init(1); period = 20000000; duty = 4.6; enable = true;}
        Component.onDestruction: enable = false
        onDutyChanged: {videocamera.onMotorsMoved(servoMotorX.duty, servoMotorY.duty);}
    }

    Binding {
        target: servoMotorX
        property: "duty"
        value: asseX.value
    }

    Binding {
        target: servoMotorY
        property: "duty"
        value: asseY.value
    }

    Item {
        id: background
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 512; height: 384

        Videocamera {
            id: videocamera
            // @disable-check M16
            anchors.fill: parent
            //width: 512; height: 384
            //x: 10; y: 10

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                /* I made the connection in qml mouseArea.clicked.connect(cppObject.onClicked)
                and then in C++ simply received a QObject* which has properties as expected:
                void CppClass::onClicked(QObject *event) {qDebug() << "clicked";} */
                Component.onCompleted: {
                    mouseArea.positionChanged.connect(videocamera.onMouseMoved);
                    mouseArea.clicked.connect(videocamera.onColorPicked);
                }
            }

            onMoveMotors:
            {
                var motorx = servoMotorX.duty + outputX;
                if(motorx < asseX.from) motorx = asseX.from;
                else if(motorx > asseX.to) motorx = asseX.to;

                servoMotorX.duty = motorx;
                asseX.value = motorx;

                var motory = servoMotorY.duty + outputY;
                if(motory < asseY.from) motory = asseY.from;
                else if(motory > asseY.to) motory = asseY.to;

                servoMotorY.duty = motory;
                asseY.value = motory;
            }

            Column {
                spacing:10
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                anchors {
                    bottomMargin: 20
                    bottom: parent.top
                }

                Row {
                    id: extraMode
                    spacing:10
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter

                    Rectangle {
                        id: pidButton
                        implicitWidth: 140
                        implicitHeight: 40

                        border.color: "#26282a"
                        border.width: 1
                        radius: 4
                        Component.onCompleted: {state = "pidOff"}
                        Text {id: pidText; text: "pid mode on"; anchors.centerIn: parent }
                        MouseArea {
                            id: pidMode; anchors.fill: parent
                            onClicked: pidButton.state = (pidButton.state === "pidOff") ? "pidOn" : "pidOff";
                        }
                        states: [
                            State {
                                name: "pidOn"
                                when: pidMode.clicked
                                PropertyChanges { target: pidText; text: "pid mode off" }
                            },
                            State {
                                name: "pidOff"
                                when: pidMode.clicked
                                PropertyChanges { target: pidText; text: "pid mode on" }
                            }
                        ]
                        transitions: [
                            Transition {
                                ScriptAction {
                                    script: videocamera.onPidFollowMode(pidButton.state === "pidOn");
                                }
                            }
                        ]
                    }
                }

                Row {
                    id: detectionMode
                    spacing:10
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter

                    Rectangle {
                        id: colorButton
                        implicitWidth: 140
                        implicitHeight: 40
                        color: colorMode.pressed ? "#d6d6d6" : "#f6f6f6"
                        border.color: "#26282a"
                        border.width: 1
                        radius: 4
                        Component.onCompleted: {state = "colorOff"}
                        Text {id: colorText; text: "color mode on"; anchors.centerIn: parent }
                        MouseArea {
                            id: colorMode; anchors.fill: parent
                            onClicked: colorButton.state = (colorButton.state === "colorOff") ? "colorOn" : "colorOff";
                        }
                        states: [
                            State {
                                name: "colorOn"
                                when: colorMode.clicked
                                PropertyChanges { target: colorText; text: "color mode off" }
                                PropertyChanges { target: colorDetection; visible: true}
                            },
                            State {
                                name: "colorOff"
                                when: colorMode.clicked
                                PropertyChanges { target: colorText; text: "color mode on" }
                                PropertyChanges { target: colorDetection; visible: false}
                            }
                        ]
                        transitions: [
                            Transition {
                                ScriptAction {
                                    script: videocamera.onColorDetectionMode(colorButton.state === "colorOn");
                                }
                            }
                        ]
                    }
                }
            }

            Column {
                id: colorDetection
                spacing:10
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                anchors {
                    leftMargin: 20
                    left: parent.right
                }

                Rectangle {
                    implicitWidth: 140
                    implicitHeight: 40
                    color: biggerArea.pressed ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                    Text {text: "bigger sample area"; anchors.centerIn: parent }
                    MouseArea {
                        id: biggerArea; anchors.fill: parent
                        onClicked: videocamera.onAreaChanged(10)
                    }
                }

                Rectangle {
                    implicitWidth: 140
                    implicitHeight: 40
                    color: smallerArea.pressed ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                    Text { text: "smaller sample area"; anchors.centerIn: parent }
                    MouseArea {
                        id: smallerArea; anchors.fill: parent
                        onClicked: videocamera.onAreaChanged(-10)
                    }
                }

                Rectangle {
                    implicitWidth: 140
                    implicitHeight: 40
                    color: higherThreshold.pressed ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                    Text {text: "higher threashold"; anchors.centerIn: parent }
                    MouseArea {
                        id: higherThreshold; anchors.fill: parent
                        onClicked: videocamera.onThresholdChanged(10)
                    }
                }

                Rectangle {
                    implicitWidth: 140
                    implicitHeight: 40
                    color: lowerThreshold.pressed ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26282a"
                    border.width: 1
                    radius: 4
                    Text { text: "lower threshold"; anchors.centerIn: parent }
                    MouseArea {
                        id: lowerThreshold; anchors.fill: parent
                        onClicked: videocamera.onThresholdChanged(-10)
                    }
                }
            }

            Slider {
                id: asseX
                width: parent.width
                height: 30
                anchors {
                    topMargin: 20
                    top: parent.bottom
                }
                from: 2.8
                value: 4.4
                to: 6.2
                onHandleChanged: pidButton.state = "pidOff"
            }

            Slider {
                id: asseY
                width: 30
                height: parent.height
                orientation: Qt.Vertical
                anchors {
                    rightMargin: 20
                    right: parent.left
                }
                from: 2.8
                value: 4.4
                to: 6.2
                onHandleChanged: pidButton.state = "pidOff"
            }
        }
    }
}
