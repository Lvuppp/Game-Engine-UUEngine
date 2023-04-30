#ifndef SCENE_H
#define SCENE_H

#include "base3dgameobject.h"
#include "camera.h"
#include "lighting.h"

class Scene
{

public:
    Scene();
    ~Scene();

    Base3DGameObject *addGameObject(
        const QVector<VertexData> &vertexes,
        const QVector<GLuint> &indexes,
        const QImage &texture,
        const float &ambiendFactor = 0.1f,
        const float &specularFactor = 10.0f,
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

    Camera * addCamera(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);
    //void addPhysicsObject();

// добавить добавление объектов камеры и света, а также добавить назначенеи текущей камеры.

    Camera *camera() const;
//    void setCamera(const Camera &newCamera);

    QVector<Lighting*> lighings() const;

//    void setLighing(const Lighting &newLighing);

    QVector<Base3DGameObject *> gameObjects() const;

    Camera *currentCamera() const;
    void setCurrentCamera(Camera *newCurrentCamera);

private:
    Camera *m_currentCamera;
    QVector<Base3DGameObject *> m_gameObjects;
    QVector<Camera *> m_cameras;
    QVector<Lighting *> m_lightings;
};

#endif // SCENE_H
