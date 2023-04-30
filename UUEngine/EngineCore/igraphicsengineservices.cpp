#include "igraphicsengineservices.h"

IGraphicsEngineServices::IGraphicsEngineServices()
{

}

IGraphicsEngineServices::IGraphicsEngineServices(QOpenGLFunctions *functions) : m_functions(functions)
{

}
