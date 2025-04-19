#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class cOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    cOpenGLWidget(QWidget* parent = nullptr);
    ~cOpenGLWidget() override;

public:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void initOpenGL();
};

#endif // OPENGLWIDGET_H
