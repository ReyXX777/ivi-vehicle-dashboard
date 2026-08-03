import QtQuick 2.15

Item {
    id: root
    width: 400
    height: 400

    property double speed: 0
    property double needleAngle: -135

    onSpeedChanged: updateNeedle()

    function updateNeedle() {
        var clamped = Math.max(0, Math.min(260, speed))
        needleAngle = -135 + (clamped / 260) * 270
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/speedo/speedo_face.svg"
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/speedo/speedo_needle.svg"
        rotation: needleAngle
        transformOrigin: Item.Center
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/speedo/speedo_case.svg"
    }
}