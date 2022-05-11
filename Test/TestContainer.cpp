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
//    qDebug() << "CTestContainer::schedTimeout()";
    if(nullptr != m_engine) {
        m_engine->rootContext()->setContextProperty("GlobalTimeString", QDateTime::currentDateTime().toString());
    }
}
