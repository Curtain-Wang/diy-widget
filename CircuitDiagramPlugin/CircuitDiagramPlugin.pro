CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpcircuitdiagramplugin)
TEMPLATE    = lib

HEADERS     = tpcircuitdiagramplugin.h
SOURCES     = tpcircuitdiagramplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpcircuitdiagram.pri)
