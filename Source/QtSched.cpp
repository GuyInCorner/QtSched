#include "QtSched.h"

#include <QDebug>
#include <QLoggingCategory>
#include <QTimer>
#include <QDateTime>

static QLoggingCategory loggingCategory("CQtSched");

CQtSched::CQtSched(QObject *_parent) : QObject(_parent) {
    m_updateTimer = new QTimer(this);
    m_updateTimer->setSingleShot(true);
    m_updateTimer->setTimerType(Qt::CoarseTimer);
    QObject::connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_verbose = false;

    m_startHour     = 0;
    m_startMin      = 0;
    m_startSec      = 0;

    m_intHour       = 0;
    m_intMin        = 0;
    m_intSec        = 0;

    m_hasEnd        = false;
    m_endHour       = 0;
    m_endMin        = 0;
    m_endSec        = 0;

    m_enabled       = true;
}

CQtSched::~CQtSched() {
    if(nullptr != m_updateTimer) {
        if(m_updateTimer->isActive()) {
            qCDebug(loggingCategory) << "CQtSched::~CQtSched() Stopping active timer: " << objectName();
            m_updateTimer->stop();
        }
        delete m_updateTimer;
    }
}

bool CQtSched::setScheduleStart(int _startHour, int _startMin, int _startSec) {
    bool rc = true;

    if((m_startHour != _startHour) || (m_startMin != _startMin) || (m_startSec != _startSec)) {
        m_startHour     = _startHour;
        m_startMin      = _startMin;
        m_startSec      = _startSec;
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
        qCDebug(loggingCategory) << "CQtSched::setScheduleStart() Incorrect format: " << _startStr;
    }

    return(rc);
}

QString CQtSched::getScheduleStart() const {
    QString outStr;

    outStr = QString("%1:%2:%3").arg(m_startHour, 2, 10, QChar('0')).arg(m_startMin, 2, 10, QChar('0')).arg(m_startSec, 2, 10, QChar('0'));

    return(outStr);
}

bool CQtSched::setScheduleInterval(int _intHour, int _intMin, int _intSec) {
    bool rc = true;

    if((m_intHour != _intHour) || (m_intMin != _intMin) || (m_intSec != _intSec)) {
        m_intHour       = _intHour;
        m_intMin        = _intMin;
        m_intSec        = _intSec;
        if((m_intHour > 24) || (m_intHour < 0)) {
            m_intHour = 0;
        }
        if((m_intMin > 60) || (m_intMin < 0)) {
            m_intMin = 0;
        }
        if((m_intSec > 60) || (m_intSec < 0)) {
            m_intSec = 0;
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
        qCDebug(loggingCategory) << "CQtSched::setScheduleInterval() Incorrect format: " << _intervalStr;
    }

    return(rc);
}

QString CQtSched::getScheduleInterval() const {
    QString outStr;

    outStr = QString("%1:%2:%3").arg(m_intHour, 2, 10, QChar('0')).arg(m_intMin, 2, 10, QChar('0')).arg(m_intSec, 2, 10, QChar('0'));

    return(outStr);
}

bool CQtSched::setScheduleEnd(int _endHour, int _endMin, int _endSec) {
    bool rc = true;

    if((m_endHour != _endHour) || (m_endMin != _endMin) || (m_endSec != _endSec)) {
        m_hasEnd = true;
        m_endHour     = _endHour;
        m_endMin      = _endMin;
        m_endSec      = _endSec;
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
        qCDebug(loggingCategory) << "CQtSched::setSchedule_endStr() Incorrect format: " << _endStr;
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
    int nowTime = 0;
    int todayTime = 0;
    int startTime = 0;
    int intTime = 0;
    int nextTime = 0;
    int endTime = 0;
    bool wasActive = isActive();

    // not already running.  Calculate how long to wait
    if(false == m_updateTimer->isActive()) {
        // get now time
        nowTime = (int)QDateTime::currentDateTime().toTime_t();

        // get time of start of today
        QDateTime curDate(QDate::currentDate());
        todayTime = (int)curDate.toTime_t();

        // get seconds of start time
        startTime = m_startHour*60*60 + m_startMin*60 + m_startSec;

        // add start time to today time
        // calculate interval time
        intTime = m_intHour*60*60 + m_intMin*60 + m_intSec;

        if(intTime > 0) {
            // next time is start time plus today time
            nextTime = todayTime + startTime;
            while(nextTime <= nowTime) {
                nextTime += intTime;
            }

            // updateInterval time is next time - now time
            intTime = nextTime - nowTime;

            // set enabled to true so that we emit the timeout signal
            m_enabled = true;

            // handle case of schedule only running for part of the day
            if(m_hasEnd) {
                // get seconds of end time
                endTime = m_endHour*60*60 + m_endMin*60 + m_endSec;
                if(startTime > endTime) {
                    // starts today, ends tomorrow
                    endTime += 86400;
                }
                if((nextTime >= (startTime+todayTime)) && (nextTime <= (endTime+todayTime))) {
                    m_enabled = true;
                } else {
                    m_enabled = false;
                }
            }

            // start timer
            m_updateTimer->setInterval(intTime*1000);
            m_updateTimer->start();
            if(m_updateTimer->isActive()) {
                if(m_verbose) qCDebug(loggingCategory) << objectName() << " timer will timeout in " << QString::number(intTime) << " sec";
            } else {
                qCDebug(loggingCategory) << "Error:  Can't start timer: " << objectName();
                rc = false;
            }
        } else {
            qCDebug(loggingCategory) << "Error: Can't start timer: " << objectName() << " Invalid interval";
            rc = false;
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
    m_updateTimer->stop();
}

bool CQtSched::isActive() const {
    return(m_updateTimer->isActive());
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
            qCDebug(loggingCategory) << "CQtSched::onTimeout() name: " << objectName();
        } else {
            qCDebug(loggingCategory) << "CQtSched::onTimeout() name: " << objectName() << " Disabled:  Outside of start and end";
        }
    }

    if(m_enabled) {
        // emit signal to trigger whatever is desired
        emit timeout();
    }

    // restart timer
    start();
}
