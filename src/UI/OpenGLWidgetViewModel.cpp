#include "OpenGLWidgetViewModel.h"

cOpenGLWidgetViewModel::cOpenGLWidgetViewModel(QWidget *parent)  : QOpenGLWidget(parent)
{
    this->setDisabled(true);
    m_engine = cEngineCore::getInstance();

    createContextMenu();
    linkWithEngine();
}

cOpenGLWidgetViewModel::~cOpenGLWidgetViewModel()
{
    delete m_engine;
}

void cOpenGLWidgetViewModel::createContextMenu()
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

    connect(setSkybox, &QAction::triggered, this, &cOpenGLWidgetViewModel::setSkybox);
    //connect(addCameraAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createCamera);
    //connect(addLightingAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createLighting);

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

    connect(addCustomObjectAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createObject);
    connect(addCubeAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createObject);
    //connect(addPrismAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createPrism);
    //connect(addPyramidAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createPyramid);
    connect(addSphereAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createObject);
    //connect(addCylinderAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createCylinder);
    //connect(addConeAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createCone);

}

void cOpenGLWidgetViewModel::linkWithEngine()
{
    connect(m_engine, &cEngineCore::setDisableState,this, &cOpenGLWidgetViewModel::setDisableState);
    connect(m_engine, &cEngineCore::updateGraphics,this, &cOpenGLWidgetViewModel::updateGraphics);
}

void cOpenGLWidgetViewModel::createObject()
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

void cOpenGLWidgetViewModel::setSkybox()
{
    auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");

    m_engine->setSkyBox(100.0f,objectPath);
}

void cOpenGLWidgetViewModel::updateGraphics()
{
    update();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::setDisableState(bool state)
{
    this->setDisabled(state);
}

void cOpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    m_engine->mousePressEvent(event);
    event->accept();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mouseMoveEvent(event);
    event->accept();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    m_engine->wheelEvent(event);
    event->accept();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_engine->mouseDoubleClickEvent(event);
    event->accept();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}


void cOpenGLWidgetViewModel::initializeGL()
{
    m_engine->initGraphicsEngine();
    emit updateWindow();
}

void cOpenGLWidgetViewModel::resizeGL(int w, int h)
{
    m_engine->resizeScene(w, h);
    emit updateWindow();
}

void cOpenGLWidgetViewModel::paintGL()
{
    m_engine->paintScene();
    emit updateWindow();
}


