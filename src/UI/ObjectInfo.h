#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include "EngineEntities/BaseEngineObject.h"
#include "Cores/EngineCore.h"

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class ObjectInfo;
}

class cObjectInfo : public QWidget
{
    Q_OBJECT

public:
    explicit cObjectInfo(QWidget *parent = nullptr);
    ~cObjectInfo();

signals:
    void updateWindow();
    void updateFrame(QLayout* layout);

public slots:
    void setObject(const QString &objectName, cBase3DGameObject **object);

private slots:
    void on_yCoordLineEdit_editingFinished();
    void on_addScriptButton_clicked();
    void on_xCoordLineEdit_textChanged(const QString &arg1);
    void on_xCoordLineEdit_textEdited(const QString &arg1);
    void on_xCoordLineEdit_editingFinished();
    void on_scaleLineEdit_editingFinished();
    void on_xCoordLineEdit_cursorPositionChanged(int arg1, int arg2);
    void on_zCoordLineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    void loadSpecificParams();

private:
    Ui::ObjectInfo *ui;

    cEngineCore *m_engine;
    cBaseEngineObject *m_currentObject;
    QString m_objectName;
};

#endif // OBJECTINFO_H
