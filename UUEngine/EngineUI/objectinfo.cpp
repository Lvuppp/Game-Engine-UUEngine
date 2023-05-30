#include "objectinfo.h"
#include "ui_objectinfo.h"

ObjectInfo::ObjectInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInfo)
{
    ui->setupUi(this);
    m_engine = EngineCore::getInstance();

    connect(m_engine, &EngineCore::emitObject, this , &ObjectInfo::setObject);

    ui->xRotate->setMinimum(0);
    ui->xRotate->setMaximum(360);

    ui->yRotate->setMinimum(0);
    ui->yRotate->setMaximum(360);
}

ObjectInfo::~ObjectInfo()
{
    delete ui;
}

void ObjectInfo::setObject(const QString &objectName, Base3DGameObject **object)
{
    if(object == nullptr) return;

    m_currentObject = *object;
    m_objectName = objectName;

    ui->objectLabel->setText(objectName);

    auto coords = m_currentObject->coordinates();
    float angleX, angleY;
    QVector3D axisX, axisY;

    m_currentObject->rotationX().getAxisAndAngle(&axisX,&angleX);
    m_currentObject->rotationY().getAxisAndAngle(&axisY,&angleY);

    ui->xCoordLineEdit->setText(QString::number(coords.x()));
    ui->yCoordLineEdit->setText(QString::number(coords.y()));
    ui->zCoordLineEdit->setText(QString::number(coords.z()));

    ui->xRotate->setValue(angleX);
    ui->xRotate->setValue(angleY);

    emit updateWindow();
}


void ObjectInfo::on_yCoordLineEdit_editingFinished()
{
    bool state;
    auto yCoord = ui->yCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(m_objectName, QVector3D(0.0f, yCoord, 0.0f));
    }
}

