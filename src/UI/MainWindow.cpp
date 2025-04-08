 #include "MainWindow.h"

#include "ui_mainWindow.h"


cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_viewModel = new cMainWindowViewModel();
    m_projectWidget = new cProjectWidgetViewModel(ui->projectHierarchyFrame);
    m_openGLWidget = new cOpenGLWidgetViewModel(ui->openGLWidget);
    //m_objectInfo = new cObjectInfo(ui->objectParamsWidget);

    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());

    linkConnections();
    ui->frame_3->hide();
    ui->moveButton->setIcon(QIcon(":/UIImages/translate.png"));
    ui->rotateButton->setIcon(QIcon(":/UIImages/rotate.png"));

}

cMainWindow::~cMainWindow()
{
    delete ui;
    delete m_projectWidget;
    delete m_openGLWidget;
    delete m_viewModel;
    delete m_objectInfo;
}

void cMainWindow::linkConnections()
{
    connect(ui->gameStatusButton, &QPushButton::clicked, m_viewModel, &cMainWindowViewModel::changeGameStatus);

    auto projectActions = this->menuBar()->actions().at(0)->menu()->actions();

    for (const auto& action : projectActions)
    {
        connect(action, &QAction::triggered, m_viewModel, &cMainWindowViewModel::processProject);
    }
}

void cMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}
