#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include"Cores/enginecore.h"
#include"projectcreator.h"

#include <QFileDialog>

class MainWindowViewModel : public QWidget
{
public:
    MainWindowViewModel(QWidget *parent = nullptr);

public slots:
    void processProject();

private:
    EngineCore *m_engine;
};

#endif // MAINWINDOWVIEWMODEL_H
