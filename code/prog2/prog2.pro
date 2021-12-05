#message("Building student project")
include(../../QtrainSim/QtrainSim.pri)

CONFIG += c++17

LIBS += -lpcosynchro

HEADERS +=  \
    src/sharedsectioninterface.h \
    src/locomotive.h \
    src/launchable.h \
    src/locomotivebehavior.h \
    src/sharedsection.h \
    src/waycontroller.h

SOURCES +=  \
    src/locomotive.cpp \
    src/cppmain.cpp \
    src/locomotivebehavior.cpp \
    src/waycontroller.cpp
