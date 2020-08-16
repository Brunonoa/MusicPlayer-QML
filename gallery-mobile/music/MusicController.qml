import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2
import QtMultimedia 5.12
import QtGraphicalEffects 1.0
import "."

import "../menu"

Item {
    id: songController

    property MediaPlayer songPlayer

    // Map and function to make the id available for the other QML files
    /*property var idMap: ({   prevTrack: prevTrack,
                             prevTrackMouse: prevTrackMouse,
                             playPause: playPause,
                             playPauseMouse: playPauseMouse,
                             nextTrack: nextTrack,
                             nextTrackMouse: nextTrackMouse,
                             replay: replay,
                             replayMouse: replayMouse,
                             volumeUp: volumeUp,
                             volumeUpMouse: volumeUpMouse,
                             volumeDw: volumeDw,
                             volumeDwMouse: volumeDwMouse})

    function findItemById(id) {
      return idMap[id];
    }*/

    function msToTime(duration) {
        var seconds = parseInt((duration/1000)%60);
        var minutes = parseInt((duration/(1000*60))%60);

        minutes = (minutes < 10) ? "0" + minutes : minutes;
        seconds = (seconds < 10) ? "0" + seconds : seconds;

        return minutes + ":" + seconds;
    }

    function init() {
        replayMode(songPlayer.playlist.playbackMode);
        console.log("playback state: " + songPlayer.playbackState)
    }

    function play(mode)
    {
        if(mode===0)
            songPlayer.play();
        else if(mode===1)
            songPlayer.pause();
        else if(mode===2)
            songPlayer.play();

        console.log("playback state: " + songPlayer.playbackState)
        console.log("indice corrente: " + songPlayer.playlist.currentIndex)
    }

    function replayMode(mode) {
        if(mode===0) {
            replay.source = "qrc:/music/icon/playerIcons/svg/whole-note.svg";
            songPlayer.playlist.playbackMode=0;
        }
        else if(mode===1) {
            replay.source = "qrc:/music/icon/playerIcons/svg/crotchet.svg";
            songPlayer.playlist.playbackMode=1;
        }
        else if(mode===2) {
            replay.source = "qrc:/music/icon/playerIcons/svg/semiquaver.svg";
            songPlayer.playlist.playbackMode=2;
        }
        else if(mode===3) {
            replay.source = "qrc:/music/icon/playerIcons/svg/musical-note.svg";
            songPlayer.playlist.playbackMode=3;
        }
        else if(mode===4) {
            replay.source = "qrc:/music/icon/playerIcons/svg/musical-note-1.svg"
            songPlayer.playlist.playbackMode=4;
        }
        console.log("playback mode: " + songPlayer.playlist.playbackMode)
    }

    Connections {
       target: songPlayer

       onPaused: {
           playPause.source = "qrc:/music/icon/playerIcons/svg/play.svg"
       }

       onPlaying: {
            playPause.source = "qrc:/music/icon/playerIcons/svg/pause-1.svg"
       }

       onStopped: {
           playPause.source = "qrc:/music/icon/playerIcons/svg/play.svg";
           if (songPlayer.status === MediaPlayer.EndOfMedia)
               songPlayer.playlist.next();
       }

       onError: {
           console.log(error+" error string is "+errorString);
       }

       onMediaObjectChanged: {
           if (songPlayer.mediaObject)
                songPlayer.mediaObject.notifyInterval = 50;
       }
    }

    FontLoader
    {
        id: appFont
        name: "OpenSans-Regular"
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    // Bar containing the song controller
    Item
    {
        id: songButtons
        property string defaultAlbumIcon: "qrc:/music/icon/cover.png"
        property var linearVolume: 1.0
        property real logaritmicVolume: QtMultimedia.convertVolume(linearVolume,
                                                             QtMultimedia.LogarithmicVolumeScale,
                                                             QtMultimedia.LinearVolumeScale)

        ColumnLayout
        {
            id: container
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 10

            RowLayout
            {
                id: upperWrap
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 150
                Layout.alignment: Qt.AlignHCenter
                spacing: 50

                Image {
                    id: prevTrack
                    source: "qrc:/music/icon/playerIcons/svg/back.svg"
                    sourceSize.width: 150
                    sourceSize.height: 150
                    state: "none"

                    MouseArea {
                        id: prevTrackMouse
                        anchors.fill: parent
                        onClicked: {
                            songPlayer.playlist.previous();
                            console.log("current index:" + songPlayer.playlist.currentIndex);
                        }
                        onPressed: prevTrack.state = "pressed"
                        onReleased: prevTrack.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: prevTrack; scale: 0.8 }
                    }
                    transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Image {
                    id: playPause
                    source: "qrc:/music/icon/playerIcons/svg/play.svg"
                    sourceSize.width: 150
                    sourceSize.height: 150
                    state: "none"

                    MouseArea {
                        id: playPauseMouse
                        anchors.fill: parent
                        onClicked: play(songPlayer.playbackState);
                        onPressed: playPause.state = "pressed"
                        onReleased: playPause.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: playPause; scale: 0.8 }
                    }
                    transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                    Component.onCompleted: init()
                }

                Image {
                    id: nextTrack
                    source: "qrc:/music/icon/playerIcons/svg/next.svg"
                    sourceSize.width: 150
                    sourceSize.height: 150
                    state: "none"

                    MouseArea {
                        id: nextTrackMouse
                        anchors.fill: parent
                        onClicked: {
                            songPlayer.playlist.next();
                            console.log("current index:" + songPlayer.playlist.currentIndex);
                        }
                        onPressed: nextTrack.state = "pressed"
                        onReleased: nextTrack.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: nextTrack; scale: 0.8 }
                    }
                    transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Image {
                    id: replay
                    sourceSize.width: 150
                    sourceSize.height: 150
                    source: "qrc:/music/icon/playerIcons/svg/whole-note.svg"
                    state: "none"

                    MouseArea {
                        id: replayMouse
                        anchors.fill: parent
                        onClicked: replayMode(songPlayer.playlist.playbackMode===4 ? 0 : ++songPlayer.playlist.playbackMode);
                        onPressed: replay.state = "pressed"
                        onReleased: replay.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: replay; scale: 0.8 }
                    }
                        transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Image {
                    id: volumeUp
                    source: "qrc:/music/icon/playerIcons/svg/volume.svg"
                    sourceSize.width: 150
                    sourceSize.height: 150
                    state: "none"

                    Text {
                        anchors.centerIn: parent
                        text: "+"
                        color: "black"
                        font.bold: true
                        font.pixelSize: 50
                    }
                    MouseArea {
                        id: volumeUpMouse
                        anchors.fill: parent
                        onClicked: {
                            songButtons.linearVolume = Math.min(songButtons.linearVolume + 0.1, 1);
                            songPlayer.volume = songButtons.logaritmicVolume;
                            console.log("volume level: " + songPlayer.volume + " " + songButtons.linearVolume);
                        }
                        onPressed: volumeUp.state = "pressed"
                        onReleased: volumeUp.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: volumeUp; scale: 0.8 }
                    }
                    transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                }

                Image {
                    id: volumeDw
                    source: "qrc:/music/icon/playerIcons/svg/volume.svg"
                    sourceSize.width: 150
                    sourceSize.height: 150
                    state: "none"

                    Text {
                        anchors.centerIn: parent
                        text: "-"
                        color: "black"
                        font.bold: true
                        font.pixelSize: 50
                    }
                    MouseArea {
                        id: volumeDwMouse
                        anchors.fill: parent
                        onClicked:  {
                            songButtons.linearVolume = Math.max(songButtons.linearVolume - 0.1, 0);
                            songPlayer.volume = songButtons.logaritmicVolume;
                            console.log("volume level: " + songPlayer.volume + " " + songButtons.linearVolume);
                        }
                        onPressed: volumeDw.state = "pressed"
                        onReleased: volumeDw.state = "none"
                    }
                    states: State {
                        name: "pressed"
                        when: mouseArea.pressed
                        PropertyChanges { target: volumeDw; scale: 0.8 }
                    }
                    transitions: Transition {
                        NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
                    }
                }
            }

            Rectangle
            {
                id: filler
                width: parent.width
                height: 50
                color: "transparent"
            }

            RowLayout
            {
                id: middleWrapper
                Layout.fillHeight: true
                Layout.fillWidth: true

                Rectangle {
                    id: leftWapper
                    Layout.leftMargin: 70
                    height: 256
                    width: 256
                    radius: 14
                    BorderImage {
                        id: coverBorder
                        source: "qrc:/music/icon/cover_overlay.png"
                        anchors.fill: parent
                        anchors.margins: 8
                        border { left: 20; top: 20; right: 20; bottom: 20 }
                        horizontalTileMode: BorderImage.Stretch
                        verticalTileMode: BorderImage.Stretch
                        Image {
                            id: coverPic
                            source: songPlayer.metaData.coverArtUrlLarge ?
                                        songPlayer.metaData.coverArtUrlLarge : songButtons.defaultAlbumIcon
                            anchors.fill: coverBorder
                            anchors.margins: 4
                        }
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.leftMargin: 70

                    ScrollableText {
                        id: trackTitle
                        textString: songPlayer.metaData.title ? songPlayer.metaData.title : "No track title"
                        width: 960
                        height: 96
                        textColor: "#eeeeee"
                        duration: 10000
                    }
                    ScrollableText {
                        id: trackAlbum
                        textString: songPlayer.metaData.albumTitle ? songPlayer.metaData.albumTitle : "No album title"
                        width: 960
                        height: 96
                        textColor: "steelblue"
                        duration: 10000
                    }
                }
            }

            RowLayout
            {
                id: lowerWrap
                Layout.fillWidth: true
                Layout.preferredHeight: 80
                Layout.leftMargin: 40
                Layout.rightMargin: 40
                spacing: 30

                Text {
                    id: currentTime
                    text: msToTime(songPlayer.position)
                    font.family: appFont.name
                    color: "#dedede"
                    font.pointSize: 48
                }
                SliderBar {
                    Layout.fillWidth: true
                    audioPlayer: songPlayer
                }
                Text {
                    id: totalTime
                    text: msToTime(songPlayer.duration)
                    font.family: appFont.name
                    color: "#dedede"
                    font.pointSize: 48
                }
            }

        }

        // Command from keyboard
        Item {
            focus: true
            Keys.onPressed: {
                if(event.key === Qt.Key_Left) {
                    prevTrackMouse.clicked(event);
                    prevTrack.state = "pressed";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Right) {
                    nextTrackMouse.clicked(event);
                    nextTrack.state = "pressed";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Up) {
                    volumeUpMouse.clicked(event);
                    volumeUp.state = "pressed";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Down) {
                    volumeDwMouse.clicked(event);
                    volumeDw.state = "pressed";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Return) {
                    playPauseMouse.clicked(event);
                    playPause.state = "pressed";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_1) {
                    replayMouse.clicked(event);
                    replay.state = "pressed";
                    console.log(1)
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_2) {
                    console.log(2)
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_3) {
                    console.log(3)
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_4) {
                    console.log(4)
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Space) {
                    pageStack.pop();
                    event.accepted = true;
                }
                //console.log(event.key)
            }

            Keys.onReleased: {
                if(event.key === Qt.Key_Left) {
                    prevTrack.state = "";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Right) {
                    nextTrack.state = "";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Up) {
                    volumeUp.state = "";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Down) {
                    volumeDw.state = "";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_Return) {
                    playPause.state = "";
                    event.accepted = true;
                }
                else if(event.key === Qt.Key_1) {
                    replay.state = "";
                    event.accepted = true;
                }
                console.log(event.key)
            }
        }
    }
}
