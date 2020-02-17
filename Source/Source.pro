QT += qml quick

TARGET = QtSched
TEMPLATE = lib

# this is being built as a static library.  It could be built as a dynamic library and brought in using the Qt plugin architrcutre.
CONFIG += staticlib
CONFIG += debug_and_release

# build to the lib dir where we use it
DESTDIR = ../../lib/debug

DEFINES += QT_DEPRECATED_WARNINGS

# add the common include directory to the include path
INCLUDEPATH += $$PWD/../../include

SOURCES += main.cpp
SOURCES += QtSched.cpp

HEADERS += QtSched.h

# This pulls in the qml components when there are any
#RESOURCES += QtSched.qrc

# Release the include files to the common include directory
incfiles.path = $$INCLUDEPATH
incfiles.files += QtSched.h
COPIES += incfiles

# Any qml can be compiled into an rcc file and copy to the common resources directory where it can be optionally distributed and imported by other projects
#QMAKE_POST_LINK += $$quote(${QMLBINDIR}/rcc -binary $$PWD/./${QMAKE_TARGET}.qrc -o $$PWD/../../resources/${QMAKE_TARGET}.rcc$$escape_expand(\n\t))
