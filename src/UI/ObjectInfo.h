#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include "Entities/BaseEntities/BaseEngineObject.h"
#include "Core/Cores/EngineCore.h"

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
    void setObject(const std::string &objectName, cBase3DGameObject **object);

    void updateCoordinates(const QVector3D &coords);
    void setScriptsLabel();
    void onDiffuseTextureSet(const QString &imagePath);
    void onNormalTextureSet(const QString &imagePath);
    void onScriptLoad(const QString &path);

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
    std::string m_objectName;
};

#endif // OBJECTINFO_H
