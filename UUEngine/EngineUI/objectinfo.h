#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include "EngineEntities/baseengineobject.h"
#include "Cores/enginecore.h"

#include <QWidget>

namespace Ui {
class ObjectInfo;
}

class ObjectInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectInfo(QWidget *parent = nullptr);
    ~ObjectInfo();

signals:
    void updateWindow();

public slots:
    void setObject(const QString &objectName, Base3DGameObject **object);

private slots:
    void on_yCoordLineEdit_editingFinished();

private:
    Ui::ObjectInfo *ui;

    EngineCore *m_engine;
    BaseEngineObject *m_currentObject;
    QString m_objectName;
};

#endif // OBJECTINFO_H
