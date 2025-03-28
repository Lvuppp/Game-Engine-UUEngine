#ifndef PROJECTWIDGETVIEWMODEL_H
#define PROJECTWIDGETVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QVBoxLayout>
#include <QWidget>

class ProjectWidgetViewModel : public QWidget
{
    Q_OBJECT
public:
    ProjectWidgetViewModel(QWidget *parent = nullptr);

signals:
    void updateWindow();

public slots:
    void updateProjectInfo();

private:
    EngineCore *m_engine;

};

#endif // PROJECTWIDGETVIEWMODEL_H
