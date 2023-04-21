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
        enginecore.cpp \
        graphicsengine.cpp \
        main.cpp \
        physicsengine.cpp \
        scriptengine.cpp

HEADERS += \
    enginecore.h \
    graphicsengine.h \
    physicsengine.h \
    scriptengine.h

DISTFILES += \
    vshader.vsh


win32: LIBS += -lopengl32 #подключение на windows

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

