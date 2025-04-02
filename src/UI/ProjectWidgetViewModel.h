#ifndef PROJECTWIDGETVIEWMODEL_H
#define PROJECTWIDGETVIEWMODEL_H

#include "Cores/EngineCore.h"

#include <QVBoxLayout>
#include <QWidget>

class cProjectWidgetViewModel : public QWidget
{
    Q_OBJECT
public:
    cProjectWidgetViewModel(QWidget *parent = nullptr);

signals:
    void updateWindow();

public slots:
    void updateProjectInfo();

private:
    cEngineCore *m_engine;

};

#endif // PROJECTWIDGETVIEWMODEL_H
