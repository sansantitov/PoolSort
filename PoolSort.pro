TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        quickSort.cpp

HEADERS += \
    poolThread.h \
    quickSort.h \
    requestHandler.h

DISTFILES += \
    README.md
