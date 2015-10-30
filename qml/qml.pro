TEMPLATE = lib
TARGET = qvimeoplugin
CONFIG += qt plugin
LIBS += -L../lib -lqvimeo

lessThan(QT_MAJOR_VERSION, 5) {
    QT += declarative
} else {
    QT += qml
}

INCLUDEPATH += ../src

HEADERS += \
    plugin.h

SOURCES += \
    plugin.cpp
    
contains(DEFINES,QVIMEO_STATIC_LIBRARY) {
    CONFIG += link_pkgconfig
} else {
    CONFIG += link_prl
    PKGCONFIG = libqvimeo
}

qml.files = qmldir

!isEmpty(INSTALL_QML_PREFIX) {
    qml.path = $$INSTALL_QML_PREFIX/lib/qt4/imports/QVimeo
    target.path = $$INSTALL_QML_PREFIX/lib/qt4/imports/QVimeo
} else:lessThan(QT_MAJOR_VERSION, 5) {
    qml.path = $$[QT_INSTALL_IMPORTS]/QVimeo
    target.path = $$[QT_INSTALL_IMPORTS]/QVimeo
} else {
    qml.path = $$[QT_INSTALL_QML]/QVimeo
    target.path = $$[QT_INSTALL_QML]/QVimeo
}

INSTALLS += qml target
