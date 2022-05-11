// *********************************************************************************************************************
//
//    Copyright © 2022 Keith Scott
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//    and associated documentation files (the “Software”), to deal in the Software without restriction,
//    including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
//    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
//    subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all copies or substantial portions
//    of the Software.
//
//    THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
//    TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//    IN THE SOFTWARE.
//
// *********************************************************************************************************************

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
