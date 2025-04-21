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
    , m_window()
    , m_engine()
{
    QObject::connect(&m_app, &QApplication::aboutToQuit, this, &cMainLoop::stopMainLoop);

    m_window.show();
    m_glWidget = m_window.getOpenGLWigdet();

    const auto window = m_glWidget->size();

    m_engine.initGraphicsEngine();
    m_engine.initInputEngine(sVec2(window));
}

int cMainLoop::startMainLoop()
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
    m_glWidget->makeCurrent();
    m_engine.render();
    m_glWidget->doneCurrent();
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
