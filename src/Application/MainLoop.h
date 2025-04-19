#pragma once

#include "Application/OpenGLWidget.h"
#include "Core/Cores/EngineCore.h"
#include <UI/MainWindow.h>

#include <QApplication>
#include <QObject>

#include <atomic>
#include <cstdint>

class cMainLoop : public QObject
{
    Q_OBJECT

public:
    cMainLoop(int &argc, char **argv);;

    int startMainLoop();

    void update(float dt);
    void render();
    void processInput();

public slots:
    void stopMainLoop();

private:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    uint32_t getMonitorRefreshRate() const;

private:
    std::atomic<bool> m_running = false;
    float m_msPerUpdate = 0.0f;
    float m_previousTime = 0.0f;
    float m_currentTime = 0.0f;
    float m_elapsed = 0.0f;
    float m_lag = 0.0f;

    QApplication m_app;
    cMainWindow m_window;
    cOpenGLWidget* m_glWidget = nullptr;
    cEngineCore m_engine;
};
