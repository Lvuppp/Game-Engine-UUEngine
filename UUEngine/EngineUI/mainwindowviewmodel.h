#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include"Cores/enginecore.h"
#include"projectcreator.h"

#include <QFileDialog>

class MainWindowViewModel : public QWidget
{
    Q_OBJECT
public:
    MainWindowViewModel(QWidget *parent = nullptr);

signals:
    void updateWindow();

public slots:
    void processProject();
    void changeGameStatus();

private:
    EngineCore *m_engine;
};

#endif // MAINWINDOWVIEWMODEL_H
