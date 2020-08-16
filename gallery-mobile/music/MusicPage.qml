import QtQuick 2.6
import QtQuick.Controls 2.0
import QtMultimedia 5.9
import Qt.labs.folderlistmodel 2.1
import "."

import "QUItMeterComponent"
import "../menu"

PageTheme {
    property string playlistName
    property int playlistIndex
    property int playlistSize

    id: musicPage
    toolbarTitle: playlistName + ": " + playlistSize + " songs"

    //onPlaylistIndexChanged: changePlaylist()

    function changePlaylist() {
        var item = playlistModel.getPlaylistFromIndex(playlistIndex)
        //note: using double ! to check item is not null or undefined (little JavaScript trick)
        if(!!item) {
            playMusic.playlist = item;
            console.log("playlist changed!!");
        }
        else
            console.log("playlist no good!!");
    }

    MediaPlayer {
        id: playMusic
        autoLoad: true
        autoPlay: true
        playlist: Playlist { id:playerList; }
        Component.onCompleted: volumeMeter.initVolume(playMusic);
    }

    Connections {
        target: volumeMeter
        onCurrentVolumeChanged: { meterComponent.value = Math.random();}
    }

    // BackGround
    Rectangle {
        id: background
        anchors.fill: parent
        color: "#232629"

        QUItMeterComponent {
            id: meterComponent
            anchors.fill: parent
            readonly property int intervalTimer: 1000
            _updateFrequencyCounter: (60.0/intervalTimer)*1000;
        }
    }

    // Buttons and sliders
    MusicController {
        id: musicScreen
        songPlayer: playMusic
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 600
    }

    FolderListModel {
        id: folderModel
        showDirs: false
        nameFilters: ["*.mp3", "*.m4a"]
        sortField:FolderListModel.Type
        folder: "file:" + playlistModel.getPlaylistPathFromIndex(playlistIndex)
        onCountChanged: {
            for(var i=0; i<folderModel.count;i++)
            {
                // Aggiungo alla playlist tutte le canzoni presenti al livello attuale
                if(!folderModel.isFolder(i)){
                    playerList.addItem(folderModel.get(i, "fileURL"));
                    console.log(folderModel.get(i, "fileName"));
                }
            }
        }
    }

    /*ListView {
        width: 100; height: 400
        Component {
            id: fileDelegate
            Rectangle {width:100; height: 100; color: "red"; Text { text: fileName }}
        }
        model: folderModel
        delegate: fileDelegate
    }*/
}
