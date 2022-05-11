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

#include "QtSched.h"

#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QLoggingCategory>

static QLoggingCategory loggingCategory("CQtSched");

CQtSched::CQtSched(QObject *_parent) : QObject(_parent) {
    m_verbose = false;

    m_nextTimer = new QTimer(this);
    m_nextTimer->setTimerType(Qt::CoarseTimer);
    m_nextTimer->setSingleShot(true);
    QObject::connect(m_nextTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    m_enabled       = true;
    m_hasEnd        = false;

    m_startHour     = 0;
    m_startMin      = 0;
    m_startSec      = 0;

    m_endHour       = 0;
    m_endMin        = 0;
    m_endSec        = 0;

    m_intervalHour       = 0;
    m_intervalMin        = 0;
    m_intervalSec        = 0;
}

CQtSched::~CQtSched() {
    if(nullptr != m_nextTimer) {
        if(m_nextTimer->isActive()) {
            qCDebug(loggingCategory) << "CQtSched::~CQtSched() Stopping active schedule: " << objectName();
            m_nextTimer->stop();
        }
        delete m_nextTimer;
    }
}

bool CQtSched::setScheduleStart(int _hour, int _minute, int _second) {
    bool rc = true;

    if((m_startHour != _hour) || (m_startMin != _minute) || (m_startSec != _second)) {
        m_startHour     = _hour;
        m_startMin      = _minute;
        m_startSec      = _second;

        if((m_startHour > 23) || (m_startHour < 0)) {
            m_startHour = 0;
        }
        if((m_startMin > 59) || (m_startMin < 0)) {
            m_startMin = 0;
        }
        if((m_startSec > 59) || (m_startSec < 0)) {
            m_startSec = 0;
        }

        emit scheduleStartChanged(getScheduleStart());
    }

    return(rc);
}

bool CQtSched::setScheduleStart(QString _startStr) {
    bool rc = false;
    int numHour = 0;
    int numMin = 0;
    int numSec = 0;
    QStringList parts;

    parts = _startStr.split(":");

    if(3 == parts.length()) {
        rc = true;
    }

    if(rc) {
        numHour = parts[0].toInt(&rc);
    }
    if(rc) {
        numMin = parts[1].toInt(&rc);
    }
    if(rc) {
        numSec = parts[2].toInt(&rc);
    }

    if(rc) {
        setScheduleStart(numHour, numMin, numSec);
    } else {
        qCDebug(loggingCategory) << "CQtSched::setScheduleStart() schedule: " << objectName() << " Incorrect format: " << _startStr;
    }

    return(rc);
}

QString CQtSched::getScheduleStart() const {
    QString outStr;

    outStr = QString("%1:%2:%3").arg(m_startHour, 2, 10, QChar('0')).arg(m_startMin, 2, 10, QChar('0')).arg(m_startSec, 2, 10, QChar('0'));

    return(outStr);
}

bool CQtSched::setScheduleInterval(int _hour, int _minute, int _second) {
    bool rc = true;

    if((m_intervalHour != _hour) || (m_intervalMin != _minute) || (m_intervalSec != _second)) {
        m_intervalHour       = _hour;
        m_intervalMin        = _minute;
        m_intervalSec        = _second;

        if((m_intervalHour > 24) || (m_intervalHour < 0)) {
            m_intervalHour = 0;
        }
        if((m_intervalMin > 60) || (m_intervalMin < 0)) {
            m_intervalMin = 0;
        }
        if((m_intervalSec > 60) || (m_intervalSec < 0)) {
            m_intervalSec = 0;
        }

        emit scheduleIntervalChanged(getScheduleInterval());
    }

    return(rc);
}

bool CQtSched::setScheduleInterval(QString _intervalStr) {
    bool rc = false;
    int numHour = 0;
    int numMin = 0;
    int numSec = 0;
    QStringList parts;

    parts = _intervalStr.split(":");

    if(3 == parts.length()) {
        rc = true;
    }

    if(rc) {
        numHour = parts[0].toInt(&rc);
    }
    if(rc) {
        numMin = parts[1].toInt(&rc);
    }
    if(rc) {
        numSec = parts[2].toInt(&rc);
    }

    if(rc) {
        setScheduleInterval(numHour, numMin, numSec);
    } else {
        qCDebug(loggingCategory) << "CQtSched::setScheduleInterval() schedule: " << objectName() << " Incorrect format: " << _intervalStr;
    }

    return(rc);
}

QString CQtSched::getScheduleInterval() const {
    QString outStr;

    outStr = QString("%1:%2:%3").arg(m_intervalHour, 2, 10, QChar('0')).arg(m_intervalMin, 2, 10, QChar('0')).arg(m_intervalSec, 2, 10, QChar('0'));

    return(outStr);
}

bool CQtSched::setScheduleEnd(int _hour, int _minute, int _second) {
    bool rc = true;

    if((m_endHour != _hour) || (m_endMin != _minute) || (m_endSec != _second)) {
        m_hasEnd = true;
        m_endHour     = _hour;
        m_endMin      = _minute;
        m_endSec      = _second;

        if((m_endHour > 23) || (m_endHour < 0)) {
            m_hasEnd = false;
            m_endHour = 0;
        }
        if((m_endMin > 59) || (m_endMin < 0)) {
            m_hasEnd = false;
            m_endMin = 0;
        }
        if((m_endSec > 59) || (m_endSec < 0)) {
            m_hasEnd = false;
            m_endSec = 0;
        }

        emit scheduleEndChanged(getScheduleEnd());
    }

    return(rc);
}

bool CQtSched::setScheduleEnd(QString _endStr) {
    bool rc = false;
    int numHour = 0;
    int numMin = 0;
    int numSec = 0;
    QStringList parts;

    parts = _endStr.split(":");

    if(3 == parts.length()) {
        rc = true;
    }

    if(rc) {
        numHour = parts[0].toInt(&rc);
    }
    if(rc) {
        numMin = parts[1].toInt(&rc);
    }
    if(rc) {
        numSec = parts[2].toInt(&rc);
    }

    if(rc) {
        setScheduleEnd(numHour, numMin, numSec);
    } else {
        qCDebug(loggingCategory) << "CQtSched::setSchedule_endStr() schedule: " << objectName() << " Incorrect format: " << _endStr;
    }

    return(rc);
}

QString CQtSched::getScheduleEnd() const {
    QString outStr;

    outStr = QString("%1:%2:%3").arg(m_endHour, 2, 10, QChar('0')).arg(m_endMin, 2, 10, QChar('0')).arg(m_endSec, 2, 10, QChar('0'));

    return(outStr);
}

bool CQtSched::start() {
    bool rc = true;
    int tsStart = 0;
    int tsInterval = 0;
    int tsEnd = 0;
    int tsCurrent = 0;
    int tsToday = 0;
    int tsNext = 0;
    bool wasActive = isActive();

    // If we're not running, calculate the next event timestamp
    if(false == wasActive) {
        tsCurrent = (int)QDateTime::currentDateTime().toTime_t();

        //QDateTime curDate(QDate::currentDate());  // works well but being depricated
        //QDateTime curDate(QDate().startOfDay());  // slow

        // reasonably quick method to replace the depticated one but requires more fiddling
        QDateTime curDate = QDateTime::currentDateTime();
        QTime t;
        t.setHMS(0,0,0);
        curDate.setTime(t);
        //qDebug() << "QDateTime curDate(QDate::currentDate()) " << curDate.toString();

        tsToday = (int)curDate.toTime_t();
        tsStart = (m_startHour * 3600) + (m_startMin * 60) + m_startSec;
        tsInterval = (m_intervalHour * 3600) + (m_intervalMin * 60) + m_intervalSec;

        if(tsInterval > 0) {
            // advance the next timestamp until it's ahead of the current timestamp
            tsNext = tsToday + tsStart;
            while(tsNext <= tsCurrent) {
                tsNext += tsInterval;
            }

            // calculate how long away that is
            tsInterval = tsNext - tsCurrent;

            if(m_hasEnd) {
                // An end time means the schedule is only running for part of the day
                tsEnd = (m_endHour * 3600) + (m_endMin * 60) + m_endSec;
                if(tsEnd < tsStart) {
                    // special case of schecule starting today but ending tomorrow so add a day
                    tsEnd += 86400;
                }
                if((tsNext <= (tsEnd+tsToday)) && (tsNext >= (tsStart+tsToday))) {
                    // We're outside of the time range during which the schedule is running (between end and star) so disable the event
                    m_enabled = true;
                } else {
                    m_enabled = false;
                }
            } else {
                // No end time so enable the firing of the event
                m_enabled = true;
            }

            m_nextTimer->setInterval(tsInterval * 1000);
            m_nextTimer->start();

            rc = m_nextTimer->isActive();
            if(rc) {
                if(m_verbose) qCDebug(loggingCategory) << "schedule: " << objectName() << " timer will timeout in " << QString::number(tsInterval) << " sec";
            } else {
                qCDebug(loggingCategory) << "Error:  Failed start schedule: " << objectName();
            }
        } else {
            qCDebug(loggingCategory) << "Error: Invalid interval. Can't start schedule: " << objectName();
        }
    }

    if(wasActive != isActive()) {
        if(m_verbose) qDebug() << objectName() << ".emit activeChanged(" << isActive() << ")";
        emit activeChanged(isActive());
    }

    return(rc);
}


void CQtSched::stop() {
    if(isActive()) {
        if(m_verbose) qDebug() << objectName() << ".emit activeChanged(false)";
        emit activeChanged(false);
    }
    m_nextTimer->stop();
}

bool CQtSched::isActive() const {
    return(m_nextTimer->isActive());
}

void CQtSched::setVerbose(bool _val) {
    m_verbose = _val;
}

bool CQtSched::verbose() const {
    return(m_verbose);
}

void CQtSched::onTimeout() {
    if(m_verbose) {
        if(m_enabled) {
            qCDebug(loggingCategory) << "CQtSched::onTimeout() schedule: " << objectName();
        } else {
            qCDebug(loggingCategory) << "CQtSched::onTimeout() schedule: " << objectName() << " Disabled:  Event is outside of start and end time";
        }
    }

    if(m_enabled) {
        // emit signal to trigger whatever is desired
        emit timeout();
    }

    // restart timer
    start();
}
