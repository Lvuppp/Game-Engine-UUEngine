#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scenewidget.h"
#include "baseengineobject.h"
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
private:
    Ui::MainWindow *ui;

    SceneWidget *scene;

};
#endif // MAINWINDOW_H
