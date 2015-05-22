TEMPLATE = lib
TARGET = qvimeoplugin
CONFIG += qt plugin
LIBS += -L../lib -lqvimeo

contains(MEEGO_EDITION,harmattan) {
    CONFIG += link_pkgconfig
    INSTALL_QML_PREFIX = /usr
} else {
    CONFIG += link_prl
    PKGCONFIG = libqvimeo
}

lessThan(QT_MAJOR_VERSION, 5) {
    QT += declarative
} else {
    QT += qml
}

HEADERS += \
    plugin.h

SOURCES += \
    plugin.cpp

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
