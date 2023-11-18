#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T19:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessGame_223637
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        BishopClass.cpp \
        FigureClass.cpp \
        GameView.cpp \
        KingClass.cpp \
        KnightClass.cpp \
        PawnClass.cpp \
        QueenClass.cpp \
        RookClass.cpp \
        actionbutton.cpp \
        boardfield.cpp \
        boardframefield.cpp \
        boardview.cpp \
        boardviewmodel.cpp \
        congratulationsview.cpp \
        constants.cpp \
        figurefield.cpp \
        main.cpp \
        pawnviemodel.cpp \
        playerview.cpp \
        utils.cpp

HEADERS += \
        BishopClass.h \
        BoardPosition.h \
        FigureClass.h \
        GameView.h \
        KingClass.h \
        KnightClass.h \
        PawnClass.h \
        QueenClass.h \
        RookClass.h \
        actionbutton.h \
        boardfield.h \
        boardframefield.h \
        boardview.h \
        boardviewmodel.h \
        congratulationsview.h \
        constants.h \
        figurefield.h \
        helpers.h \
        pawnviewmodel.h \
        playerview.h \
        utils.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
