#ifndef BASEENGINEOBJECT_H
#define BASEENGINEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class QOpenGLShaderProgram;
class QOpenGLFunctions;

class cBaseEngineObject
{
public:
    cBaseEngineObject();
    cBaseEngineObject(uint32_t hash);
    virtual ~cBaseEngineObject() = default;

    uint32_t getId() const;

    bool isLocked() const;
    void lock();
    void unlock();

    float scale() const;
    QVector3D coordinates() const;
    QQuaternion rotationX() const;
    QQuaternion rotationY() const;
    QQuaternion rotation() const;
    QMatrix4x4 modelMatrix();

    void setCoordinates(const QVector3D &coordinates);
    void setRotateX(const QQuaternion &rotation);
    void setRotateY(const QQuaternion &rotation);
    void setScale(float scale);

    void translate(const QVector3D &coordinates);
    void rotate(const QQuaternion &rotation);
    void rotateX(const QQuaternion &rotation);
    void rotateY(const QQuaternion &rotation);
    void scale(float scale);

public:
    enum class ObjectType{
        GameObject,
        Camera,
        Lighting,
        SkyBox,
    };

    virtual ObjectType objectType() const;
    virtual void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture);

private:
    bool checkFlag();

protected:
    uint32_t m_id = 0;

    QMatrix4x4 m_modelMatrix;
    QVector3D m_coordinates;
    QQuaternion m_rotate;
    QQuaternion m_rotateX;
    QQuaternion m_rotateY;
    float m_scale = 0.0f;

    enum class Flags
    {
        Lock,
        RenderEnable
    };

    uint32_t m_flags = 0u;
};

#endif // BASEENGINEOBJECT_H
