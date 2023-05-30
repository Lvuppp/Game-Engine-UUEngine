#include "openglwidgetviewmodel.h"

OpenGLWidgetViewModel::OpenGLWidgetViewModel(QWidget *parent)  : QOpenGLWidget(parent)
{
    this->setDisabled(true);
    m_engine = EngineCore::getInstance();

    createContextMenu();
    linkWithEngine();
}

OpenGLWidgetViewModel::~OpenGLWidgetViewModel()
{
    delete m_engine;
}

void OpenGLWidgetViewModel::createContextMenu()
{
    m_contextMenu = new QMenu(this);

    QMenu *m_objectContextMenu = new QMenu("Add game object",this);
    QAction *addCameraAction = new QAction("Add camera", this);
    QAction *addLightingAction = new QAction("Add lighting", this);

    m_contextMenu->addMenu(m_objectContextMenu);
    //m_contextMenu->addAction(addCameraAction);
    //m_contextMenu->addAction(addLightingAction);

    connect(addCameraAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCamera);
    connect(addLightingAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createLighting);

    QAction *addCustomObjectAction = new QAction("Custom object", this);
    QAction *addCubeAction = new QAction("Cube", this);
    QAction *addPyramidAction = new QAction("Pyramid", this);
    QAction *addPrismAction = new QAction("Prism", this);
    QAction *addCylinderAction = new QAction("Cylinder", this);
    QAction *addSphereAction = new QAction("Sphere", this);
    QAction *addConeAction = new QAction("Cone", this);

    m_objectContextMenu->addAction(addCustomObjectAction);
    m_objectContextMenu->addAction(addCubeAction);
    //m_objectContextMenu->addAction(addPyramidAction);
    //m_objectContextMenu->addAction(addPrismAction);
    //m_objectContextMenu->addAction(addCylinderAction);
    m_objectContextMenu->addAction(addSphereAction);
    //m_objectContextMenu->addAction(addConeAction);

    connect(addCustomObjectAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCustomObject);
    connect(addCubeAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCube);
    connect(addPrismAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createPrism);
    connect(addPyramidAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createPyramid);
    connect(addSphereAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createSphere);
    connect(addCylinderAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCylinder);
    connect(addConeAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCone);

}

void OpenGLWidgetViewModel::linkWithEngine()
{
    connect(m_engine, &EngineCore::setDisableState,this, &OpenGLWidgetViewModel::setDisableState);
    connect(m_engine, &EngineCore::updateGraphics, this, &OpenGLWidgetViewModel::updateGraphics);

}

void OpenGLWidgetViewModel::createCube()
{
    QString defaultName = "Cube1";

    for (int var = 2; !m_engine->createCube(defaultName); ++var) {
        defaultName.chop(1);
        defaultName += QString::number(var);
    }
}

void OpenGLWidgetViewModel::createPyramid()
{
    m_engine->createPyramide("Pyramid");
}

void OpenGLWidgetViewModel::createSphere()
{
    QString defaultName = "Sphere1";

    for (int var = 2; !m_engine->createSphere(defaultName); ++var) {
        defaultName.chop(1);
        defaultName += QString::number(var);
    }
}

void OpenGLWidgetViewModel::createPrism()
{
    m_engine->createPrism("Prism");
}

void OpenGLWidgetViewModel::createCylinder()
{
    m_engine->createCylinder("Cylinder");
}

void OpenGLWidgetViewModel::createCone()
{
    m_engine->createCone("Cone");
}

void OpenGLWidgetViewModel::createCustomObject()
{
    auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.obj*)");

    if(objectPath.split('/').last().split('.').constLast() == "obj"){
        QString defaultName = "CustomModel1";

        for (int var = 2; !m_engine->createOBJModel(defaultName, objectPath); ++var) {
            defaultName.chop(1);
            defaultName += QString::number(var);
        }
    }
}

void OpenGLWidgetViewModel::setDisableState(bool state)
{
    this->setDisabled(state);
}

void OpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    m_engine->mousePressEvent(event);
    emit updateWindow();
}

void OpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mouseMoveEvent(event);
    emit updateWindow();
}

void OpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    m_engine->wheelEvent(event);
    emit updateWindow();
}

void OpenGLWidgetViewModel::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_engine->mouseDoubleClickEvent(event);
    emit updateWindow();
}

void OpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void OpenGLWidgetViewModel::updateGraphics()
{
    repaint();
}

void OpenGLWidgetViewModel::createCamera()
{
    m_engine->createCameraInScene("Camera");
}

void OpenGLWidgetViewModel::createLighting()
{
    m_engine->createLightingInScene("Lighting");
}

void OpenGLWidgetViewModel::initializeGL()
{
    m_engine->initGraphicsEngine();
    emit updateWindow();
}

void OpenGLWidgetViewModel::resizeGL(int w, int h)
{
    m_engine->resizeScene(w, h);
    emit updateWindow();
}

void OpenGLWidgetViewModel::paintGL()
{
    m_engine->paintScene();
    emit updateWindow();
}


