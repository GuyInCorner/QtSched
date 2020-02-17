#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include <QDir>
#include <QObject>

#include "QtSched.h"
#include "TestContainer.h"


int main(int argc, char *argv[]) {
    QStringList listrrc;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<CQtSched>("ca.sksconsulting.libs.qtsched", 1, 0, "QtSched");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("GlobalHomePath", QDir::homePath());

    CTestContainer testContainer(&engine);

    QString globalTimeStr = "No Time Yet?";
    engine.rootContext()->setContextProperty("GlobalTimeString", globalTimeStr);
    engine.rootContext()->setContextProperty("GlobalTestSchedule", &testContainer);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
