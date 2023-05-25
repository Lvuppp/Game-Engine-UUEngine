#ifndef PROJECTWIDGETVIEWMODEL_H
#define PROJECTWIDGETVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QVBoxLayout>
#include <QWidget>

class ProjectWidgetViewModel : public QWidget
{
public:
    ProjectWidgetViewModel(QWidget *parent = nullptr);

public slots:
    void updateProjectInfo();

private:
    EngineCore *m_engine;

};

#endif // PROJECTWIDGETVIEWMODEL_H
