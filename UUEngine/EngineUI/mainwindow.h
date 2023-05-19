#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindowviewmodel.h"
#include "projectwidgetviewmodel.h"

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

    void resizeEvent(QResizeEvent *event) override;
public slots:
    void loadProjectStructure(QLayout *layout);

private:
    Ui::MainWindow *ui;

    ProjectWidgetViewModel * m_projectWidget;
    MainWindowViewModel *m_viewModel;

};
#endif // MAINWINDOW_H
