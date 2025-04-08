#include "MainLoop.h"

#include "Core/Cores/EngineCore.h"
#include "Utils/TimeFacade.h"

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <qcoreevent.h>

void cMainLoop::startMainLoop()
{
    m_running = true;
    m_msPerUpdate = 1000.0f / getMonitorRefreshRate();

    m_previousTime = time_facade::getCurrentTime<float>();
    m_lag = 0.0f;
    m_currentTime = time_facade::getCurrentTime<float>();
    m_elapsed = m_currentTime - m_previousTime;

    while (m_running)
    {
        m_currentTime = time_facade::getCurrentTime<float>();
        m_elapsed = m_currentTime - m_previousTime;
        m_previousTime = m_currentTime;
        m_lag += m_elapsed;

        processInput();

        while (m_lag >= m_msPerUpdate)
        {
            update(m_msPerUpdate);
            m_lag -= m_msPerUpdate;
        }

        render();
    }
}

void cMainLoop::stopMainLoop()
{
    m_running = false;
}

void cMainLoop::update(float dt)
{
    m_engine->update(dt);
//    m_window->update();
}

void cMainLoop::render()
{
    m_engine->render();
//    m_window->render();
}

void cMainLoop::processInput()
{
}

uint32_t cMainLoop::getMonitorRefreshRate() const
{
    auto *screen = QApplication::primaryScreen();
    if (screen != nullptr)
    {
        return screen->refreshRate();
    }
    return 60u;
}
