#ifndef OPENGLWIDGETVIEWMODEL_H
#define OPENGLWIDGETVIEWMODEL_H

#include "Core/Cores/EngineCore.h"
#include "ObjectCreatorDialog.h"

#include <QMenu>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class cEngineOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    cEngineOpenGLWidget(QWidget *parent = nullptr);

    void setEngineContext(cEngineContext* context);

    void createContextMenu();
    void linkWithEngine();

public slots:
    void createObject();
    void setSkybox();
    void setDisableState(bool state);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;


private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    std::unique_ptr<QMenu> m_contextMenu;
    std::shared_ptr<cEngineCore> m_engine;
};

#endif // OPENGLWIDGETVIEWMODEL_H
