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
    src/newplaylist.cpp \
    src/playlistobj.cpp \
    src/openplaylist.cpp \
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
    src/newplaylist.h \
    src/playlistobj.h \
    src/sync.h \
    src/readDB.h \
    src/qmpyuvreader.h \
    src/qmpwidget.h \
    src/preferences.h \
    src/prefdialog.h \
    src/playlistobj.h \
    src/newplaylist.h \
    src/mysqlconn.h \
    src/mplaycon.h \
    src/beaglemain.h \
    src/about.h \
    src/openplaylist.h \
    src/radioObj.h \
    src/fileobj.h \
    src/localsync.h

FORMS    += \
    src/prefdialog.ui \
    src/about.ui \
    src/newplaylist.ui \
    src/beaglemain.ui \
    src/openplaylist.ui

RESOURCES += \
    images/BTres.qrc
