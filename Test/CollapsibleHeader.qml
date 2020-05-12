import QtQuick 2.12

Rectangle {
    id: rootCollapsibleHeader

    property var container: null
    property string text: "Header"

    property alias textColor: txt.color
    property alias textSize: txt.font.pointSize

    height: 40
    width: 200

    color: "lightgray"

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
        text: rootCollapsibleHeader.text + "  " + priv.stateText
        color: "white"
        anchors.centerIn: parent
        font.pointSize: 18
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: {
            priv.toggleState();
            priv.checkState();
        }
    }
}
