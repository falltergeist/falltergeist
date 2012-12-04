TEMPLATE = app
CONFIG -= qt

SOURCES += main.cpp \
    src/Engine/Surface.cpp \
    src/Engine/Exception.cpp \
    src/Engine/State.cpp \
    src/Engine/Game.cpp \
    src/Engine/Screen.cpp \
    src/Engine/InteractiveSurface.cpp \
    src/Engine/Event.cpp \
    src/Engine/ResourceManager.cpp \
    src/Engine/CrossPlatform.cpp \
    src/Engine/Font.cpp \
    src/Engine/Animation.cpp\
    src/Engine/Player.cpp \
    src/Engine/SurfaceSet.cpp \
    src/Fallout/DatFile.cpp \
    src/Fallout/DatFileItem.cpp \
    src/Fallout/FrmFileType.cpp \
    src/Fallout/PalFileType.cpp \
    src/Fallout/LstFileType.cpp \
    src/Fallout/FonFileType.cpp \
    src/Fallout/AafFileType.cpp \
    src/Fallout/GcdFileType.cpp \
    src/Fallout/MsgFileType.cpp \
    src/Fallout/BioFileType.cpp \
    src/States/StartState.cpp \
    src/States/MainMenuState.cpp \
    src/States/NewGameState.cpp \
    src/States/PlayerEditState.cpp \
    src/UI/ImageButton.cpp \
    src/UI/TextArea.cpp \
    src/UI/FpsCounter.cpp \
    src/UI/BigCounter.cpp \
    src/UI/HiddenMask.cpp

HEADERS += \
    src/Engine/Surface.h \
    src/Engine/Exception.h \
    src/Engine/State.h \
    src/Engine/Game.h \
    src/Engine/Screen.h \
    src/Engine/InteractiveSurface.h \
    src/Engine/Event.h \
    src/Engine/ResourceManager.h \
    src/Engine/CrossPlatform.h \
    src/Engine/Font.h \
    src/Engine/Animation.h \
    src/Engine/Player.h \
    src/Engine/SurfaceSet.h \
    src/Fallout/DatFile.h \
    src/Fallout/DatFileItem.h \
    src/Fallout/FrmFileType.h \
    src/Fallout/PalFileType.h \
    src/Fallout/LstFileType.h \
    src/Fallout/FonFileType.h \
    src/Fallout/AafFileType.h \
    src/Fallout/GcdFileType.h \
    src/Fallout/MsgFileType.h \
    src/Fallout/BioFileType.h \
    src/States/StartState.h \
    src/States/MainMenuState.h \
    src/States/NewGameState.h \
    src/States/PlayerEditState.h \
    src/UI/ImageButton.h \
    src/UI/TextArea.h \
    src/UI/FpsCounter.h \
    src/UI/BigCounter.h \
    src/UI/HiddenMask.h

LIBS += -lSDL

OTHER_FILES += \
    CMakeLists.txt
