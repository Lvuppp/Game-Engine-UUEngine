#include "mainwindowviewmodel.h"

#include <QFileDialog>
MainWindowViewModel::MainWindowViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = EngineCore::getInstance();
}

void MainWindowViewModel::processProject()
{
    QAction *action = dynamic_cast<QAction *>(sender());

    if(action->text() == "Create"){
        ProjectCreator *projectCreator = new ProjectCreator();

        connect(projectCreator, &ProjectCreator::getFolderPath, this, [this](QString path){
            m_engine->createProject(path.split(' ')[0], path.split(' ')[1]);
        });

        projectCreator->exec();

        delete projectCreator;

    }
    else if(action->text() == "Open"){
        auto projectPath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.uupj*)");

        if(projectPath.size()){
            m_engine->loadProject(projectPath);
        }

    }

    else if(action->text() == "Save"){
        m_engine->saveProject();

    }
    else if(action->text() == "Save as"){
        ProjectCreator *projectCreator = new ProjectCreator();

        connect(projectCreator, &ProjectCreator::getFolderPath, this, [this](QString path){
            m_engine->createProject(path.split(' ')[0], path.split(' ')[1]);
            m_engine->saveProject(path.split(' ')[0] + '/' + path.split(' ')[1]  + '/' + path.split(' ')[1] + ".uupj");
        });

        projectCreator->exec();

        delete projectCreator;

    }
    else if(action->text() == "Close"){
        m_engine->closeProject();
    }

    emit updateWindow();

}

void MainWindowViewModel::changeGameStatus()
{
    m_engine->changeGameStatus();
}
