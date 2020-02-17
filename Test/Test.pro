QT += core gui qml quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

defined(RELEASE, var) {
    equals(RELEASE, 1) {
        CONFIG += release
        message("Building for release");
    }
} else {
    defined(DEBUG, var) {
        equals(DEBUG, 1) {
            CONFIG += debug
            message("Building for debug");
        }
    }
}

# Common library include path
INCLUDEPATH += $$PWD/../../include

SOURCES += main.cpp
SOURCES += TestContainer.cpp

HEADERS += TestContainer.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/../../plugins
QML_IMPORT_PATH += $$PWD/../../resources

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

# Here we are compiling in the static QtSched library.  It could be built as a shared library and loaded as a plugin at runtime instead.
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/release/ -lQtSched
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/debug/ -lQtSched
else:unix: LIBS += -L$$OUT_PWD/../../lib/debug/ -lQtSched

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/release/libQtSched.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/debug/libQtSched.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/release/QtSched.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/debug/QtSched.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/debug/libQtSched.a
