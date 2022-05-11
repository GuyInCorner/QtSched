# QtSched
A simple realtime scheduler class that allows control of recurring events at specified times.

One short coming of Qt is that it has no way to schedule events in realtime.  QTimer only allows relative event scheduling.  QtSched provides a way to set absolute start, end, and interval times based upon the local time.

It can be used in either C++ or QML

## Building
The project uses Qmake to create a static lib but the source files can be compiled into a Qt project in other ways.  The project comes with a test container that can be built and run in QtCreator.  

## Usage
Schedule is set in three parts, Start, Interval, End

Schedule can run in three ways:
  Start, Interval, End - Schedule will resume the next time the start time occurs.
  Start, Interval         - Schedule runs at the prescribed interval as though it started at the start time.  (default is midnight)
  Interval                - If only an interval is specified then it will run at that interval as though it started at midnight

If an end time has been specified and is no longer desired then set the end times to -1:-1:-1 and the end will be removed

Default Start is midnight

Default end is midnight

Default Interval is 0, thereby disabling the timer

To use, set the schedule then start()

Debug messages will reference the schedule by objectName so setting objectName is recommended.

**Details of the interface can be found in QtSched.h**

# Supported Platforms
This works on Mac and Linux and should work on Windows.
It supports Qt 5.x but has not been ported to Qt 6.

# Licensing
This is released under the MIT license.  Depending how you use it in a Qt application that licensing may change due to GPL and LGPL requirements of Qt.


Copyright © 2022 Keith Scott

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.


