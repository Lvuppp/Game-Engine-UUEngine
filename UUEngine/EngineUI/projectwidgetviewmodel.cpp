#include "projectwidgetviewmodel.h"

ProjectWidgetViewModel::ProjectWidgetViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = EngineCore::getInstance();
    m_engine->initProjectProcessor();
    connect(m_engine, EngineCore::projectLoaded, this, ProjectWidgetViewModel::setProjectLayout);
}

void ProjectWidgetViewModel::loadProject(const QString &path)
{

}

void ProjectWidgetViewModel::presentProjectStructure()
{
    update();
}

