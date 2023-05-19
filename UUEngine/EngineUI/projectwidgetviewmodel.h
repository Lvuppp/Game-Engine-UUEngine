#ifndef PROJECTWIDGETVIEWMODEL_H
#define PROJECTWIDGETVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QVBoxLayout>
#include <QWidget>

class ProjectWidgetViewModel : public QWidget
{
public:
    ProjectWidgetViewModel(QWidget *parent = nullptr);

signals:

public slots:
    void presentProjectStructure();
private:
    EngineCore *m_engine;

};

#endif // PROJECTWIDGETVIEWMODEL_H
