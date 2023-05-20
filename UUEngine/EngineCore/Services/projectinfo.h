#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <QString>

class ProjectInfo
{
public:
    ProjectInfo();

    static QString projectName();

    static QString projectPath();

private:
    //friend class ProjectProcessor;

    static QString m_projectName;
    static QString m_projectPath;


};

#endif // PROJECTINFO_H
