QT       += core gui widgets printsupport


CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TweeFirstUseDialog.cpp \
    TweeLanguageDialog.cpp \
    main.cpp \
    mainwindow_oncreate.cpp\
    mainwindow_basic.cpp\
    mainwindow_slots_edit.cpp\
    mainwindow_slots_file.cpp\
    mainwindow_slots_help.cpp\
    mainwindow_events.cpp\
    FindDialog.cpp

HEADERS += \
    TweeFirstUseDialog.h \
    TweeLanguageDialog.h \
    mainwindow.h\
    FindDialog.h

RESOURCES += resource.qrc

TRANSLATIONS += \
    TweeSimpleEdit_zh_CN.ts\
    TweeSimpleEdit_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
