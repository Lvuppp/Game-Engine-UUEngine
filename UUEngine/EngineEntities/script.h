#ifndef SCRIPT_H
#define SCRIPT_H

#include "EngineEntities/baseengineobject.h"
#include <QRunnable>

using UpdateFunction = void (*)(BaseEngineObject *);

class Script : public QThread
{
    Q_OBJECT
public:
    Script(BaseEngineObject *object, QFunctionPointer script);

    void run() override;
    bool isInterruptionRequested() const;

signals:
    void updateScene();

public slots:
    void requestInterruption();

private:
    UpdateFunction m_updateFunction;
    BaseEngineObject *m_object;

    mutable QMutex mutex;
    bool interrupted = false;
};

#endif // SCRIPT_H
