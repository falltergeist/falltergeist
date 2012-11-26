TEMPLATE = app
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
    Fallout/DatFile.cpp \
    Fallout/DatFileItem.cpp \
    Fallout/FrmFileType.cpp \
    Fallout/PalFileType.cpp \
    ResourceManager.cpp \
    CrossPlatform.cpp \
    Fallout/LstFileType.cpp \
    Fallout/FonFileType.cpp \
    Fallout/AafFileType.cpp \
    UI/TextLabel.cpp \
    Font.cpp \
    States/NewGameState.cpp \
    Fallout/GcdFileType.cpp \
    Fallout/MsgFileType.cpp \
    UI/ImageButton.cpp

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
    Fallout/DatFile.h \
    Fallout/DatFileItem.h \
    Fallout/FrmFileType.h \
    Fallout/PalFileType.h \
    ResourceManager.h \
    CrossPlatform.h \
    Fallout/LstFileType.h \
    Fallout/FonFileType.h \
    Fallout/AafFileType.h \
    UI/TextLabel.h \
    Font.h \
    States/NewGameState.h \
    Fallout/GcdFileType.h \
    Fallout/MsgFileType.h \
    UI/ImageButton.h

LIBS += -lSDL
