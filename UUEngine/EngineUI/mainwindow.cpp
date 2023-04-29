#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new SceneWidget(ui->openGLWidget);
    scene->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

//void MainWindow::resizeEvent(QResizeEvent *event)
//{
//    scene->resize(ui->openGLWidget->sizeHint().width(), ui->openGLWidget->sizeHint().height());
//    QMainWindow::resizeEvent(event);
//}

