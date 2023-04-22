#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QOpenGLWidget>

#include "enginecore.h"

class SceneWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initshaders();

    EngineCore* engine;
    QOpenGLShaderProgram shaderProgram;
};

#endif // SCENEWIDGET_H
