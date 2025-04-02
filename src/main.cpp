#include "MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setSamples(32);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    cMainWindow w;
    w.show();
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;
    return a.exec();
}
