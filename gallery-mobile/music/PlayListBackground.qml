import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Particles 2.0
import "."

Item {
    Image {
        anchors.fill: parent
        //fillMode: Image.PreserveAspectFit
        source: "qrc:/music/image/music6.jpg"
    }

    ParticleSystem {
        id: particleSystem
    }

    Emitter {
        id: emitter
        anchors.fill: parent
        system: particleSystem
        emitRate: 20
        lifeSpan: 2000
        lifeSpanVariation: 500
        size: 32
        endSize: 64
        velocity: AngleDirection {
            angle: 90
            angleVariation: 0
            magnitude: 100
            magnitudeVariation: 50
        }
    }

    ImageParticle {
        source: "qrc:/music/icon/notes1.png"
        system: particleSystem
        rotation: 0
        rotationVariation: 15
        rotationVelocity: 5
        rotationVelocityVariation: 5
        entryEffect: ImageParticle.Scale
    }
}
