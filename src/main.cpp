#include "UI/MainWindow.h"
#include "Application/MainLoop.h"

int main(int argc, char *argv[])
{

    // QSurfaceFormat format;
    // format.setVersion(3, 2);
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // format.setDepthBufferSize(24);
    // format.setStencilBufferSize(8);
    // format.setSamples(4); // MSAA
    // QSurfaceFormat::setDefaultFormat(format);
    
    // QApplication app(argc, argv);
    // cMainWindow mainWindow;
    // mainWindow.show();
    // return app.exec();

    cMainLoop mainLoop(argc, argv);
    return mainLoop.startMainLoop();
}
