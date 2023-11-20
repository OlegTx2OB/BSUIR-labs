QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ActionButton.cpp \
    Consts.cpp \
    CreateView.cpp \
    MainWindow.cpp \
    SetParams.cpp \
    checkersFiles/Bishop.cpp \
    checkersFiles/Board.cpp \
    checkersFiles/Game.cpp \
    checkersFiles/King.cpp \
    checkersFiles/Knight.cpp \
    checkersFiles/Pawn.cpp \
    checkersFiles/Piece.cpp \
    checkersFiles/Queen.cpp \
    checkersFiles/Rook.cpp \
    checkersFiles/Square.cpp \
    display.cpp \
    main.cpp \
    space.cpp

HEADERS += \
    ActionButton.h \
    Consts.h \
    CreateView.h \
    MainWindow.h \
    SetParams.h \
    checkersFiles/Bishop.h \
    checkersFiles/Board.h \
    checkersFiles/Game.h \
    checkersFiles/King.h \
    checkersFiles/Knight.h \
    checkersFiles/Pawn.h \
    checkersFiles/Piece.h \
    checkersFiles/Queen.h \
    checkersFiles/Rook.h \
    checkersFiles/Square.h \
    display.h \
    space.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
