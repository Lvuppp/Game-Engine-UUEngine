#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UI/ProjectWidgetViewModel.h"
#include "UI/MainWindowViewModel.h"
#include "UI/ObjectInfo.h"

#include <QMainWindow>
#include <QResizeEvent>

class cEngineContext;
class cEngineOpenGLWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class  cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    cMainWindow(cEngineContext* context, QWidget *parent = nullptr);
    ~cMainWindow();

    void linkConnections();

    cEngineOpenGLWidget* getOpenGLWigdet() const;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    std::unique_ptr<cMainWindowViewModel> m_viewModel;
    std::unique_ptr<cProjectWidgetViewModel> m_projectWidget;
    std::unique_ptr<cObjectInfo> m_objectInfo;

};
#endif // MAINWINDOW_H
