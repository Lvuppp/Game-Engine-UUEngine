#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_viewModel = new MainWindowViewModel(ui->openGLWidget);
    m_viewModel->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
    m_projectWidget = new ProjectWidgetViewModel(ui->projectHierarchyFrame);

    connect(m_viewModel, &MainWindowViewModel::setProjectLayout, this, &MainWindow::loadProjectStructure);

    ui->moveButton->setIcon(QIcon(":/UIImages/translate.png"));
    ui->rotateButton->setIcon(QIcon(":/UIImages/rotate.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_viewModel;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_viewModel->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}

void MainWindow::loadProjectStructure(QLayout *layout)
{
    ui->projectHierarchyFrame->setLayout(layout);

}
