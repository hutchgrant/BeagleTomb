#-------------------------------------------------
#
# Project created by QtCreator 2012-01-24T14:56:37
#
#-------------------------------------------------

QT       += core gui sql

TARGET = beagletomb
TEMPLATE = app
QT += network \
        opengl


SOURCES += src/main.cpp\
    src/beaglemain.cpp \
    src/sync.cpp \
    src/readDB.cpp \
    src/qmpwidget.cpp \
    src/preferences.cpp \
    src/prefdialog.cpp \
    src/mysqlconn.cpp \
    src/mplaycon.cpp \
    src/about.cpp \
    src/playlistobj.cpp \
    src/radioObj.cpp \
    src/fileobj.cpp \
    src/localsync.cpp

HEADERS  += src/beaglemain.h \
    src/sync.h \
    src/readDB.h \
    src/qmpyuvreader.h \
    src/qmpwidget.h \
    src/preferences.h \
    src/prefdialog.h \
    src/mysqlconn.h \
    src/mplaycon.h \
    src/about.h \
    src/playlistobj.h \
    src/sync.h \
    src/readDB.h \
    src/qmpyuvreader.h \
    src/qmpwidget.h \
    src/preferences.h \
    src/prefdialog.h \
    src/playlistobj.h \
    src/mysqlconn.h \
    src/mplaycon.h \
    src/beaglemain.h \
    src/about.h \
    src/radioObj.h \
    src/fileobj.h \
    src/localsync.h

FORMS    += \
    src/prefdialog.ui \
    src/about.ui \
    src/beaglemain.ui

RESOURCES += \
    images/BTres.qrc

documentation.files = docs/*
documentation.path = /opt/extras.ubuntu.com/beagletomb/docs
sources.files = src/*
sources.path = /opt/extras.ubuntu.com/beagletomb/src
target.path = /opt/extras.ubuntu.com/beagletomb
other.files = ./*
other.path = /opt/extras.ubuntu.com/beagletomb/release
INSTALLS += target \
            sources \
            documentation \
            other
