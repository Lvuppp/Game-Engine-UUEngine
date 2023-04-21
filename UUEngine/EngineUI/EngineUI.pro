QT       += core gui
QT       += opengl
QT  += core gui openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scenewidget.cpp

HEADERS += \
    mainwindow.h \
    scenewidget.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/../EngineCore

win32: LIBS += -lopengl32 #подключение на windows
win32: LIBS += -lGLU32 #подключение на windows

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
