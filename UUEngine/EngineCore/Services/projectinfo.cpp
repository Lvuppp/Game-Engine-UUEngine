#include "projectinfo.h"

QString ProjectInfo::m_projectPath ="";
QString ProjectInfo::m_projectName ="";


ProjectInfo::ProjectInfo()
{

}

QString ProjectInfo::projectName()
{
    return m_projectName;
}


QString ProjectInfo::projectPath()
{
    return m_projectPath;
}
