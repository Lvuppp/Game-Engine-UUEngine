#pragma once

#include <QObject>

#include <atomic>
#include <cstdint>
#include <memory>

class cEngineCore;
class QMainWindow;

class cMainLoop : public QObject
{
    Q_OBJECT

public:
    void startMainLoop();
    void stopMainLoop();

    void update(float dt);
    void render();
    void processInput();

private:
    uint32_t getMonitorRefreshRate() const;

private:
    std::atomic<bool> m_running = false;
    float m_msPerUpdate = 0.0f;
    float m_previousTime = 0.0f;
    float m_lag = 0.0f;
    float m_currentTime = 0.0f;
    float m_elapsed = 0.0f;

    std::unique_ptr<cEngineCore> m_engine = nullptr;
    std::unique_ptr<QMainWindow> m_window = nullptr;
};
