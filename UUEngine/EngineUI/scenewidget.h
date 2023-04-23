#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include "enginecore.h"

#include <QOpenGLWidget>
#include <QMouseEvent>

class SceneWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent);

signals:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    void updateGraphics();
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    EngineCore* engine;
};

#endif // SCENEWIDGET_H
