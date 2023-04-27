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
        base3dgameobject.cpp \
        base3dphysicsgameobject.cpp \
        baseengineobject.cpp \
        camera.cpp \
        lighting.cpp \
        main.cpp \
        scene.cpp \
        vertexdata.cpp

HEADERS += \
    base3dgameobject.h \
    base3dphysicsgameobject.h \
    baseengineobject.h \
    camera.h \
    lighting.h \
    scene.h \
    vertexdata.h


unix: LIBS += -L/usr/lib64 -lGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
