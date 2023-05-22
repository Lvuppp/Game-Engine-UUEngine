#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <QString>

class ProjectProcessor;

class ProjectInfo
{
public:
    ProjectInfo();
    friend class ProjectProcessor;

    static QString projectName();
    static QString projectPath();

private:

    static QString m_projectName;
    static QString m_projectPath;

private:
};

#endif // PROJECTINFO_H
