CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpscaleplugin)
TEMPLATE    = lib

HEADERS     = tpscaleplugin.h
SOURCES     = tpscaleplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpscale.pri)
