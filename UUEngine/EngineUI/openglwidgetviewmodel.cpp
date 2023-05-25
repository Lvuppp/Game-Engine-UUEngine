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

    connect(addCameraAction, &QAction::triggered, m_engine, &EngineCore::createCameraInScene);
    connect(addLightingAction, &QAction::triggered, m_engine, &EngineCore::createLightingInScene);

    QAction *addCustomObjectAction = new QAction("Custom object", this);
    QAction *addCubeAction = new QAction("Cube", this);
    QAction *addPlatformAction = new QAction("Platform", this);

    m_objectContextMenu->addAction(addCustomObjectAction);
    m_objectContextMenu->addAction(addCubeAction);
    m_objectContextMenu->addAction(addPlatformAction);

    connect(addCustomObjectAction, &QAction::triggered, m_engine, &EngineCore::createCustomObjectInScene);
    connect(addCubeAction, &QAction::triggered, m_engine, &EngineCore::createSimpleObjectInScene);
}

void OpenGLWidgetViewModel::linkWithEngine()
{
    connect(this, &OpenGLWidgetViewModel::mouseEvent, m_engine, &EngineCore::getEvent);
    connect(this, &OpenGLWidgetViewModel::mouseEvent, m_engine, &EngineCore::getEvent);
    connect(this, &OpenGLWidgetViewModel::mouseEvent, m_engine, &EngineCore::getEvent);
    connect(m_engine, &EngineCore::updateGraphics, this, &OpenGLWidgetViewModel::updateGraphics);

}

void OpenGLWidgetViewModel::mousePressEvent(QMouseEvent  *event)
{
    emit mouseEvent(event);
}

void OpenGLWidgetViewModel::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseEvent(event);
}

void OpenGLWidgetViewModel::wheelEvent(QWheelEvent *event)
{
    emit mouseEvent(event);
}

void OpenGLWidgetViewModel::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void OpenGLWidgetViewModel::createObject()
{
    qDebug() << sender()->objectName();
}

void OpenGLWidgetViewModel::updateGraphics()
{
    update();
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

