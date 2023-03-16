import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Automobile Dashboard")
    Rectangle {
        id:dashboard
        height:500
        width:900
        color:"black";
        anchors.top : parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        ValueSource {
            id: valueSource

        }
        Row {
            id:dashboardRow
            spacing:dashboard.width * 0.02
            anchors{
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            anchors.centerIn: parent
            Rectangle {
                id:leftindicator
                anchors.verticalCenter: parent.verticalCenter
                height:dashboard.height * 0.2 - dashboardRow.spacing
                width:height
                color: "white"
            }

            CircularGauge {
                id: speedmeter
                value: acceleration ? maximumValue:0

                width: height
                height: dashboard.height * 0.8
                maximumValue: 180
                property bool acceleration: false
                style: SpeedmeterStyle {}

                Behavior on value {
                    NumberAnimation {
                        duration: 9000
                    }
                }
                Component.onCompleted: forceActiveFocus();
            }

            Rectangle {
                id:rightindicator
                anchors.verticalCenter: parent.verticalCenter
                height:dashboard.height * 0.2 - dashboardRow.spacing
                width:height
                color: "white"
            }

        }

        Keys.onUpPressed:{
            speedmeter.acceleration = true
        }
        Keys.onReleased: {
             speedmeter.acceleration = false;
        }
    }

}
