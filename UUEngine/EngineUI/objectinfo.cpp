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

    if(ui->specificalParams->layout() != nullptr)
        delete ui->specificalParams->layout();

    if(m_currentObject->objectType() == ObjectType::GameObject &&
        (*object)->model()->modelType() == ModelType::SimpleModel){
        loadSpecificParams();
    }

    emit updateWindow();
}


void ObjectInfo::loadSpecificParams()
{
    if(ui->specificalParams->layout() != nullptr)
        delete ui->specificalParams->layout();

    QLayout *layout = new QVBoxLayout();

    auto model = m_engine->getModel(m_objectName);

    QRegularExpression paramsRegex("(\\w*)\\((.*?)\\)");
    QRegularExpressionMatchIterator matchIterator = paramsRegex.globalMatch(model);
    QRegularExpressionMatch matchObject = matchIterator.next();

    if(matchObject.captured(1) == "CUBE"){
        auto widthLabel = new QLabel("width:");
        layout->addWidget(widthLabel);

        auto width = new QLineEdit();
        layout->addWidget(width);

        auto heightLabel = new QLabel("height:");
        layout->addWidget(heightLabel);

        auto height = new QLineEdit();
        layout->addWidget(height);

        auto depthLabel = new QLabel("depth:");
        layout->addWidget(depthLabel);

        auto depth = new QLineEdit();
        layout->addWidget(depth);

        auto changeCube =[&](){
            m_engine->createCube(m_objectName, width->text().toFloat(), height->text().toFloat(), depth->text().toFloat());
        };

        connect(width, &QLineEdit::editingFinished,this, changeCube);
        connect(height, &QLineEdit::editingFinished,this, changeCube);
        connect(depth, &QLineEdit::editingFinished,this, changeCube);

    }

    ui->specificalParams->setLayout(layout);

}


void ObjectInfo::on_yCoordLineEdit_editingFinished()
{
    bool state;
    auto yCoord = ui->yCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(m_objectName, QVector3D(0.0f, yCoord, 0.0f));
    }
    emit updateWindow();
}


void ObjectInfo::on_addScriptButton_clicked()
{
    auto path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.so*)");
    m_engine->loadScript(m_objectName, path);
}


void ObjectInfo::on_xCoordLineEdit_textChanged(const QString &arg1)
{
    emit updateWindow();
    ui->xCoordLineEdit->setText(arg1);
}


void ObjectInfo::on_xCoordLineEdit_textEdited(const QString &arg1)
{
    emit updateWindow();
    ui->xCoordLineEdit->setText(arg1);
}


void ObjectInfo::on_xCoordLineEdit_editingFinished()
{
    bool state;
    auto yCoord = ui->xCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(m_objectName, QVector3D(0.0f, yCoord, 0.0f));
    }
    emit updateWindow();
}

void ObjectInfo::on_scaleLineEdit_editingFinished()
{
    bool state;
    auto scale = ui->scaleLineEdit->text().toFloat(&state);
    if(state){
        m_engine->scaleObject(m_objectName, scale);
    }

    emit updateWindow();
}


void ObjectInfo::on_xCoordLineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->xCoordLineEdit->setCursorPosition(arg2);
    emit updateWindow();
}


void ObjectInfo::on_yRotate_sliderMoved(int position)
{
    ui->yRotate->setValue(position);
}


void ObjectInfo::on_xRotate_sliderMoved(int position)
{
    ui->xRotate->setValue(position);
}


void ObjectInfo::on_xRotate_valueChanged(int value)
{
    m_engine->rotateXObject(m_objectName, QQuaternion::fromAxisAndAngle(QVector3D(1.0f,0.0f,0.0f),value));

    emit updateWindow();
}


void ObjectInfo::on_yRotate_valueChanged(int value)
{
    m_engine->rotateYObject(m_objectName, QQuaternion::fromAxisAndAngle(QVector3D(0.0f,1.0f,0.0f),value));

    emit updateWindow();
}


void ObjectInfo::on_zCoordLineEdit_editingFinished()
{
    bool state;
    auto zCoord = ui->zCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(m_objectName, QVector3D(0.0f, 0.0f, zCoord));
    }
    emit updateWindow();
}

