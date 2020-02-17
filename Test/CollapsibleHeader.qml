import QtQuick 2.0

Rectangle {
    id: root

    property var container: null
    property string text: "Header"
    property alias textColor: txt.color
    property alias textSize: txt.font.pointSize

    height: 36
    width: 100
    color: "gray"

    Component.onCompleted: {
        priv.checkState();
    }

    Item {
        id: priv

        property string stateText: ">"

        function toggleState() {
            if(container) {
                container.visible = !container.visible;
            }
        }

        function checkState() {
            if(container) {
                if(container.visible) {
                    priv.stateText = "V";
                } else {
                    priv.stateText = ">";
                }
            } else {
                priv.stateText = ">";
            }
        }
    }

    Text {
        id:txt
        text: root.text + "  " + priv.stateText
        color: "white"
        anchors.centerIn: parent
        font.pointSize: 20
    }

    MouseArea {
        width: parent.width
        height: parent.height
        onClicked: {
            priv.toggleState();
            priv.checkState();
        }
    }
}
