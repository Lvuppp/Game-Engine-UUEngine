#include "Script.h"

cScript::cScript(cBaseEngineObject *object, QFunctionPointer script)
{
    m_object = object;
    m_updateFunction = reinterpret_cast<UpdateFunction>(script);

}
void cScript::run()
{
    while(!isInterruptionRequested()){
        QMutexLocker locker(&m_mutex);
        m_updateFunction(m_object);
        emit updateScene();
    }
}


void cScript::requestInterruption()
{
    m_interrupted = true;
}

bool cScript::isInterruptionRequested() const
{
    QMutexLocker locker(&m_mutex);
    return m_interrupted;
}
