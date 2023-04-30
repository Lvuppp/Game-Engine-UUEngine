QT -= gui
QT += opengl

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = lib
CONFIG += staticlib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=

HEADERS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/release/ -lEngineEntities
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EngineEntities/debug/ -lEngineEntities
else:unix: LIBS += -L$$OUT_PWD/../EngineEntities/ -lEngineEntities

INCLUDEPATH += $$PWD/../EngineEntities
DEPENDPATH += $$PWD/../EngineEntities

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/release/libEngineEntities.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/debug/libEngineEntities.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/release/EngineEntities.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/debug/EngineEntities.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../EngineEntities/libEngineEntities.a
