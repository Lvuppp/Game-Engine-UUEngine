#include "script.h"

Script::Script(BaseEngineObject *object, QFunctionPointer script)
{
    m_object = object;
    m_updateFunction = reinterpret_cast<UpdateFunction>(script);

}
void Script::run()
{
    while(!isInterruptionRequested()){
        QMutexLocker locker(&mutex);
        m_updateFunction(m_object);
        emit updateScene();
    }
}


void Script::requestInterruption()
{
    interrupted = true;
}

bool Script::isInterruptionRequested() const
{
    QMutexLocker locker(&mutex);
    return interrupted;
}
