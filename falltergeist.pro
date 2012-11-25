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
    Fallout/LstFileType.cpp \
    Fallout/FonFileType.cpp \
    Fallout/AafFileType.cpp \
    UI/TextLabel.cpp \
    Font.cpp \
    States/NewGameState.cpp \
    UI/RedSmallCircleButton.cpp \
    UI/LeftArrowButton.cpp \
    UI/RightArrowButton.cpp \
    Fallout/GcdFileType.cpp \
    Fallout/MsgFileType.cpp

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
    Fallout/LstFileType.h \
    Fallout/FonFileType.h \
    Fallout/AafFileType.h \
    UI/TextLabel.h \
    Font.h \
    States/NewGameState.h \
    UI/RedSmallCircleButton.h \
    UI/LeftArrowButton.h \
    UI/RightArrowButton.h \
    Fallout/GcdFileType.h \
    Fallout/MsgFileType.h

LIBS+= -lSDL
