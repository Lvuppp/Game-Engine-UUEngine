QT -= gui
QT += opengl

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = lib
CONFIG += staticlib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        EngineEntities/base3dgameobject.cpp \
        EngineEntities/base3dphysicsgameobject.cpp \
        EngineEntities/baseengineobject.cpp \
        EngineEntities/camera.cpp \
        Models/custommodel.cpp \
        EngineEntities/lighting.cpp \
        material.cpp \
        Models/model.cpp \
        Models/modelparticle.cpp \
        scene.cpp \
        Models/simplemodel.cpp \
        EngineEntities/skybox.cpp \
        script.cpp \
        vertexdata.cpp\
        scenefolder.cpp

HEADERS += \
    EngineEntities/base3dgameobject.h \
    EngineEntities/base3dphysicsgameobject.h \
    EngineEntities/baseengineobject.h \
    EngineEntities/camera.h \
    Models/custommodel.h \
    EngineEntities/lighting.h \
    material.h \
    Models/model.h \
    Models/modelparticle.h \
    scene.h \
    Models/simplemodel.h \
    EngineEntities/skybox.h \
    script.h \
    vertexdata.h\
    scenefolder.h


unix: LIBS += -L/usr/lib64 -lGL
LIBS += -lncurses

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
