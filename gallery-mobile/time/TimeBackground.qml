import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Particles 2.0

Item {
    id: window

    property int backgroundWidth: parent.width
    property int backgroundHeight: parent.height
    property int timeDuration: 10000

    width: backgroundWidth
    height: backgroundHeight

    // Let's draw the sky...
    Rectangle {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: parent.verticalCenter }
        //! [0]
        gradient: Gradient {
            GradientStop {
                position: 0.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: timeDuration/2 }
                    ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: timeDuration/2 }
                }
            }
            GradientStop {
                position: 1.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14aaff"; to: "#437284"; duration: timeDuration/2 }
                    ColorAnimation { from: "#437284"; to: "#14aaff"; duration: timeDuration/2 }
                }
            }
        }
        //! [0]
    }

    // the sun, moon, and stars
    Item {
        width: parent.width; height: 2 * parent.height
        NumberAnimation on rotation { from: 0; to: 360; duration: timeDuration; loops: Animation.Infinite }
        Image {
            source: "qrc:/time/images/sun.png"; y: 10; anchors.horizontalCenter: parent.horizontalCenter
            rotation: -3 * parent.rotation
        }
        Image {
            source: "qrc:/time/images/moon.png"; y: parent.height - 74; anchors.horizontalCenter: parent.horizontalCenter
            rotation: -parent.rotation
        }
        ParticleSystem {
            id: particlesystem
            x: 0; y: parent.height/2
            width: parent.width; height: parent.height/2
            ImageParticle {
                source: "qrc:/time/images/star.png"
                groups: ["star"]
                color: "#00333333"
                SequentialAnimation on opacity {
                    loops: Animation.Infinite
                    NumberAnimation { from: 0; to: 1; duration: timeDuration/2 }
                    NumberAnimation { from: 1; to: 0; duration: timeDuration/2 }
                }
            }
            Emitter {
                group: "star"
                anchors.fill: parent
                emitRate: parent.width / 50
                lifeSpan: 5000
            }
        }
    }

    // ...and the ground.
    Rectangle {
        anchors { left: parent.left; top: parent.verticalCenter; right: parent.right; bottom: parent.bottom }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#80c342"; to: "#001600"; duration: timeDuration/2 }
                    ColorAnimation { from: "#001600"; to: "#80c342"; duration: timeDuration/2 }
                }
            }
            GradientStop { position: 1.0; color: "#006325" }
        }
    }
}

