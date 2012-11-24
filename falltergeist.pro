TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    Surface.cpp \
    Exception.cpp \
    State.cpp \
    Game.cpp \
    Screen.cpp \
    States/StartState.cpp \
    States/MainMenuState.cpp \
    InteractiveSurface.cpp \
    Event.cpp \
    States/SaveMenuState.cpp \
    Fallout/DatFile.cpp \
    Fallout/DatFileItem.cpp \
    Fallout/FrmFileType.cpp \
    Fallout/PalFileType.cpp \
    ResourceManager.cpp \
    CrossPlatform.cpp \
    UI/RedCircleButton.cpp \
    Fallout/LstFileType.cpp

HEADERS += \
    Surface.h \
    Exception.h \
    State.h \
    Game.h \
    Screen.h \
    States/StartState.h \
    States/MainMenuState.h \
    InteractiveSurface.h \
    Event.h \
    States/SaveMenuState.h \
    Fallout/DatFile.h \
    Fallout/DatFileItem.h \
    Fallout/FrmFileType.h \
    Fallout/PalFileType.h \
    ResourceManager.h \
    CrossPlatform.h \
    UI/RedCircleButton.h \
    Fallout/LstFileType.h

LIBS+= -lSDL
