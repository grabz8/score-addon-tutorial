import QtQuick 2.0

import QtQuick.Controls 2.1
import QtQuick.Particles 2.0
Rectangle {
    anchors.fill: parent
    color:  "red"
    width: 300
    height: 1000

    Text
    {
        text: "banana"
        font.pointSize: 40
        color: "white"
        x: 100
        y: 100

        RotationAnimation on rotation
        {
            duration: 2048
            from: 0
            to: 360
            loops: Animation.Infinite
        }
    }

    MouseArea {
        id: mouse
        onClicked: {
            pulseEmitter.x = mouseX;
            pulseEmitter.y = mouseY;
            pulseEmitter.pulse(500);
        }
        width: 500
        height: 500
    }

    ParticleSystem {
        id: particles
        anchors.fill: parent

        ImageParticle {
            source: "qrc:///qss_icons/rc/close.png"
            alpha: 0.2
            autoRotation: true
            colorVariation: 0.6
            alphaVariation: 0.4
        }

        Emitter {
            id: pulseEmitter
            x: 200
            y: 200
            emitRate: 1000
            lifeSpan: 2000
            enabled: false
            velocity: AngleDirection{magnitude: 64; angleVariation: 360}
            size: 24
            sizeVariation: 8
        }
    }

}
