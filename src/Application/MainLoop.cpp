#include "MainLoop.h"

#include "Core/Cores/EngineCore.h"
#include "Core/Services/ProjectProcessor.h"
#include "Utils/TimeFacade.h"

#include <QApplication>
#include <QOpenGLWidget>
#include <QScreen>
#include <qcoreevent.h>

#include <iostream>

cMainLoop::cMainLoop(int &argc, char **argv)
    : m_app(argc, argv)
    , m_engine()
    , m_window(&m_engine)
{
    QObject::connect(&m_app, &QApplication::aboutToQuit, this, &cMainLoop::stopMainLoop);

    m_window.show();
    m_glWidget = m_window.getOpenGLWigdet();
}

int cMainLoop::startMainLoop()
{
    m_running = true;
    m_msPerUpdate = 1000.0f / getMonitorRefreshRate();

    m_previousTime = getCurrentTime();

    while (m_running)
    {
        m_currentTime = getCurrentTime();
        m_elapsed = (m_currentTime - m_previousTime) * 0.000001f;
        m_previousTime = m_currentTime;
        m_lag += m_elapsed;

        processInput();


        while (m_lag >= m_msPerUpdate)
        {
            m_lag -= m_msPerUpdate;
            update(m_msPerUpdate);
        }

        render();
    }

    return 0;
}


bool cMainLoop::eventFilter(QObject* obj, QEvent* event)
{
    return QObject::eventFilter(obj, event);
}

void cMainLoop::stopMainLoop()
{
    m_running = false;
}

void cMainLoop::update(float dt)
{
    m_engine.update(dt);
}

void cMainLoop::render()
{
}

void cMainLoop::processInput()
{
    m_app.processEvents();
}

uint32_t cMainLoop::getMonitorRefreshRate() const
{
    auto screen = m_app.primaryScreen();
    if (screen != nullptr)
    {
        return screen->refreshRate();
    }
    return 60u;
}

inline uint32_t
cMainLoop::getCurrentTime() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
