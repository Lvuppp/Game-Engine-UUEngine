#include "UI/MainWindow.h"
#include "Application/MainLoop.h"

#include <QApplication>
#include <QThread>
#include <iostream>

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setSamples(32);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    cMainWindow w;
    w.show();
    auto version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;

    cMainLoop mainLoop;
    QThread gameThread;
    mainLoop.moveToThread(&gameThread);

    QObject::connect(&gameThread, &QThread::started, &mainLoop, &cMainLoop::startMainLoop);
    QObject::connect(&a, &QApplication::aboutToQuit, [&]() {
        mainLoop.stopMainLoop();
        gameThread.quit();
        gameThread.wait();
    });

    gameThread.start();

    return a.exec();
}
