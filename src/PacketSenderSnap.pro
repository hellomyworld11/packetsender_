#  Project file used by snapcraft

QT  += core gui network widgets

DEFINES += "ISSNAP=1"


TARGET = packetsender
TEMPLATE = app
DEFINES += GUI_BUILD

TRANSLATIONS += languages/packetsender_en.ts \
                languages/packetsender_es.ts \
                languages/packetsender_fr.ts \
                languages/packetsender_de.ts \
                languages/packetsender_hi.ts

SOURCES += mainwindow.cpp \
    languagechooser.cpp \
    panel.cpp \
    sendpacketbutton.cpp \
    brucethepoodle.cpp \
    irisandmarigold.cpp \
    persistentconnection.cpp \
    about.cpp \
    subnetcalc.cpp \
    cloudui.cpp \
    multicastsetup.cpp \
    udpflooding.cpp \
    packetlogmodel.cpp \
    postdatagen.cpp \
    panelgenerator.cpp \
    persistenthttp.cpp

HEADERS  += mainwindow.h \
    languagechooser.h \
    panel.h \
    sendpacketbutton.h \
    brucethepoodle.h \
    irisandmarigold.h \
    persistentconnection.h \
    about.h \
    subnetcalc.h \
    cloudui.h \
    multicastsetup.h \
    udpflooding.h \
    packetlogmodel.h \
    postdatagen.h\
    panelgenerator.h \
    persistenthttp.h



FORMS    += mainwindow.ui \
    brucethepoodle.ui \
    irisandmarigold.ui \
    languagechooser.ui \
    persistentconnection.ui \
    settings.ui \
    about.ui \
    subnetcalc.ui \
    cloudui.ui \
        multicastsetup.ui \
    udpflooding.ui \
        persistenthttp.ui \
        postdatagen.ui \
    panelgenerator.ui


include(packetsender_main.pri)

DISTFILES += \
    languages/zh_CN.ts
