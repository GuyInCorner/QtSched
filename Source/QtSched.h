#ifndef QTSCHED_H
#define QTSCHED_H

#include <QObject>
#include <QTimer>


//
// A simple realtime scheduler class that allows control of recurring events at specified times.
// Can be used in C++ or QML.
//
// Schedule is set in three parts, Start, Interval, End
// Schedule can run in three ways:
//      Start, Interval, End - Schedule will resume the next time the start time occurs.
//      Start, Interval         - Schedule runs at the prescribed interval as though it started at the start time.  (default is midnight)
//      Interval                - If only an interval is specified then it will run at that interval as though it started at midnight
// If an end time has been specified and is no longer desired then set the end times to -1:-1:-1 and the end will be removed
// Default Start is midnight
// Default end is midnight
// Default Interval is 0, thereby disabling the timer
//
// To use set the schedule then start()
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

    // turn on event logging
    Q_PROPERTY(bool verbose READ verbose WRITE setVerbose)

public:
    explicit CQtSched(QObject *_parent = nullptr);
    ~CQtSched();

    //
    // Accessors
    //

    // Set start of schedule
    Q_INVOKABLE bool setScheduleStart(int _startHour, int _startMin, int _startSec);

    // Set start of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleStart(QString _startStr);

    Q_INVOKABLE QString getScheduleStart() const;

    // Set interval of schedule
    Q_INVOKABLE bool setScheduleInterval(int _intHour, int _intMin, int _intSec);

    // Set interval of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleInterval(QString _intervalStr);

    Q_INVOKABLE QString getScheduleInterval() const;

    // Set end of schedule
    Q_INVOKABLE bool setScheduleEnd(int _endHour, int _endMin, int _endSec);

    // Set end of schedule as a string hh:mm:ss
    Q_INVOKABLE bool setScheduleEnd(QString _endStr);

    Q_INVOKABLE QString getScheduleEnd() const;

    // returns true if it's running or false if not running.
    Q_INVOKABLE bool isActive() const;

    void setVerbose(bool _val);
    bool verbose() const;

    //
    // Contol methods
    //

    // call start after setting up the schedule
    Q_INVOKABLE bool start();

    // call stop to pause it and start to resume again
    Q_INVOKABLE void stop();


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
    QTimer      *m_updateTimer;
    bool        m_verbose;

    int         m_startHour;
    int         m_startMin;
    int         m_startSec;

    int         m_intHour;
    int         m_intMin;
    int         m_intSec;

    bool        m_hasEnd;
    int         m_endHour;
    int         m_endMin;
    int         m_endSec;

    bool        m_enabled;      // false if we're between the end time and next start time
};

#endif // PVHAPP_H
