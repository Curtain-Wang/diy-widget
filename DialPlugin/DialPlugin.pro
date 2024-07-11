CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpdialplugin)
TEMPLATE    = lib

HEADERS     = tpdialplugin.h
SOURCES     = tpdialplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpdial.pri)
