TEMPLATE = lib

#DEFINES += QVIMEO_DEBUG

#unix:INSTALL_SRC_PREFIX = /opt

QT += network
QT -= gui

TARGET = qvimeo
DESTDIR = ../lib

contains(MEEGO_EDITION,harmattan) {
    CONFIG += staticlib
    DEFINES += QVIMEO_STATIC_LIBRARY
} else {
    CONFIG += create_prl
    DEFINES += QVIMEO_LIBRARY
}

HEADERS += \
    authenticationrequest.h \
    json.h \
    model.h \
    model_p.h \
    request.h \
    request_p.h \
    resourcesmodel.h \
    resourcesrequest.h \
    streamsmodel.h \
    streamsrequest.h \
    urls.h

SOURCES += \
    authenticationrequest.cpp \
    json.cpp \
    model.cpp \
    request.cpp \
    resourcesmodel.cpp \
    resourcesrequest.cpp \
    streamsmodel.cpp \
    streamsrequest.cpp
    
headers.files += \
    authenticationrequest.h \
    model.h \
    request.h \
    resourcesmodel.h \
    resourcesrequest.h \
    streamsmodel.h \
    urls.h

!isEmpty(INSTALL_SRC_PREFIX) {
    target.path = $$INSTALL_SRC_PREFIX/lib
    headers.path = $$INSTALL_SRC_PREFIX/include/qvimeo
} else {
    target.path = /usr/lib
    headers.path = /usr/include/qvimeo
}

INSTALLS += target headers
