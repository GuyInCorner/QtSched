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

import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11
import QtQuick.Controls 2.4

import ca.sksconsulting.libs.qtsched 1.0

Window {
    visible: true
    width: 1000
    height: 800
    title: qsTr("QtSched Test")
    id: mainWindow


    ColumnLayout {
        id: colPanels
        spacing: 5
        Layout.fillHeight: true


        //
        // QtSched test
        //
        CollapsibleHeader {
            id: hdrschedTest
            text: "Sched Test"
            Layout.preferredWidth: mainWindow.width
            container: ccSchedTest
        }

        CollapsibleContainer {
            id: ccSchedTest
            visible: true
            Layout.preferredWidth: mainWindow.width

            Rectangle {
                id: rectSchedTest
                width: parent.width
                height: 60

                color: "darkgray"

                Component.onCompleted: {
                    if(ccSchedTest.visible) {
                        GlobalTestSchedule.start();
                    } else {
                        GlobalTestSchedule.stop();
                    }
                }

                QtSched {
                    id: schedColor
                    objectName: "schedColor"
                    scheduleStart: "07:13:50"
                    scheduleInterval: "00:00:05"
                    scheduleEnd: "16:42:00"

                    // we have to start it once the schedule is set
                    Component.onCompleted: {
                        if(ccSchedTest.visible) {
                            schedColor.start();
                            GlobalTestSchedule.start();
                            swColorSchedStartStop.checked = true;
                        }
                    }

                    // setting verbose will cause extra log messages for debugging
                    verbose: true

                    onActiveChanged: {
                        console.log(objectName + ".active: " + schedColor.active);
                    }
                }

                Connections {
                    target: schedColor
                    onTimeout: {
                        console.log(schedColor.objectName + "::onTimeout() " + txtSchedTest.color);
                        if("#000000" == txtSchedTest.color) {
                            txtSchedTest.color = "green";
                        } else {
                            txtSchedTest.color = "black";
                        }
                    }
                }

                Connections {
                    target: ccSchedTest
                    onVisibleChanged: {
                        if(ccSchedTest.visible) {
                            schedColor.start();
                            GlobalTestSchedule.start();
                            swColorSchedStartStop.checked = true;
                        } else {
                            schedColor.stop();
                            GlobalTestSchedule.stop();
                            swColorSchedStartStop.checked = false;
                        }
                    }
                }

                Text {
                    id: lblSchedTest
                    text: "Should change color every " + (parseInt(schedColor.scheduleInterval.split(":")[0]*60*60) + parseInt(schedColor.scheduleInterval.split(":")[1]*60) + parseInt(schedColor.scheduleInterval.split(":")[2])) + " sec:"
                    anchors.top: rectSchedTest.top
                    anchors.margins: 10
                    color: "black"
                }

                Text {
                    id: txtSchedTest
                    text: GlobalTimeString
                    anchors.left: lblSchedTest.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: lblSchedTest.verticalCenter
                    color: "black"
                }

                Text {
                    id: lblSchedText
                    text: "Color Schedule: " + schedColor.scheduleStart + " " + schedColor.scheduleInterval + " " + schedColor.scheduleEnd
                    anchors.topMargin: 5
                    anchors.top: lblSchedTest.bottom
                    color: "black"
                }

                Text {
                    id: lblColorSchedStartStop
                    text: "Color Schedule Control"
                    anchors.topMargin: 5
                    anchors.top: lblSchedText.bottom
                    anchors.left: lblSchedText.left
                }
                Switch {
                    id: swColorSchedStartStop
                    anchors.top: lblSchedText.bottom
                    anchors.left: lblColorSchedStartStop.right
                    anchors.verticalCenter: lblColorSchedStartStop.verticalCenter

                    onCheckedChanged: {
                        if(checked) {
                            schedColor.start();
                        } else {
                            schedColor.stop();
                        }
                    }
                }

                TestValue {
                    id: valStart
                    anchors.topMargin: 5
                    anchors.top: swColorSchedStartStop.bottom
                    label: "Start"

                    Component.onCompleted: {
                        value = schedColor.getScheduleStart();
                    }

                    onAccepted: {
                        schedColor.setScheduleStart(value);
                    }
                }

                TestValue {
                    id: valInterval
                    anchors.topMargin: 5
                    anchors.top: valStart.bottom
                    label: "Interval"

                    Component.onCompleted: {
                        value = schedColor.getScheduleInterval();
                    }

                    onAccepted: {
                        schedColor.setScheduleInterval(value);
                    }
                }

                TestValue {
                    id: valEnd
                    anchors.topMargin: 5
                    anchors.top: valInterval.bottom
                    label: "End"

                    Component.onCompleted: {
                        value = schedColor.getScheduleEnd();
                    }

                    onAccepted: {
                        schedColor.setScheduleEnd(value);
                    }
                }

            } // end of QtSched test
        } // end of ccSchedTest

    } // end of ccPanels

} // end of mainWindow
