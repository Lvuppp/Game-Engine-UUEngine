#include "ProjectWidgetViewModel.h"

cProjectWidgetViewModel::cProjectWidgetViewModel(QWidget *parent) : QWidget(parent)
{
    m_engine = cEngineCore::getInstance();

    QVBoxLayout layout;
    this->setLayout(&layout);
    m_engine->initProjectProcessor(layout);

}

void cProjectWidgetViewModel::updateProjectInfo()
{
    update();
}

