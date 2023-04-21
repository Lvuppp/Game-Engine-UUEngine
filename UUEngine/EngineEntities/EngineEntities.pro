QT += gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        base3dnonphysicsgameobject.cpp \
        base3dphysicsgameobject.cpp \
        baseengineobject.cpp \
        camera.cpp \
        lighting.cpp \
        main.cpp \
        scene.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    base3dnonphysicsgameobject.h \
    base3dphysicsgameobject.h \
    baseengineobject.h \
    camera.h \
    lighting.h \
    scene.h
