QT -= gui
QT += opengl openglwidgets

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = lib
CONFIG += staticlib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



win32: LIBS += -lopengl32 #подключение на windows

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/release/ -lEngineEntities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/debug/ -lEngineEntities
else:unix:!macx: LIBS += -L$$OUT_PWD/../EngineEntities/ -lEngineEntities

INCLUDEPATH += $$PWD/../Entities
DEPENDPATH += $$PWD/../Entities

HEADERS += \
    Cores/EngineCore.h \
    Cores/GraphicsEngine.h \
    Cores/InputEngine.h \
    Cores/PhysicsEngine.h \
    Cores/ScriptEngine.h \
    Folders/MaterialLib.h \
    Folders/ModelFolder.h \
    Folders/ScriptFolder.h \
    Folders/TextureFolder.h \
    Services/Eventhandler.h \
    Services/ModelBuilder.h \
    Services/ModelLoader.h \
    Services/ProjectProcessor.h \
    Services/Projectinfo.h

SOURCES += \
    Cores/EngineCore.cpp \
    Cores/GraphicsEngine.cpp \
    Cores/InputEngine.cpp \
    Cores/PhysicsEngine.cpp \
    Cores/ScriptEngine.cpp \
    Folders/MaterialLib.cpp \
    Folders/ModelFolder.cpp \
    Folders/ScriptFolder.cpp \
    Folders/TextureFolder.cpp \
    Services/Eventhandler.cpp \
    Services/ModelBuilder.cpp \
    Services/ModelLoader.cpp \
    Services/ProjectProcessor.cpp \
    Services/Projectinfo.cpp
