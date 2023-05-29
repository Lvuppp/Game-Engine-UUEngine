#include "objectinfo.h"
#include "ui_objectinfo.h"

ObjectInfo::ObjectInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInfo)
{
    ui->setupUi(this);
    m_engine = EngineCore::getInstance();

    connect(m_engine, &EngineCore::emitObject, this , &ObjectInfo::setObject);
}

ObjectInfo::~ObjectInfo()
{
    delete ui;
}

void ObjectInfo::setObject(BaseEngineObject *object)
{
    auto coords = object->coordinates();

    ui->xCoordLineEdit->setText(QString::number(coords.x()));
    ui->yCoordLineEdit->setText(QString::number(coords.y()));
    ui->zCoordLineEdit->setText(QString::number(coords.z()));


    emit updateWindow();
}

