import QtQuick 2.0
import "ledscreencomponent"

Item {
    id: root

    // Current value 0...1
    property real value: 0.5
    // Width and height of individual leds
    property alias ledWidth: ledScreen.ledWidth
    property alias ledHeight: ledScreen.ledHeight
    // How frequently ledscreen progresses, 60fps/updateFrequency
    property int updateFrequency: 5;
    // *** private ***
    property int _updateFrequencyCounter: 0;
    property real _peakValue: root.value

    onValueChanged: {
        root.value = Math.min(1.0, root.value)
        root._peakValue = Math.max(root._peakValue, root.value);
    }

    width: 400
    height: 300

    LedScreen {
        id: ledScreen
        anchors.fill: parent
        sourceItem: inputItem
        useSourceColors: true
        ledColor: Qt.rgba(0.4, 0.4, 0.4, 0.2)
        threshold: 0.01
        ledWidth: 32
        ledHeight: 24
    }

    // This area is the source, one pixel is one led
    Rectangle {
        id: sourceArea
        width: Math.floor(root.width / ledScreen.ledWidth)
        height: Math.floor(root.height / ledScreen.ledHeight)
        color:"#000000"
        visible: false

        Image {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: 1
            height: parent.height*root.value
            source: "images/eqline.png"
            smooth: false
        }

        Rectangle {
            anchors.right: parent.right
            color: "#ffffff"
            width: 1
            height: 1
            y: Math.floor(parent.height * (1 - root._peakValue))
        }
    }

    ShaderEffect {
        id: inputItem
        property variant source: ShaderEffectSource { sourceItem: sourceArea; smooth: false }
        property variant recursiveSource: recursiveSource
        property real ledWidthPercent: ledScreen.ledWidth/ledScreen.width
        anchors.fill: sourceArea
        visible: false

        fragmentShader: "
            varying mediump vec2 qt_TexCoord0;
            uniform highp float qt_Opacity;
            uniform highp float ledWidthPercent;
            uniform lowp sampler2D source;
            uniform lowp sampler2D recursiveSource;
            void main() {
                highp vec4 pix;
                if (qt_TexCoord0.x > (1.0 - ledWidthPercent)) {
                    pix = texture2D(source, qt_TexCoord0);
                } else {
                    highp vec2 pos = vec2(qt_TexCoord0.x+ledWidthPercent, qt_TexCoord0.y);
                    pix = texture2D(recursiveSource, pos) * (1.0-ledWidthPercent*2.0);
                }
                gl_FragColor = pix * qt_Opacity;
            }
        "
    }

    ShaderEffectSource {
        id: recursiveSource
        sourceItem: inputItem
        hideSource: true
        visible: false
        live: root.updateFrequency == 1//false
        recursive: true
        smooth: false
    }

    // Dummy element for syncing updates
    Item {
        id: dummyItem
        NumberAnimation on rotation {
            from:0
            to: 360
            duration: 1000
            loops: Animation.Infinite
        }
        onRotationChanged: {
            root._updateFrequencyCounter++;
            if (root._updateFrequencyCounter == 1) {
                // Reduce peak in first iteratio after repaint
                var reduced_peakValue = root._peakValue - (root._peakValue - root.value)/2;
                root._peakValue = Math.max(root.value, reduced_peakValue);
            }
            if (root._updateFrequencyCounter >= root.updateFrequency) {
                recursiveSource.scheduleUpdate();
                root._updateFrequencyCounter = 0;
            }
        }
    }
}
