CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpseccircuitdiagramplugin)
TEMPLATE    = lib

HEADERS     = tpseccircuitdiagramplugin.h
SOURCES     = tpseccircuitdiagramplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpseccircuitdiagram.pri)
