#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "base3dgameobject.h"

#include <QDir>
#include <dlfcn.h>

// В данный момент он довольно таки примитивный, но он старается :)

class ScriptEngine
{
public:
    ~ScriptEngine();

    void loadScript(Base3DGameObject *object);


    static ScriptEngine *getInstance();

private:
    QDir currentDirectory;


private:
    ScriptEngine();

    ScriptEngine(const ScriptEngine&) = delete;
    ScriptEngine& operator=(const ScriptEngine&) = delete;

    static ScriptEngine *m_instance;
};

#endif // SCRIPTENGINE_H
