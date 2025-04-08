#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include "Core/Cores/EngineCore.h"
#include "UI/ProjectCreator.h"

#include <QFileDialog>

class cMainWindowViewModel : public QWidget
{
    Q_OBJECT
public:
    cMainWindowViewModel(QWidget *parent = nullptr);

signals:
    void updateWindow();

public slots:
    void processProject();
    void changeGameStatus();

private:
    cEngineCore *m_engine;
};

#endif // MAINWINDOWVIEWMODEL_H
