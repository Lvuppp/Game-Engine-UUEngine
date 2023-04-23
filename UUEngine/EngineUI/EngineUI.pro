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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EngineCore/release/ -lEngineCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EngineCore/debug/ -lEngineCore
else:unix: LIBS += -L$$OUT_PWD/../EngineCore/ -lEngineCore

INCLUDEPATH += $$PWD/../EngineCore
DEPENDPATH += $$PWD/../EngineCore

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineCore/release/libEngineCore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineCore/debug/libEngineCore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineCore/release/EngineCore.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineCore/debug/EngineCore.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../EngineCore/libEngineCore.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/release/ -lEngineEntities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/debug/ -lEngineEntities
else:unix:!macx: LIBS += -L$$OUT_PWD/../EngineEntities/ -lEngineEntities

INCLUDEPATH += $$PWD/../EngineEntities
DEPENDPATH += $$PWD/../EngineEntities

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/release/libEngineEntities.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/debug/libEngineEntities.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/release/EngineEntities.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/debug/EngineEntities.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/libEngineEntities.a
