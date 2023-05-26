#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <QString>

class ProjectProcessor;

class ProjectInfo
{
public:
    ProjectInfo();;

    static QString projectName();
    static QString projectPath();
    static QString projectFolder();

    friend class ProjectProcessor;
private:

    static QString m_projectName;
    static QString m_projectPath;
    static QString m_projectFolder;

private:
};

#endif // PROJECTINFO_H
