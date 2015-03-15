TEMPLATE = app
TARGET = streams-list
INSTALLS += target

INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lqvimeo
SOURCES += main.cpp

unix {
    target.path = /opt/qvimeo/bin
}
