#include "lighting.h"


Lighting::Lighting() : BaseEngineObject() , m_lightPower(5.0f), m_isLightingDynamic(false)
{

}

Lighting::~Lighting()
{

}

void Lighting::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    shaderProgram->setUniformValue("u_isDrawDynamic", m_isLightingDynamic);// освещение динамическое или статическое
    shaderProgram->setUniformValue("u_eyePosition", QVector4D(coordinates(), 1.0f)); // позиция наблюдателя
    shaderProgram->setUniformValue("u_lightPosition", QVector4D(0.0,0.0,0.0,1.0)); // позиция источника света
    shaderProgram->setUniformValue("u_lightPower", m_lightPower); // сила свечения
}
