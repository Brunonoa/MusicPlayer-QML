import QtQuick 2.9
import QtQuick.Controls 2.0
import "."

import QtMultimedia 5.9

Page
{
    id: menu
    ListModel {
        id: appModel
        ListElement { name: "Gallery"; icon: "qrc:/menu/icon/048-photos.svg"; link: "qrc:/gallery/AlbumListPage.qml"}
        ListElement { name: "Music"; icon: "qrc:/menu/icon/034-garage-band.svg"; link: "qrc:/music/PlayListPage.qml"}
        ListElement {name: "Time"; icon: "qrc:/menu/icon/045-clock.svg"; link: "qrc:/time/TimePage.qml"}
        ListElement {name: "Charts"; icon: "qrc:/menu/icon/041-stocks.svg"; link: "qrc:/chart/Performances.qml"}
        ListElement {name: "Camera"; icon: "qrc:/menu/icon/047-camera.svg"; link: "qrc:/camera/Opencv.qml"}
        ListElement {name: "Shutdown"; icon: "qrc:/menu/icon/021-apple-5.svg"; link: ""}
        ListElement {name: "Close"; icon: "qrc:/menu/icon/040-files.svg"; link: ""}
    }

    Image {
        source: "qrc:/menu/image/background.jpg"
        opacity: 0.5
        anchors.centerIn: parent
        fillMode: Image.Pad
    }

    GridView {
           id: myGridView
           anchors.fill: parent
           anchors.topMargin: 50
           anchors.leftMargin: 50
           cellWidth: 300; cellHeight: 300
           model: appModel
           highlightFollowsCurrentItem: true

           /*Shortcut {
              //context: Qt.ApplicationShortcut
              sequences: [StandardKey.MoveToNextLine, StandardKey.MoveToPreviousLine,
                  StandardKey.MoveToNextChar, StandardKey.MoveToPreviousChar]

               onActivated: {
                    myGridView.currentIndex++;
                    console.log("JS: Shortcut activated.");
               }
           }*/

           highlight: Rectangle {   width: parent.cellWidth; height: parent.cellHeight;
                                    color: "lightsteelblue" }

           delegate: Component {
               id: myDelegate
               Item {
                   width: myGridView.cellWidth - 50; height: myGridView.cellHeight - 50

                   Image {
                       id: myIcon
                       height: parent.height
                       width: parent.width
                       source: icon
                   }
                   Text {
                       id: appName
                       anchors { top: myIcon.bottom; horizontalCenter: parent.horizontalCenter }
                       text: name
                       color: "WHITE"
                       font.pointSize: 20
                   }

                   MouseArea {
                       anchors.fill: parent
                       onClicked: {
                            if(name=="Shutdown") {
                                systemCall.shutdown();
                            }
                            else if (name=="Close") {
                                Qt.quit();
                            }
                            else {
                                parent.GridView.view.currentIndex = index;
                                pageStack.push(link);
                            }
                       }
                   }
               }
           }
    }

    Item {
        focus: true
        Keys.onPressed: {
            if(event.key === Qt.Key_Left) {
                myGridView.moveCurrentIndexLeft();
                event.accepted = true;
            }
            else if(event.key === Qt.Key_Right) {
                myGridView.moveCurrentIndexRight();
                event.accepted = true;
            }
            else if(event.key === Qt.Key_Down) {
                myGridView.moveCurrentIndexDown();
                event.accepted = true;
            }
            else if(event.key === Qt.Key_Up) {
                myGridView.moveCurrentIndexUp();
                event.accepted = true;
            }
            else if(event.key === Qt.Key_Return) {
                pageStack.push(appModel.get(myGridView.currentIndex).link);
                event.accepted = true;
            }
            else if(event.key === Qt.Key_Space) {
                //pageStack.pop();
                event.accepted = true;
            }
            console.log(event.key);
        }
    }

    StackView.onActivated:
        stackBusy.running = false;
    StackView.onDeactivated:
        stackBusy.running = false;
    StackView.onActivating:
        stackBusy.running = true;
    StackView.onDeactivating:
        stackBusy.running = true;
}

