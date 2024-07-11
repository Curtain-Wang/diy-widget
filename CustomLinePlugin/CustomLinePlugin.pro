CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpcustomlineplugin)
TEMPLATE    = lib

HEADERS     = tpcustomlineplugin.h
SOURCES     = tpcustomlineplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpcustomline.pri)
