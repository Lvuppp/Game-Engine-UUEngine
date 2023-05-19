#include "projectwidgetviewmodel.h"

ProjectWidgetViewModel::ProjectWidgetViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = EngineCore::getInstance();
    //connect(m_engine, EngineCore::projectLoaded, this, ProjectWidgetViewModel::presentProjectStructure);
}

void ProjectWidgetViewModel::presentProjectStructure()
{
    update();
}

