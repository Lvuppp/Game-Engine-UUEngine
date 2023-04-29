#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "baseengineobject.h"
#include "vertexdata.h"

#include <QImage>

class Base3DGameObject : public BaseEngineObject
{
public:
    Base3DGameObject(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

    Base3DGameObject(
        const QVector<VertexData> &vertexes,
        const QVector<GLuint> &indexes,
        const QImage &texture,
        const float &ambiendFactor = 0.1f,
        const float &specularFactor = 10.0f,
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

    ~Base3DGameObject();

    QOpenGLTexture* texture();
    void setTexture(const QImage &newTexture);

    QOpenGLBuffer* vertexesBuffer();
    void setVertexesBuffer(const QVector<VertexData> &newVertexes);

    QOpenGLBuffer* indexesBuffer();
    void setIndexesBuffer(const QVector<GLuint> &newIndexes);

    float specularFactor() const;
    void setSpecularFactor(float newSpecularFactor);

    float ambiendFactor() const;
    void setAmbiendFactor(float newAmbiendFactor);

    virtual float g() = 0;

protected:
    QOpenGLBuffer s_vertexes;
    QOpenGLBuffer s_indexes;
    QOpenGLTexture *s_texture;

    float s_specularFactor;
    float s_ambiendFactor;
};
#endif // BASE3DGAMEOBJECT_H
