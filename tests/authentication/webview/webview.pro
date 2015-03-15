TEMPLATE = app
TARGET = authentication-webview
INSTALLS += target

DEFINES += QVIMEO_DEBUG
INCLUDEPATH += ../../../src
LIBS += -L../../../lib -lqvimeo
HEADERS += webview.h
SOURCES += main.cpp webview.cpp

lessThan(QT_MAJOR_VERSION, 5) {
    QT += webkit
} else {
    QT += webkitwidgets
}

unix {
    target.path = /opt/qvimeo/bin
}
