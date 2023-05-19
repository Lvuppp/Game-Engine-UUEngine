#ifndef CAMERA_H
#define CAMERA_H

#include "baseengineobject.h"

class Camera : public BaseEngineObject
{
public:
    Camera();
    ~Camera();


    void addScript(QString);
    QVector<QString> scripts();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0) override;

private:
    QVector<QString> m_scriptsNames;

};

#endif // CAMERA_H
