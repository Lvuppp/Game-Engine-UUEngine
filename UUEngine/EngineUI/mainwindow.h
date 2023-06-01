#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "openglwidgetviewmodel.h"
#include "projectwidgetviewmodel.h"
#include "mainwindowviewmodel.h"
#include "objectinfo.h"

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void linkConnections();

public slots:
    void updateWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::MainWindow *ui;

    MainWindowViewModel *m_viewModel;
    OpenGLWidgetViewModel *m_openGLWidget;
    ProjectWidgetViewModel *m_projectWidget;
    ObjectInfo *m_objectInfo;

};
#endif // MAINWINDOW_H
