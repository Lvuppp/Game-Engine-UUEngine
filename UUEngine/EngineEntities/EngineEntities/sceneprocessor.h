#ifndef SCENEPROCESSOR_H
#define SCENEPROCESSOR_H

#include "scene.h"

#include <QString>

class SceneProcessor
{
public:
    Scene *setCurrentScene(const QString &sceneName);
    Scene *currentScene();

public:
    static SceneProcessor *getInstance(QHash<QString, Scene *> &scenes);

private:
    Scene *m_currentScene;
    QHash<QString, Scene *> m_scenes;

private:
    SceneProcessor(QHash<QString, Scene*> &scenes);
    ~SceneProcessor();

    SceneProcessor(const SceneProcessor&) = delete;
    SceneProcessor& operator=(const SceneProcessor&) = delete;

    static SceneProcessor* m_instance;
};
#endif // SCENEPROCESSOR_H
