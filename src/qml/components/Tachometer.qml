import QtQuick 2.15

Item {
    id: root
    width: 400
    height: 400

    property double rpm: 0
    property double needleAngle: -140

    onRpmChanged: updateNeedle()

    function updateNeedle() {
        var clamped = Math.max(0, Math.min(7000, rpm))
        needleAngle = -140 + (clamped / 7000) * 260
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/tacho/tacho_face.svg"
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/tacho/tacho_needle.svg"
        rotation: needleAngle
        transformOrigin: Item.Center
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/speedo/speedo_case.svg"
    }
}