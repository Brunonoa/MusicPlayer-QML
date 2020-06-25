import QtQuick 2.6
import QtQuick.Controls 2.0
import "."

Rectangle
{
    ListModel {
        id: appModel
        ListElement {name: "Shutdown"; icon: "qrc:/menu/icon/002-apple-22.svg"; link: ""}
        ListElement { name: "Gallery"; icon: "qrc:/menu/icon/048-photos.svg"; link: "qrc:/gallery/AlbumListPage.qml"}
        ListElement { name: "Music"; icon: "qrc:/menu/icon/034-garage-band.svg"; link: "qrc:/music/PlayListPage.qml"}
        ListElement {name: "Time"; icon: "qrc:/menu/icon/045-clock.svg"; link: "qrc:/time/TimePage.qml"}
        ListElement {name: "Charts"; icon: "qrc:/menu/icon/041-stocks.svg"; link: "qrc:/chart/Performances.qml"}
        ListElement {name: "Camera"; icon: "qrc:/menu/icon/047-camera.svg"; link: "qrc:/camera/Opencv.qml"}
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
           focus: true
           model: appModel

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
                           console.log(name)
                            if(name=="Shutdown") {
                                systemCall.shutdown();
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

    StackView.onActivated:
        stackBusy.running = false;
    StackView.onDeactivated:
        stackBusy.running = false;
    StackView.onActivating:
        stackBusy.running = true;
    StackView.onDeactivating:
        stackBusy.running = true;
}

