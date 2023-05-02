#ifndef CAMERA_H
#define CAMERA_H

#include "baseengineobject.h"

class Camera : public BaseEngineObject
{
public:
    Camera(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);
    ~Camera();

    void setModel(QVector<Model *>models) override;
    void setModel(Model *models)  override;


    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

};

#endif // CAMERA_H
