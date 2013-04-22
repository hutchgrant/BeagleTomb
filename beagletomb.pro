#-------------------------------------------------
#
# Project created by QtCreator 2012-05-07T21:07:53
#
#-------------------------------------------------

QT       += core gui sql

TARGET = beagletomb
TEMPLATE = app
QT += network \
        opengl

SOURCES += \
    src/qmpwidget.cpp \
    src/playlist.cpp \
    src/main.cpp \
    src/localsync.cpp \
    src/fileobj.cpp \
    src/controls.cpp \
    src/browse.cpp \
    src/beaglemain.cpp \
    src/prefdialog.cpp \
    src/about.cpp \
    src/volume.cpp \
    src/dbconnect.cpp \
    src/newplaylist.cpp \
    src/prefobj.cpp \
    src/remotesync.cpp

HEADERS  += \
    src/qmpyuvreader.h \
    src/qmpwidget.h \
    src/playlist.h \
    src/localsync.h \
    src/fileobj.h \
    src/controls.h \
    src/browse.h \
    src/beaglemain.h \
    src/prefdialog.h \
    src/about.h \
    src/volume.h \
    src/dbconnect.h \
    src/newplaylist.h \
    src/prefobj.h \
    src/remotesync.h

FORMS    += \
    src/playlist.ui \
    src/controls.ui \
    src/browse.ui \
    src/beaglemain.ui \
    src/prefdialog.ui \
    src/about.ui \
    src/volume.ui \
    src/newplaylist.ui

OTHER_FILES += \
    qmpwidget.pri \
    src/qmpwidget.pri \
    res/UP_icon.png \
    res/STOP_icon.png \
    res/RWD_icon.png \
    res/RRWD_icon.png \
    res/RPT_icon.png \
    res/PAUSE_icon.png \
    res/FWD_icon.png \
    res/FFWD_icon.png \
    res/DOWN_icon.png \
    res/beagletomb_icon.png \
    res/REMOVE_icon.png \
    res/OPEN_icon.png \
    res/ADD_icon.png

RESOURCES += \
    res/BTres.qrc

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
