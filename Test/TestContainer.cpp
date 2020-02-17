#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include <QDir>
#include <QObject>
#include <QDebug>
#include <QDateTime>

#include "TestContainer.h"
#include "QtSched.h"

CTestContainer::CTestContainer(QQmlApplicationEngine *_engine, QObject *_parent) : QObject(_parent) {
    m_engine = _engine;
    m_sched = new CQtSched(this);
    m_sched->setObjectName("schedUpdate");
    // set schedule with start, interval
    m_sched->setScheduleStart(7, 3, 5);
    m_sched->setScheduleInterval(0, 0, 1);
//    m_sched->setVerbose(true);
    m_sched->start();

    QObject::connect(m_sched, &CQtSched::timeout, this, &CTestContainer::schedTimeout);
}

CTestContainer::~CTestContainer() {
}

void CTestContainer::start() {
    m_sched->start();
}

void CTestContainer::stop() {
    m_sched->stop();
}

void CTestContainer::schedTimeout() {
    qDebug() << "CTestContainer::schedTimeout()";
    if(nullptr != m_engine) {
        m_engine->rootContext()->setContextProperty("GlobalTimeString", QDateTime::currentDateTime().toString());
    }
}
