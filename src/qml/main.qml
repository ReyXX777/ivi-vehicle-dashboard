import QtQuick 2.15
import QtQuick.Window 2.15
import "components"

Window {
    id: root
    width: 1280
    height: 480
    visible: true
    title: "QML IVI - Cluster"
    color: "#0A0A0A"

    // Proportional sizing constants
    readonly property real largeGaugeSize: Math.min(root.width * 0.32, root.height * 0.82)
    readonly property real smallGaugeSize: largeGaugeSize * 0.42
    readonly property real gaugeGap: root.width * 0.04

    Item {
        id: clusterLayout
        anchors.centerIn: parent
        width: root.width * 0.92
        height: root.height * 0.92

        Speedometer {
            id: speedo
            width: root.largeGaugeSize
            height: root.largeGaugeSize
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: -root.largeGaugeSize - root.gaugeGap / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -root.height * 0.04
            speed: vehicle.speed
        }

        Tachometer {
            id: tacho
            width: root.largeGaugeSize
            height: root.largeGaugeSize
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: root.gaugeGap / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -root.height * 0.04
            rpm: vehicle.rpm
        }

        FuelGauge {
            id: fuel
            width: root.smallGaugeSize
            height: root.smallGaugeSize
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: root.width * 0.02
            fuelLevel: vehicle.fuelLevel
        }
        TempGauge {
            id: temp
            width: root.smallGaugeSize
            height: root.smallGaugeSize
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: root.width * 0.02
            engineTemp: vehicle.engineTemp
        }
    }
}