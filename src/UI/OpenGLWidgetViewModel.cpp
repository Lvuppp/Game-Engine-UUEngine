#include "OpenGLWidgetViewModel.h"

#include "Utils/Hash.h"

cOpenGLWidgetViewModel::cOpenGLWidgetViewModel(QWidget *parent)  : QOpenGLWidget(parent)
{
    this->setDisabled(true);
    //m_engine = cEngineCore::getInstance();

    createContextMenu();
    linkWithEngine();

    makeCurrent();
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
    connect(addSphereAction, &QAction::triggered, this, &cOpenGLWidgetViewModel::createObject);

}

void cOpenGLWidgetViewModel::linkWithEngine()
{
    connect(m_engine, &cEngineCore::setDisableState,this, &cOpenGLWidgetViewModel::setDisableState);
}

void cOpenGLWidgetViewModel::createObject()
{
    QAction *action = dynamic_cast<QAction *>(sender());
    std::string objectName = action->text().toStdString();
    std::function<bool(std::string)> func;

    if(objectName == "Cube")
    {
        func = [this](std::string objectName) -> bool{ return m_engine->createCube(cHash::hash(objectName));};
    }
    else if(objectName == "Sphere")
    {
        func = [this](std::string objectName) -> bool{ return m_engine->createSphere(cHash::hash(objectName));};
    }
    else if(objectName == "Custom object")
    {
        auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.obj*)");

        if(objectPath.split('/').last().split('.').constLast() == "obj"){
            std::string objectPathStd = objectPath.toStdString();
            func = [this, objectPathStd](std::string objectName) -> bool {
                return m_engine->createOBJModel(cHash::hash(objectName), objectPathStd);
            };
        }
    }
    else{
        return;
    }

    objectName += '1';

    for (int var = 2; !func(objectName); ++var)
    {
        objectName.pop_back();
        objectName += std::to_string(var);
    }
}

void cOpenGLWidgetViewModel::setSkybox()
{
    const auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");

    m_engine->setSkyBox(100.0f, objectPath.toStdString());
}

void cOpenGLWidgetViewModel::setDisableState(bool state)
{
    this->setDisabled(state);
}

void cOpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    m_engine->mousePressEvent(event);
    event->accept();
}

void cOpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    m_engine->mouseMoveEvent(event);
    event->accept();
}

void cOpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    m_engine->wheelEvent(event);
    event->accept();
}

void cOpenGLWidgetViewModel::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_engine->mouseDoubleClickEvent(event);
    event->accept();
}

void cOpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void cOpenGLWidgetViewModel::initializeGL()
{
}

void cOpenGLWidgetViewModel::resizeGL(int w, int h)
{
    m_engine->resizeScene(w, h);
}

void cOpenGLWidgetViewModel::paintGL()
{
}
