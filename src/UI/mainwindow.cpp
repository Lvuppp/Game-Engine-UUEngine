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
    //m_objectInfo = new ObjectInfo(ui->objectParamsWidget);

    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());

    linkConnections();
    ui->frame_3->hide();
    ui->moveButton->setIcon(QIcon(":/UIImages/translate.png"));
    ui->rotateButton->setIcon(QIcon(":/UIImages/rotate.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_projectWidget;
    delete m_openGLWidget;
    delete m_viewModel;
    delete m_objectInfo;
}

void MainWindow::linkConnections()
{
    connect(m_objectInfo, &ObjectInfo::updateWindow, this, &MainWindow::updateWindow);
    connect(m_viewModel, &MainWindowViewModel::updateWindow, this, &MainWindow::updateWindow);
    connect(m_openGLWidget, &OpenGLWidgetViewModel::updateWindow, this, &MainWindow::updateWindow);
    connect(ui->gameStatusButton, &QPushButton::clicked, m_viewModel, &MainWindowViewModel::changeGameStatus);

    auto projectActions = this->menuBar()->actions().at(0)->menu()->actions();

    foreach (auto action, projectActions) {
        connect(action,&QAction::triggered ,m_viewModel ,&MainWindowViewModel::processProject);
    }
}

void MainWindow::updateWindow()
{
    ui->openGLWidget->update();
    //ui->objectParamsWidget->update();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}
