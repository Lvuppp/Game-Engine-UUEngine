#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "baseengineobject.h"
#include "model.h"

#include <QImage>
#include <QVector3D>

enum class ModelType{
    Cube,
    Pyramide,
    CustomeModel
};
// надо отвязать от этого модель и скрипты, сделать так чтобы модель была независима от объекта и скрипты,
// скрипты более менее понятно(сделать скрипт фолдер туда объекты к скриптам подвязывать, или хотябы название,
// по которым уже можно будет найти и скрипт и модель
class Base3DGameObject : public BaseEngineObject
{
public:
    Base3DGameObject();
    Base3DGameObject(ModelType modelType, QVector<Model *>models, QString modelPath = "");
    Base3DGameObject(ModelType modelType, Model *models, QString modelPath = "");

    ~Base3DGameObject();

    void addScript(QString);

    QVector<QString> scripts();
    QVector<Model *> model();
    QString modelPath();
    ModelType modelType();

    void setModel(ModelType modelType, QVector<Model *>models, QString modelPath = "");
    void setModel(ModelType modelType, Model *models, QString modelPath = "");

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

private:
    QVector<Model *> m_modelParticulars;
    QVector<QString> m_scriptsName;

    ModelType m_modelType;
    QString m_modelPath;
};
#endif // BASE3DGAMEOBJECT_H
