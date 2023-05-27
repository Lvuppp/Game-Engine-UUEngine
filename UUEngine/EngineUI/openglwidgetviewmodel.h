#ifndef OPENGLWIDGETVIEWMODEL_H
#define OPENGLWIDGETVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

class OpenGLWidgetViewModel : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWidgetViewModel(QWidget *parent = nullptr);

    void createContextMenu();
    void linkWithEngine();

public:
    void updateGraphics();

signals:
    void mousePress(QMouseEvent* event);
    void mouseMove(QMouseEvent* event);
    void wheelMove(QWheelEvent* event);

public slots:
    void createCamera();
    void createLighting();
    void createCube();
    void createPyramid();
    void createSphere();
    void createPrism();
    void createCylinder();
    void createCone();
    void createCustomObject();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QMenu *m_contextMenu;
    EngineCore *m_engine;
};

#endif // OPENGLWIDGETVIEWMODEL_H
