#include "MainWindow.h"

#include "Core/Cores/EngineCore.h"
#include "UI/EngineOpenGLWidget.h"

#include "ui_mainWindow.h"


cMainWindow::cMainWindow(cEngineContext* context, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_viewModel.reset(new cMainWindowViewModel());
    m_projectWidget.reset(new cProjectWidgetViewModel(ui->projectHierarchyFrame));
    //m_objectInfo = new cObjectInfo(ui->objectParamsWidget);

    ui->openGLWidget->setEngineContext(context);
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
    auto projectActions = this->menuBar()->actions().at(0)->menu()->actions();

    auto engine = cEngineCore::getInstance();
    connect(projectActions[0], &QAction::triggered, [engine](){
        cProjectCreator projectCreator;
        connect(&projectCreator, &cProjectCreator::getFolderPath, [engine](const auto& path, const auto& name) {
            engine->createProject(path, name);
        });

        projectCreator.exec();
    });
}

cEngineOpenGLWidget* cMainWindow::getOpenGLWigdet() const
{
    return ui->openGLWidget;
}

void cMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    //m_openGLWidget->resize(ui->openGLWidget->width(), ui->openGLWidget->height());
}
