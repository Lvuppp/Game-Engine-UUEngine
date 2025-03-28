#include "projectwidgetviewmodel.h"

ProjectWidgetViewModel::ProjectWidgetViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = EngineCore::getInstance();

    QVBoxLayout layout;
    this->setLayout(&layout);
    m_engine->initProjectProcessor(layout);

}


void ProjectWidgetViewModel::updateProjectInfo()
{
    update();
}

