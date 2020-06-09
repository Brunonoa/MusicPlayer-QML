import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import "."

//import com.tsts.comps 1.0

Page {

    property alias toolbarButtons: buttonsLoader.sourceComponent
    property alias toolbarTitle: titleLabel.text

    header: ToolBarTheme {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                background: Image {
                    source: "qrc:/res/icons/back.svg"
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop();
                    }
                }
            }

            Label {
                id: titleLabel
                Layout.fillWidth: true
                color: Style.text
                elide: Text.ElideRight
                font.pointSize: 20
            }

            Loader {
                Layout.alignment: Qt.AlignRight
                id: buttonsLoader
            }
        }
    }

    Rectangle {
        id: mainScreen
        color: StyleDark.pageBackground
        anchors.fill: parent
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
