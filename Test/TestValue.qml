import QtQuick 2.12

Rectangle {
    id: rootTestValue

    property alias readOnly: inp.readOnly

    property string label: "Label"
    property alias labelColor: txt.color
    property real labelWidthFactor: 0.25;

    property alias valueColor: inp.color
    property real valueWidthFactor: 0.75;
    property alias value: inp.text

    signal accepted(string _value);

    height: 30
    width: 380
    border.width: 1
    border.color: "darkgray"

    Text {
        id:txt
        text: rootTestValue.label + ":"
        color: "black"
        width: parent.width * rootTestValue.labelWidthFactor;
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 5
        font.pointSize: 16
    }

    TextInput {
        id: inp
        width: parent.width * rootTestValue.valueWidthFactor;
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 5
        font.pointSize: 16
        selectByMouse: true

        cursorVisible: true

        onAccepted: {
            rootTestValue.accepted(rootTestValue.value);
        }
    }
}

