#include "Lighting.h"


cLighting::cLighting() : cBaseEngineObject() , m_lightPower(5.0f), m_isLightingDynamic(false)
{
    m_objectType = ObjectType::Lighting;
}

cLighting::~cLighting()
{

}

void cLighting::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    shaderProgram->setUniformValue("u_isDrawDynamic", m_isLightingDynamic);// освещение динамическое или статическое
    shaderProgram->setUniformValue("u_eyePosition", QVector4D(coordinates(), 1.0f)); // позиция наблюдателя
    shaderProgram->setUniformValue("u_lightPosition", QVector4D(0.0,0.0,0.0,1.0)); // позиция источника света
    shaderProgram->setUniformValue("u_lightPower", m_lightPower); // сила свечения
}
