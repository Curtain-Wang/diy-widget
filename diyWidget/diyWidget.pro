QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customline.cpp \
    heater.cpp \
    main.cpp \
    mainwindow.cpp \
    mydial.cpp

HEADERS += \
    customline.h \
    heater.h \
    mainwindow.h \
    mydial.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -ltpbatteryplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -ltpbatteryplugind

win32:CONFIG(release, debug|release) {
    message("Adding release library for tpcustomlineplugin")
    LIBS += -L$$PWD/include/ -ltpcustomlineplugin
} else:win32:CONFIG(debug, debug|release) {
    message("Adding debug library for tpcustomlineplugin")
    LIBS += -L$$PWD/include/ -ltpcustomlineplugind
}

message("Include path: $$PWD/include")


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/include/ -ltpdialplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/include/ -ltpdialplugind

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
