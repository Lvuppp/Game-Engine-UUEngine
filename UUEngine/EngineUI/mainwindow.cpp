#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_viewModel = new MainWindowViewModel();
    m_projectWidget = new ProjectWidgetViewModel(ui->projectHierarchyFrame);
    m_openGLWidget = new OpenGLWidgetViewModel(ui->openGLWidget);

    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());

    auto projectActions = this->menuBar()->actions()[0]->menu()->actions();

    foreach (auto action, projectActions) {
        connect(action,&QAction::triggered ,m_viewModel ,&MainWindowViewModel::processProject);
    }

    //connect(m_viewModel, &MainWindowViewModel::setProjectLayout, this, &MainWindow::loadProjectStructure);

    ui->moveButton->setIcon(QIcon(":/UIImages/translate.png"));
    ui->rotateButton->setIcon(QIcon(":/UIImages/rotate.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_projectWidget;
    delete m_openGLWidget;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}



