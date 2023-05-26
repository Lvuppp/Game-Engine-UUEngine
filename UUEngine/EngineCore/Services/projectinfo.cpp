#include "projectinfo.h"

QString ProjectInfo::m_projectPath ="";
QString ProjectInfo::m_projectName ="";
QString ProjectInfo::m_projectFolder ="";


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

QString ProjectInfo::projectFolder()
{
    return m_projectFolder;
}
