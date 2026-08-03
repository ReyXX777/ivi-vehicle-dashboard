import QtQuick 2.15

Item {
    id: root
    width: 200
    height: 200

    property double engineTemp: 90
    property double needleAngle: -120

    onEngineTempChanged: updateNeedle()

    function updateNeedle() {
        var clamped = Math.max(70, Math.min(170, engineTemp))
        needleAngle = -120 + ((clamped - 70) / 100.0) * 240
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/temp/temp_face.svg"
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/temp/temp_needle.svg"
        rotation: needleAngle
        transformOrigin: Item.Center
    }

    CustomImage {
        anchors.fill: parent
        source: "qrc:/Images/temp/temp_case.svg"
    }
}