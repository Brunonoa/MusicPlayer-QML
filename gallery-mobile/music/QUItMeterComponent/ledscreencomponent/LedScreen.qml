import QtQuick 2.0

Item {
    id: root
    // QML content used as a source
    property alias sourceItem: effectSource.sourceItem
    // Size of one led, in pixels
    property real ledWidth: 64
    property real ledHeight: 32
    // Color of a led, default yellow
    property color ledColor: Qt.rgba(1.0, 1.0, 0.0, 1.0);
    // Set this true to use colors from sourceItem instead of ledColor
    property bool useSourceColors: false
    // Amount of opacity required to switch a led on
    property real threshold: 0.5

    ShaderEffectSource {
        id: effectSource
        hideSource: true
        smooth: false
    }

    ShaderEffect {
        id: effectItem
        width: screenWidth * root.ledWidth
        height: screenHeight * root.ledHeight
        anchors.centerIn: parent
        smooth: false

        property real screenWidth: Math.floor(root.width / root.ledWidth)
        property real screenHeight: Math.floor(root.height / root.ledHeight)
        property var source: effectSource
        property var sledOn: Image { source: "images/led_on2.png"; sourceSize.width: root.ledWidth; sourceSize.height: root.ledHeight; visible: false }
        property var sledOff: Image { source: "images/led_off2.png"; sourceSize.width: root.ledWidth; sourceSize.height: root.ledHeight; visible: false }
        property point screenSize: Qt.point(screenWidth, screenHeight)
        property alias ledColor: root.ledColor
        property real useSourceColors: root.useSourceColors ? 1.0 : 0.0
        property alias threshold: root.threshold

        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform lowp float qt_Opacity;
            uniform sampler2D source;
            uniform sampler2D sledOn;
            uniform sampler2D sledOff;
            uniform highp vec2 screenSize;
            uniform highp vec4 ledColor;
            uniform lowp float useSourceColors;
            uniform lowp float threshold;

            void main() {
                highp vec2 cpos = (floor(qt_TexCoord0 * screenSize) + 0.5) / screenSize;
                highp vec4 tex = texture2D(source, cpos);
                highp vec2 lpos = fract(qt_TexCoord0 * screenSize);
                lowp float isOn = step(threshold, tex.r);
                highp vec4 pix = mix(texture2D(sledOff, lpos), texture2D(sledOn, lpos), isOn);
                highp vec4 color = mix(ledColor, tex, isOn * useSourceColors);
                gl_FragColor = pix * color * qt_Opacity;
            }"
    }
}
