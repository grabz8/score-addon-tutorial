import QtQuick 2.0

import QtQuick.Controls 2.1
Rectangle {
    anchors.fill: parent
    color:  "cyan"
    width: 300
    height: 1000
    Column {
        Item {
            height: txt.height
            width: txt.width
            ShaderEffect
            {
                height: txt.height
                width: txt.width
                property real rot: txt.rotation / 360
                fragmentShader: "
            uniform float rot;
            void main(void)
            {
              gl_FragColor = vec4(rot, 0.3, 0.4, 1.);
            }"
            }
            Text
            {
                id:txt

                text: "foo"
                font.pointSize: 40

                RotationAnimation on rotation
                {
                    duration: 2048
                    from: 0
                    to: 360
                    loops: Animation.Infinite
                }
            }
        }

        TextArea {
            text: "some editable text\nhello"
        }

        Slider {

        }

        Dial
        {
            width: 50
            height: 50

        }

        CheckBox {
        }

        ComboBox {
            model: ["num1", "num2", "num3"]
        }

        RadioButton {
        }
        SpinBox {
        }

        Label {
            text: " a label "
            font.family: "Ubuntu"
        }
        Button {
            text : " a button"
            font.family: "Ubuntu"
        }
    }


}
