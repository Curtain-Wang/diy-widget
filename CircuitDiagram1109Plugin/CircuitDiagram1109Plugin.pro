CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(tpcircuitdiagram1109plugin)
TEMPLATE    = lib

HEADERS     = tpcircuitdiagram1109plugin.h
SOURCES     = tpcircuitdiagram1109plugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(tpcircuitdiagram1109.pri)
