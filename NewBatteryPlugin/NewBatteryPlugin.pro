CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpnewbatteryplugin)
TEMPLATE    = lib

HEADERS     = tpnewbatteryplugin.h
SOURCES     = tpnewbatteryplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpnewbattery.pri)
