 #include "MainWindow.h"

#include "Application/OpenGLWidget.h"
#include "ui_mainWindow.h"


cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_viewModel.reset(new cMainWindowViewModel());
    m_projectWidget.reset(new cProjectWidgetViewModel(ui->projectHierarchyFrame));
    //m_objectInfo = new cObjectInfo(ui->objectParamsWidget);

//    m_openGLWidget.reset(ui->openGLWidget);
    ui->openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());

    linkConnections();
    ui->frame_3->hide();
    ui->moveButton->setIcon(QIcon(":/UIImages/translate.png"));
    ui->rotateButton->setIcon(QIcon(":/UIImages/rotate.png"));

}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::linkConnections()
{
    // connect(ui->gameStatusButton, &QPushButton::clicked, m_viewModel.get(), &cMainWindowViewModel::changeGameStatus);

    // auto projectActions = this->menuBar()->actions().at(0)->menu()->actions();

    // for (const auto& action : projectActions)
    // {
    //     connect(action, &QAction::triggered, m_viewModel.get(), &cMainWindowViewModel::processProject);
    // }
}

cOpenGLWidget* cMainWindow::getOpenGLWigdet() const
{
    return ui->openGLWidget;
}

void cMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    //m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}
