#include "OpenGLWidget.h"

#include "Core/Cores/GraphicsEngine.h"

cOpenGLWidget::cOpenGLWidget(QWidget* parent)
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
}

cOpenGLWidget::~cOpenGLWidget()
{
    makeCurrent();
    doneCurrent();
}

void cOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initOpenGL();
}

void cOpenGLWidget::resizeGL(int w, int h)
{
}

void cOpenGLWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cOpenGLWidget::initOpenGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
