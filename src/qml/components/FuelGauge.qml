import QtQuick 2.15

Item {
    id: root
    width: 200
    height: 200

    property double fuelLevel: 0
    property double needleAngle: -120

    onFuelLevelChanged: updateNeedle()

    function updateNeedle() {
        var clamped = Math.max(0, Math.min(1, fuelLevel))
        needleAngle = -120 + (clamped / 1.0) * 240
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/fuel/fuel_face.svg"
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/fuel/fuel_needle.svg"
        rotation: needleAngle
        transformOrigin: Item.Center
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/fuel/fuel_case.svg"
    }
}