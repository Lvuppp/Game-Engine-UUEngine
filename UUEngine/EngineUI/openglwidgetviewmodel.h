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
    ~OpenGLWidgetViewModel();

    void createContextMenu();
    void linkWithEngine();

public slots:
    void createObject();
    void setSkybox();

signals:
    void updateWindow();

public slots:
    void updateGraphics();
    void setDisableState(bool state);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QMenu *m_contextMenu;
    EngineCore *m_engine;
};

#endif // OPENGLWIDGETVIEWMODEL_H
