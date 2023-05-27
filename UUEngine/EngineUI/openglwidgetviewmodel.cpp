#include "openglwidgetviewmodel.h"

OpenGLWidgetViewModel::OpenGLWidgetViewModel(QWidget *parent)  : QOpenGLWidget(parent)
{
    m_engine = EngineCore::getInstance();
    createContextMenu();
    linkWithEngine();
}

void OpenGLWidgetViewModel::createContextMenu()
{
    m_contextMenu = new QMenu(this);

    QMenu *m_objectContextMenu = new QMenu("Add game object",this);
    QAction *addCameraAction = new QAction("Add camera", this);
    QAction *addLightingAction = new QAction("Add lighting", this);

    m_contextMenu->addMenu(m_objectContextMenu);
    m_contextMenu->addAction(addCameraAction);
    m_contextMenu->addAction(addLightingAction);

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
    m_objectContextMenu->addAction(addPyramidAction);
    m_objectContextMenu->addAction(addPrismAction);
    m_objectContextMenu->addAction(addCylinderAction);
    m_objectContextMenu->addAction(addSphereAction);
    m_objectContextMenu->addAction(addConeAction);

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
    connect(this, &OpenGLWidgetViewModel::mousePress,m_engine, &EngineCore::mousePressEvent);
    connect(this, &OpenGLWidgetViewModel::mouseMove,m_engine, &EngineCore::mouseMoveEvent);
    connect(this, &OpenGLWidgetViewModel::wheelMove,m_engine, &EngineCore::wheelEvent);
    connect(m_engine, &EngineCore::updateGraphics, this, &OpenGLWidgetViewModel::updateGraphics);

}

void OpenGLWidgetViewModel::createCube()
{
    m_engine->createCube("Cube");
}

void OpenGLWidgetViewModel::createPyramid()
{
    m_engine->createPyramide("Pyramid");
}

void OpenGLWidgetViewModel::createSphere()
{
    m_engine->createCube("Sphere");
}

void OpenGLWidgetViewModel::createPrism()
{
    m_engine->createCube("Sphere");
}

void OpenGLWidgetViewModel::createCylinder()
{
    m_engine->createCube("Sphere");
}

void OpenGLWidgetViewModel::createCone()
{
    m_engine->createCube("Sphere");
}

void OpenGLWidgetViewModel::createCustomObject()
{
    auto projectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.obj|.fbx*)");

    if(projectPath.split('/').last().split('.').constLast() == ".fbx"){
        m_engine->createFBXModel("CustomModel", projectPath);
    }else{
        m_engine->createOBJModel("CustomModel", projectPath);
    }
}

void OpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    m_engine->mousePressEvent(event);
}

void OpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mouseMoveEvent(event);
}

void OpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    m_engine->wheelEvent(event);
}

void OpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void OpenGLWidgetViewModel::updateGraphics()
{
    update();
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
}

void OpenGLWidgetViewModel::resizeGL(int w, int h)
{
    m_engine->resizeScene(w, h);
}

void OpenGLWidgetViewModel::paintGL()
{
    m_engine->paintScene();
}


