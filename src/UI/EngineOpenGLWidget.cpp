#include "EngineOpenGLWidget.h"

#include "ObjectCreatorDialog.h"

#include "Core/Cores/EngineCore.h"
#include "Core/Cores/GraphicsEngine.h"
#include "Core/Cores/InputEngine.h"
#include "Core/Services/ModelBuilder.h"

#include "Utils/Hash.h"
#include "Utils/Vectors.h"

#include <QAction>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMenu>
#include <QVBoxLayout>
#include <QWheelEvent>

cEngineOpenGLWidget::cEngineOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);
    setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);

    makeCurrent();
    m_engine = cEngineCore::getInstance();

    createContextMenu();
    m_engine->resizeScene(size());
    installEventFilter(m_engine->m_inputEngine.get());
}

void cEngineOpenGLWidget::setEngineContext(cEngineContext* context)
{
}

void cEngineOpenGLWidget::createContextMenu()
{
    m_contextMenu.reset(new QMenu(this));

    QMenu *m_objectContextMenu = new QMenu("Add game object",this);
    QAction *setSkybox = new QAction("Set skybox");
    QAction *addCameraAction = new QAction("Add camera", this);
    QAction *addLightingAction = new QAction("Add lighting", this);

    m_contextMenu->addMenu(m_objectContextMenu);
    m_contextMenu->addAction(setSkybox);

    connect(setSkybox, &QAction::triggered, this, &cEngineOpenGLWidget::createSkybox);

    QAction* addCustomObjectAction = new QAction("Custom object", this);
    QAction* addCubeAction = new QAction("Cube", this);
    QAction* addPyramidAction = new QAction("Pyramid", this);
    QAction* addPrismAction = new QAction("Prism", this);
    QAction* addCylinderAction = new QAction("Cylinder", this);
    QAction* addSphereAction = new QAction("Sphere", this);
    QAction* addConeAction = new QAction("Cone", this);

    m_objectContextMenu->addAction(addCustomObjectAction);
    m_objectContextMenu->addAction(addCubeAction);
    m_objectContextMenu->addAction(addSphereAction);
    m_objectContextMenu->addAction(addConeAction);
    m_objectContextMenu->addAction(addCylinderAction);
    m_objectContextMenu->addAction(addPyramidAction);
    m_objectContextMenu->addAction(addPrismAction);

    connect(addCustomObjectAction, &QAction::triggered, this, &cEngineOpenGLWidget::createObject);
    connect(addCubeAction, &QAction::triggered, this, [this]() {
        createFigureObject("cube", cModelBuilder::Base3DFiguresType::Cube);
    });
    connect(addSphereAction, &QAction::triggered, this, [this]() {
        createFigureObject("sphere", cModelBuilder::Base3DFiguresType::Sphere);
    });
    connect(addConeAction, &QAction::triggered, this, [this]() {
        createFigureObject("cone", cModelBuilder::Base3DFiguresType::Cone);
    });
    connect(addCylinderAction, &QAction::triggered, this, [this]() {
        createFigureObject("cylinder", cModelBuilder::Base3DFiguresType::Cylinder);
    });
    connect(addPyramidAction, &QAction::triggered, this, [this]() {
        createFigureObject("pyramid", cModelBuilder::Base3DFiguresType::Pyramid);
    });
    connect(addPrismAction, &QAction::triggered, this, [this]() {
        createFigureObject("prism", cModelBuilder::Base3DFiguresType::Prism);
    });
}

void cEngineOpenGLWidget::createObject()
{
    const auto modelPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");

    m_engine->createCustomModelObject("obj"_hash, modelPath.toStdString());
}

void cEngineOpenGLWidget::createFigureObject(const std::string& name, cModelBuilder::Base3DFiguresType type)
{
    m_engine->createBaseFigureObject("cube"_hash, type);
}

void cEngineOpenGLWidget::createSkybox()
{
    const auto objectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");

    if (objectPath.isEmpty() == false)
    {
        QFileInfo fileInfo(objectPath);
        QString fileName = fileInfo.fileName();
        m_engine->createSkyBox("skybox", objectPath.toStdString());
    }
}

void cEngineOpenGLWidget::setDisableState(bool state)
{
}

void cEngineOpenGLWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void cEngineOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_engine->initGraphicsEngine(this);
}

void cEngineOpenGLWidget::resizeGL(int w, int h)
{
    m_engine->resizeScene(sVec2{ static_cast<float>(w),static_cast<float>(h) });
}

void cEngineOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_engine->render();
}
