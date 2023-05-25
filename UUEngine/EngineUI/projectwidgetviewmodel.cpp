#include "projectwidgetviewmodel.h"

ProjectWidgetViewModel::ProjectWidgetViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = EngineCore::getInstance();

    QVBoxLayout layout;
    this->setLayout(&layout);
    m_engine->initProjectProcessor(layout);

    connect(m_engine, &EngineCore::projectLoaded, this, &ProjectWidgetViewModel::updateProjectInfo);
}


void ProjectWidgetViewModel::updateProjectInfo()
{
    update();
}

