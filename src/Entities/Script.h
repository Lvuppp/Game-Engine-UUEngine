#ifndef SCRIPT_H
#define SCRIPT_H

#include "EngineEntities/BaseEngineObject.h"
#include <QRunnable>

using UpdateFunction = void (*)(cBaseEngineObject *);

class cScript : public QThread
{
    Q_OBJECT
public:
    cScript(cBaseEngineObject *object, QFunctionPointer script);

    void run() override;
    bool isInterruptionRequested() const;

signals:
    void updateScene();

public slots:
    void requestInterruption();

private:
    UpdateFunction m_updateFunction;
    cBaseEngineObject *m_object;

    mutable QMutex m_mutex;
    bool m_interrupted = false;
};

#endif // SCRIPT_H
