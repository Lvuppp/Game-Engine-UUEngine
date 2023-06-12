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
    QAction *setSkybox = new QAction("Set skybox");
    QAction *addCameraAction = new QAction("Add camera", this);
    QAction *addLightingAction = new QAction("Add lighting", this);

    m_contextMenu->addMenu(m_objectContextMenu);
    m_contextMenu->addAction(setSkybox);
    //m_contextMenu->addAction(addCameraAction);
    //m_contextMenu->addAction(addLightingAction);

    connect(setSkybox, &QAction::triggered, this, &OpenGLWidgetViewModel::setSkybox);
    //connect(addCameraAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCamera);
    //connect(addLightingAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createLighting);

    QAction *addCustomObjectAction = new QAction("Custom object", this);
    QAction *addCubeAction = new QAction("Cube", this);
    QAction *addPyramidAction = new QAction("Pyramid", this);
    QAction *addPrismAction = new QAction("Prism", this);
    QAction *addCylinderAction = new QAction("Cylinder", this);
    QAction *addSphereAction = new QAction("Sphere", this);
    QAction *addConeAction = new QAction("Cone", this);

    m_objectContextMenu->addAction(addCustomObjectAction);
    m_objectContextMenu->addAction(addCubeAction);
    //m_objectContextMenu->addAction(addPrismAction);
    //m_objectContextMenu->addAction(addCylinderAction);
    m_objectContextMenu->addAction(addSphereAction);
    //m_objectContextMenu->addAction(addConeAction);

    connect(addCustomObjectAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createObject);
    connect(addCubeAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createObject);
    //connect(addPrismAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createPrism);
    //connect(addPyramidAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createPyramid);
    connect(addSphereAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createObject);
    //connect(addCylinderAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCylinder);
    //connect(addConeAction, &QAction::triggered, this, &OpenGLWidgetViewModel::createCone);

}

void OpenGLWidgetViewModel::linkWithEngine()
{
    connect(m_engine, &EngineCore::setDisableState,this, &OpenGLWidgetViewModel::setDisableState);
    connect(m_engine, &EngineCore::updateGraphics,this, &OpenGLWidgetViewModel::updateGraphics);
}

void OpenGLWidgetViewModel::createObject()
{
    QAction *action = dynamic_cast<QAction *>(sender());
    QString objectName = action->text();
    std::function<bool(QString)> func;

    if(objectName == "Cube"){
        func = [this](QString objectName) -> bool{ return m_engine->createCube(objectName);};
    }
    else if(objectName == "Sphere"){
        func = [this](QString objectName) -> bool{ return m_engine->createSphere(objectName);};
    }
    else if(objectName == "Custom object"){
        auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.obj*)");

        if(objectPath.split('/').last().split('.').constLast() == "obj"){
            func = [this,objectPath](QString objectName) -> bool{ return  m_engine->createOBJModel(objectName, objectPath);};
        }
    }
    else{
        return;
    }

    objectName += '1';

    for (int var = 2; !func(objectName); ++var) {
        objectName.chop(1);
        objectName += QString::number(var);
    }
    emit updateGraphics();
}

void OpenGLWidgetViewModel::setSkybox()
{
    auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");

    m_engine->setSkyBox(100.0f,objectPath);
}

void OpenGLWidgetViewModel::updateGraphics()
{
    update();
    emit updateWindow();
}

void OpenGLWidgetViewModel::setDisableState(bool state)
{
    this->setDisabled(state);
}

void OpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    m_engine->mousePressEvent(event);
    event->accept();
    emit updateWindow();
}

void OpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mouseMoveEvent(event);
    event->accept();
    emit updateWindow();
}

void OpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    m_engine->wheelEvent(event);
    event->accept();
    emit updateWindow();
}

void OpenGLWidgetViewModel::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_engine->mouseDoubleClickEvent(event);
    event->accept();
    emit updateWindow();
}

void OpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
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


