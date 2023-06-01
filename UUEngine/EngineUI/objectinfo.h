#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include "EngineEntities/baseengineobject.h"
#include "Cores/enginecore.h"

#include <QWidget>
#include <QFileDialog>

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
    void updateFrame(QLayout* layout);

public slots:
    void setObject(const QString &objectName, Base3DGameObject **object);

private slots:
    void on_yCoordLineEdit_editingFinished();
    void on_addScriptButton_clicked();
    void on_xCoordLineEdit_textChanged(const QString &arg1);
    void on_xCoordLineEdit_textEdited(const QString &arg1);
    void on_xCoordLineEdit_editingFinished();
    void on_scaleLineEdit_editingFinished();
    void on_xCoordLineEdit_cursorPositionChanged(int arg1, int arg2);
    void on_yRotate_sliderMoved(int position);
    void on_xRotate_sliderMoved(int position);
    void on_xRotate_valueChanged(int value);
    void on_yRotate_valueChanged(int value);
    void on_zCoordLineEdit_editingFinished();

private:
    void loadSpecificParams();

private:
    Ui::ObjectInfo *ui;

    EngineCore *m_engine;
    BaseEngineObject *m_currentObject;
    QString m_objectName;
};

#endif // OBJECTINFO_H
