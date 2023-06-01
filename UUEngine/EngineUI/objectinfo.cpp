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

    if(ui->specificalParams->layout() != nullptr)
        delete ui->specificalParams->layout();

    ui->specificalParams->update();
    repaint();

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

    ui->scaleLineEdit->setText(QString::number(m_currentObject->scale()));

    ui->scriptsLabel->setText(m_engine->getScripts(m_objectName).join(' '));

    if(m_currentObject->objectType() == ObjectType::GameObject &&
        (*object)->model()->modelType() == ModelType::SimpleModel){
        loadSpecificParams();
    }

    emit updateWindow();
}


void ObjectInfo::loadSpecificParams()
{
    QLayout *layout = new QVBoxLayout();

    auto model = m_engine->getModel(m_objectName);

    QRegularExpression paramsRegex("(\\w*)\\((.*?)\\)");
    QRegularExpressionMatchIterator matchIterator = paramsRegex.globalMatch(model);
    QRegularExpressionMatch matchObject = matchIterator.next();

    if(matchObject.captured(1) == "CUBE"){
        auto params = matchObject.captured(2).split(' ');

        auto widthLabel = new QLabel("width:");
        layout->addWidget(widthLabel);

        auto width = new QLineEdit();
        width->setText(params[0]);
        layout->addWidget(width);

        auto heightLabel = new QLabel("height:");
        layout->addWidget(heightLabel);

        auto height = new QLineEdit();
        height->setText(params[1]);
        layout->addWidget(height);

        auto depthLabel = new QLabel("depth:");
        layout->addWidget(depthLabel);

        auto depth = new QLineEdit();
        depth->setText(params[2]);
        layout->addWidget(depth);

        auto changeCube =[this, width, height, depth](){
            m_engine->changeCube(m_objectName, width->text().toFloat(), height->text().toFloat(), depth->text().toFloat());
        };

        connect(width, &QLineEdit::editingFinished,changeCube);
        connect(height, &QLineEdit::editingFinished,changeCube);
        connect(depth, &QLineEdit::editingFinished, changeCube);

    }
    else if(matchObject.captured(1) == "SPHERE"){
        auto params = matchObject.captured(2).split(' ');
        auto radiusLabel = new QLabel("radius:");
        layout->addWidget(radiusLabel);

        auto radius = new QLineEdit();
        radius->setText(params[0]);
        layout->addWidget(radius);

        auto ringsLabel = new QLabel("rings:");
        layout->addWidget(ringsLabel);

        auto rings = new QLineEdit();
        rings->setText(params[1]);
        layout->addWidget(rings);

        auto sectorsLabel = new QLabel("depth:");
        layout->addWidget(sectorsLabel);

        auto sectors = new QLineEdit();
        sectors->setText(params[2]);
        layout->addWidget(sectors);

        auto changeSphere =[this, radius, rings, sectors](){
            m_engine->changeSphere(m_objectName, radius->text().toFloat(), rings->text().toInt(), sectors->text().toInt());
        };

        connect(radius, &QLineEdit::editingFinished,changeSphere);
        connect(rings, &QLineEdit::editingFinished,changeSphere);
        connect(sectors, &QLineEdit::editingFinished, changeSphere);
    }


    auto diffuseTextureButton = new QPushButton();
    auto normalTextureButton = new QPushButton();

    diffuseTextureButton->setText("Set diffuse map");
    normalTextureButton->setText("Set normal map");

    connect(diffuseTextureButton, &QPushButton::clicked, [this](){
        auto imagePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");
        if(imagePath == "") return;
        m_engine->setDiffuseTexture(m_objectName, imagePath);
    });

    connect(normalTextureButton, &QPushButton::clicked, [this](){
        auto imagePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");
        if(imagePath == "") return;
        m_engine->setNormalTexture(m_objectName, imagePath);
    });

    layout->addWidget(diffuseTextureButton);
    layout->addWidget(normalTextureButton);

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
    auto xCoord = ui->xCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(m_objectName, QVector3D(xCoord, 0.0f, 0.0f));
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
    emit updateWindow();
}


void ObjectInfo::on_xRotate_sliderMoved(int position)
{
    ui->xRotate->setValue(position);
    emit updateWindow();
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

