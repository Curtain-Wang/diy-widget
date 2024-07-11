CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpheaterplugin)
TEMPLATE    = lib

HEADERS     = tpheaterplugin.h
SOURCES     = tpheaterplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpheater.pri)
