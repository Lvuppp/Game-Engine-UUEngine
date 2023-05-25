#ifndef OPENGLWIDGETVIEWMODEL_H
#define OPENGLWIDGETVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>

class OpenGLWidgetViewModel : public QOpenGLWidget
{
    Q_OBJECT
public:
    OpenGLWidgetViewModel(QWidget *parent = nullptr);

    void createContextMenu();
    void linkWithEngine();

signals:
    void createObjects();
    void mouseEvent(QEvent* event);

public slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;
    void createObject();
public:
    void updateGraphics();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    QMenu *m_contextMenu;
    EngineCore *m_engine;
};

#endif // OPENGLWIDGETVIEWMODEL_H
