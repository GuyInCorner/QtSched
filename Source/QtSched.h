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

#ifndef QTSCHED_H
#define QTSCHED_H

#include <QObject>
#include <QTimer>

//
//    A simple realtime scheduler class that allows control of recurring events at specified times.
//    Can be used in C++ or QML.
//
//    Schedule is set in three parts, Start, Interval, End
//    Schedule can run in three ways:
//      Start, Interval, End - Schedule will resume the next time the start time occurs.
//      Start, Interval         - Schedule runs at the prescribed interval as though it started at the start time.  (default is midnight)
//      Interval                - If only an interval is specified then it will run at that interval as though it started at midnight
//    If an end time has been specified and is no longer desired then set the end times to -1:-1:-1 and the end will be removed
//    Default Start is midnight
//    Default end is midnight
//    Default Interval is 0, thereby disabling the timer

//    To use set the schedule then start()

//    Debug messages will reference the schedule by objectName so setting objectName is recommended
//
class CQtSched : public QObject {
    Q_OBJECT

    // When should the schedule start hh:mm:ss
    Q_PROPERTY(QString scheduleStart READ getScheduleStart WRITE setScheduleStart NOTIFY scheduleStartChanged)

    // What is the interval of the schedule hh:mm:ss
    Q_PROPERTY(QString scheduleInterval READ getScheduleInterval WRITE setScheduleInterval NOTIFY scheduleIntervalChanged)

    // When should the schedule End hh:mm:ss
    Q_PROPERTY(QString scheduleEnd READ getScheduleEnd WRITE setScheduleEnd NOTIFY scheduleEndChanged)

    // Monitor if the schedule is active or not.  This is a read only property.  Use stop() to stop it.
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)

    // when true, detailed event data will appear in the debug log
    Q_PROPERTY(bool verbose READ verbose WRITE setVerbose)

public:
    explicit CQtSched(QObject *_parent = nullptr);
    ~CQtSched();

    //
    // Accessors
    //

    // Set start of schedule
    Q_INVOKABLE bool setScheduleStart(int _hour, int _minute, int _second);

    // Set start of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleStart(QString _startStr);

    Q_INVOKABLE QString getScheduleStart() const;

    // Set interval of schedule
    Q_INVOKABLE bool setScheduleInterval(int _hour, int _minute, int _second);

    // Set interval of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleInterval(QString _intervalStr);

    Q_INVOKABLE QString getScheduleInterval() const;

    // Set end of schedule
    Q_INVOKABLE bool setScheduleEnd(int _hour, int _minute, int _second);

    // Set end of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleEnd(QString _endStr);

    Q_INVOKABLE QString getScheduleEnd() const;

    // returns true if it's running or false if not running.
    bool isActive() const;

    void setVerbose(bool _val);
    bool verbose() const;

    //
    // Contol methods
    //

    // Setup schedule start, interval, (and optionally end) times then call start to begin
    Q_INVOKABLE bool start();

    Q_INVOKABLE void stop();

private:

    //
    // helpers
    //


signals:
    // emitted when the event happens.  If you want it as a one-shot them stop() the schedule in the handler
    void timeout();

    void scheduleStartChanged(const QString _startStr);
    void scheduleIntervalChanged(const QString _intervalStr);
    void scheduleEndChanged(const QString _endStr);

    void activeChanged(const bool _isActive);

public slots:

private slots:
    void onTimeout();

private:
    QTimer      *m_nextTimer;

    bool        m_verbose;
    bool        m_enabled;
    bool        m_hasEnd;

    int         m_startHour;
    int         m_startMin;
    int         m_startSec;

    int         m_intervalHour;
    int         m_intervalMin;
    int         m_intervalSec;

    int         m_endHour;
    int         m_endMin;
    int         m_endSec;
};
#endif
