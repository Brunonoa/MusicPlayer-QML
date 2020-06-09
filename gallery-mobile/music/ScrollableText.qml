import QtQuick 2.3

Item {
    id: scrollingText
    clip: true

    property color textColor: "yellow"
    property string textString: "text"
    property int pointSize: 54
    property int duration: 10000
    property int distance: 100

    property int positionText2
    property int durationText2

    function initialize()
    {
        positionText2 = distance + (text1.contentWidth > scrollingText.width ? text1.contentWidth : scrollingText.width);
        durationText2 = (text1.contentWidth/scrollingText.width) * duration * (text1.contentWidth > scrollingText.width ? positionText2/text1.contentWidth : 1)
        text1.x = 0;
        text2.x = positionText2;
        if(animation.running)
            animation.restart();
    }

    Component.onCompleted: initialize()

    Connections {
        target: text1
        onTextChanged: initialize()
    }

    Text {
        id: text1
        x: 0
        verticalAlignment: Text.AlignVCenter
        text: textString
        color: textColor
        font.pointSize: pointSize
        font.family: "qrc:/fonts/OpenSans-Regular.ttf"
        font.bold: true
        style: Text.Raised
        styleColor: "#111111"
    }

    Text {
        id: text2
        x: positionText2
        verticalAlignment: Text.AlignVCenter
        text: textString
        color: textColor
        font.pointSize: pointSize
        font.family: "qrc:/fonts/OpenSans-Regular.ttf"
        font.bold: true
        style: Text.Raised
        styleColor: "#111111"
        visible: text1.contentWidth > scrollingText.width
    }

    SequentialAnimation {
        id: animation
        running: text1.contentWidth > scrollingText.width
        loops: Animation.Infinite

        ParallelAnimation {
            PropertyAnimation {target: text1; property: "x"; to: -positionText2; duration: durationText2}
            PropertyAnimation {target: text2; property: "x"; to: 0; duration: durationText2}
        }

        PropertyAnimation {target: text1; property: "x"; to: positionText2; duration: 0}

        ParallelAnimation {
            PropertyAnimation {target: text1; property: "x"; to: 0; duration: durationText2}
            PropertyAnimation {target: text2; property: "x"; to: -positionText2; duration: durationText2}
       }

       PropertyAnimation {target: text2; property: "x"; to: positionText2; duration: 0}
    }
}

/*Item {
    id: scrollingText
    clip: true

    property color textColor: "white"
    property string text: "This is a scrolling text!"
    property int duration: 2000

    Text {
        id: text1
        verticalAlignment: Text.AlignVCenter
        text: scrollingText.text
        color: "white"
        x: 0
        font.pointSize: 64
    }

    Text {
        id: text2
        verticalAlignment: Text.AlignVCenter
        text: scrollingText.text
        color: "white"
        x: scrollingText.width
        font.pointSize: 64
    }

    SequentialAnimation {
        id: animation
        running:true
        loops: Animation.Infinite

        ParallelAnimation {
            PropertyAnimation {target: text1; property: "x"; to: -scrollingText.width; duration: scrollingText.duration}
            PropertyAnimation {target: text2; property: "x"; to: 0; duration: scrollingText.duration}
        }

        PropertyAnimation {target: text1; property: "x"; to: scrollingText.width; duration: 0}

        ParallelAnimation {
            PropertyAnimation {target: text1; property: "x"; to: 0; duration: scrollingText.duration}
            PropertyAnimation {target: text2; property: "x"; to: -scrollingText.width; duration: scrollingText.duration}
       }

       PropertyAnimation {target: text2; property: "x"; to: scrollingText.width; duration: 0}
    }
}
*/

