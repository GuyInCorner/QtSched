#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlcontext.h>
#include <QDir>

#include "QtSched.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<CQtSched>("ca.sksconsulting.libs.qtsched", 1, 0, "QtSched");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("GlobalHomePath", QDir::homePath());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
