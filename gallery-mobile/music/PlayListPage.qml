import QtQuick 2.6
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQml 2.0
import "."

import "../menu"

PageTheme {

    property string musicFolder: "qrc:/music/icon/folder_music10.png"
    property int infotabHeight: 150
    property int infotabWidth: 1000
    property int fontSize: 28

    toolbarTitle: "Playlists"

    FontLoader
    {
        id: playlistFont
        name: "comic-sans-ms"
        source: "qrc:/fonts/comic-sans-ms.ttf"
    }


        PlayListBackground {
            anchors.fill: parent

            Rectangle {
                id:infotab
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 10
                border.color: "black"
                border.width: 10
                radius: 50
                height: infotabHeight
                width: infotabWidth
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "red" }
                    GradientStop { position: 0.33; color: "yellow" }
                    GradientStop { position: 1.0; color: "green" }
                }
                Text {
                    id: playlistInfo
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.family: playlistFont.name
                    font.pointSize: fontSize
                    text: playlistModel.getPlaylistInformation(view.currentIndex);
                }
            }

            Component {
                id: delegate
                Image
                {
                    id: nameImage
                    opacity: PathView.isCurrentItem ? 1.0 : 0.5
                    scale: PathView.iconScale
                    width: 240; height: 240
                    source: (!!icon) ? musicFolder : icon
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            pageStack.push("qrc:/music/MusicPage.qml",
                                           { playlistName: name, playlistIndex: index, playlistSize: size})
                        }
                    }
                    Text {
                        id: nameText
                        anchors.bottom: nameImage.top
                        anchors.margins: 20

                        font.capitalization: Font.AllUppercase
                        font.family: playlistFont.name
                        font.pointSize: 54
                        color: "yellow"
                        text: name
                    }
                }
            }

            PathView {
                id: view
                anchors.fill: parent
                model: playlistModel
                delegate: delegate
                preferredHighlightBegin: 0.5
                preferredHighlightEnd: 0.5
                snapMode: PathView.SnapToItem
                cacheItemCount: 10
                path: Path {
                    startX: 150; startY: 200
                     PathAttribute { name: "iconScale"; value: 0.3 }
                     PathAttribute { name: "iconOpacity"; value: 0.5 }
                     PathCurve { x: 150; y: 200 }
                     PathCurve { x: 400; y: 350 }
                     PathCurve { x: 550; y: 400 }
                     PathCurve { x: 650; y: 350 }
                     PathAttribute { name: "iconScale"; value: 1.0 }
                     PathAttribute { name: "iconOpacity"; value: 1.0 }
                     PathCurve { x: 750; y: 350 }
                     PathCurve { x: 850; y: 400 }
                     PathCurve { x: 1000; y: 350 }
                     PathCurve { x: 1150; y: 200 }
                     PathAttribute { name: "iconScale"; value: 0.3 }
                     PathAttribute { name: "iconOpacity"; value: 0.5 }
                }

                //fontHelper.changeStretchFont(playlistInfo.font, infotab.width * (100.0/infotabWidth));
                onMovementEnded: { openMovementAnimation.start(); }
                onDragStarted: { closeMovementAnimation.start();}
            }
        }

        ParallelAnimation {
            id: openMovementAnimation
            PropertyAnimation {
                target: infotab
                property: "width"
                to: infotabWidth
                easing.type: Easing.OutElastic
                duration: 600
            }
            PropertyAnimation {
                target: playlistInfo
                property: "font.pointSize"
                to: fontSize
                easing.type: Easing.OutElastic
                duration: 600
            }
            onStarted: playlistInfo.visible = true
        }

        ParallelAnimation {
            id: closeMovementAnimation
            PropertyAnimation {
                target: infotab
                property: "width"
                to: 0
                easing.type: Easing.InOutQuad
                duration: 600
            }
            PropertyAnimation {
                target: playlistInfo
                property: "font.pointSize"
                to: 1
                easing.type: Easing.InOutQuad
                duration: 600
            }
            onStopped: playlistInfo.visible = false
        }

        Item {
            focus: true
            Keys.onPressed: {
                if(event.key === Qt.Key_Left) {
                    view.decrementCurrentIndex();
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Right) {
                    view.incrementCurrentIndex();
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Return) {
                    pageStack.push("qrc:/music/MusicPage.qml", {
                                        playlistName: playlistModel.data(view.currentIndex, playlistModel.name),
                                        playlistIndex: playlistModel.data(view.currentIndex, playlistModel.index),
                                        playlistSize: playlistModel.data(view.currentIndex, playlistModel.size)});
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Space) {
                    pageStack.pop();
                    event.accepted = true;
                }
                console.log(event.key);
            }
        }

}
