#pragma once

#include "Core/Cores/EngineCore.h"
#include "UI/EngineOpenGLWidget.h"
#include "UI/MainWindow.h"

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
    inline uint32_t getCurrentTime() const;

private:
    std::atomic<bool> m_running = false;
    uint32_t m_previousTime = 0.0f;
    uint32_t m_currentTime = 0.0f;
    float m_msPerUpdate = 0.0f;
    float m_elapsed = 0.0f;
    float m_lag = 0.0f;

    QApplication m_app;
    cEngineCore m_engine;
    cMainWindow m_window;
    cEngineOpenGLWidget* m_glWidget = nullptr;
};
