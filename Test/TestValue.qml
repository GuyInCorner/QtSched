import QtQuick 2.0

Rectangle {
    id: root

    property alias readOnly: inp.readOnly
    property alias label: txt.text
    property alias labelColor: txt.color
    property alias labelSize: txt.font.pointSize
    property alias labelWidth: txt.width
    property alias valueColor: inp.color
    property alias valueSize: inp.font.pointSize
    property alias valueWidth: inp.width
    property alias value: inp.text

    signal accepted();

    height: 32
    width: 400
    border.width: 1
    border.color: "black"

    Text {
        id:txt
        text: "Label"
        color: "black"
        width: parent.width/4
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 5
        font.pointSize: 16
    }

    TextInput {
        id: inp
        width: parent.width/4*3
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 5
        font.pointSize: 16
        selectByMouse: true

        cursorVisible: true

        onAccepted: {
            root.accepted();
        }
    }
}

