#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OpenGLWidgetViewModel.h"
#include "ProjectWidgetViewModel.h"
#include "MainWindowViewModel.h"
#include "ObjectInfo.h"

#include <QMainWindow>
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    cMainWindow(QWidget *parent = nullptr);
    ~cMainWindow();

    void linkConnections();

public slots:
    void updateWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;


private:
    Ui::MainWindow *ui;

    cMainWindowViewModel *m_viewModel;
    cOpenGLWidgetViewModel *m_openGLWidget;
    cProjectWidgetViewModel *m_projectWidget;
    cObjectInfo *m_objectInfo;

};
#endif // MAINWINDOW_H
