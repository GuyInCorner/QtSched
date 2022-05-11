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

