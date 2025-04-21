#include "ObjectInfo.h"
#include "ui_objectInfo.h"

#include "Utils/Hash.h"
#include "Utils/TextUtils.h"

#include <sstream>
#include <iterator>

cObjectInfo::cObjectInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInfo)
{
    ui->setupUi(this);
    //m_engine = cEngineCore::getInstance();

    //connect(m_engine, &cEngineCore::emitObject, this , &cObjectInfo::setObject);
}

cObjectInfo::~cObjectInfo()
{
    delete ui;
}

void cObjectInfo::setObject(const std::string &objectName, cBase3DGameObject **object)
{
    if(object == nullptr) return;

    // if(ui->specificalParams->layout() != nullptr)
    //     delete ui->specificalParams->layout();

    // ui->specificalParams->update();
    repaint();

    //m_currentObject = *object;
    m_objectName = objectName;

    //ui->objectLabel->setText(objectName);

    auto coords = m_currentObject->coordinates();
    ui->xCoordLineEdit->setText(QString::number(coords.x()));
    ui->yCoordLineEdit->setText(QString::number(coords.y()));
    ui->zCoordLineEdit->setText(QString::number(coords.z()));

    ui->scaleLineEdit->setText(QString::number(m_currentObject->scale()));

    setScriptsLabel();

    // if(m_currentObject->objectType() == ObjectType::GameObject &&
    //     (*object)->model()->modelType() == cModel::ModelType::SimpleModel){
    //     loadSpecificParams();
    // }


    emit updateWindow();
}

void cObjectInfo::updateCoordinates(const QVector3D &coords)
{
    ui->xCoordLineEdit->setText(QString::number(coords.x()));
    ui->yCoordLineEdit->setText(QString::number(coords.y()));
    ui->zCoordLineEdit->setText(QString::number(coords.z()));
}

void cObjectInfo::setScriptsLabel() {
    auto scripts = m_engine->getScripts(cHash::hash(m_objectName));
    ui->scriptsLabel->setText(QString::fromStdString(text_utils::join(scripts, ' ')));
}

void cObjectInfo::loadSpecificParams()
{
    QLayout *layout = new QVBoxLayout();

    auto model = QString::fromStdString(m_engine->getModel(cHash::hash(m_objectName)));

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
            m_engine->changeCube(cHash::hash(m_objectName), width->text().toFloat(), height->text().toFloat(), depth->text().toFloat());
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
            m_engine->changeSphere(cHash::hash(m_objectName), radius->text().toFloat(), rings->text().toInt(), sectors->text().toInt());
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
        onDiffuseTextureSet(imagePath);
    });

    connect(normalTextureButton, &QPushButton::clicked, [this](){
        auto imagePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (**)");
        if(imagePath == "") return;
        onNormalTextureSet(imagePath);
    });

    layout->addWidget(diffuseTextureButton);
    layout->addWidget(normalTextureButton);

    //ui->specificalParams->setLayout(layout);

}

void cObjectInfo::onDiffuseTextureSet(const QString &imagePath) {
    m_engine->setDiffuseTexture(cHash::hash(m_objectName), imagePath.toStdString());
}

void cObjectInfo::onNormalTextureSet(const QString &imagePath) {
    m_engine->setNormalTexture(cHash::hash(m_objectName), imagePath.toStdString());
}

void cObjectInfo::onScriptLoad(const QString &path) {
    m_engine->loadScript(cHash::hash(m_objectName), path.toStdString());
}

void cObjectInfo::on_yCoordLineEdit_editingFinished()
{
    bool state;
    auto yCoord = ui->yCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(cHash::hash(m_objectName), QVector3D(0.0f, yCoord, 0.0f));
    }
    emit updateWindow();
}


void cObjectInfo::on_addScriptButton_clicked()
{
    auto path = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "Все файлы (*.so*)");
    onScriptLoad(path);
}


void cObjectInfo::on_xCoordLineEdit_textChanged(const QString &arg1)
{
    emit updateWindow();
    ui->xCoordLineEdit->setText(arg1);
}


void cObjectInfo::on_xCoordLineEdit_textEdited(const QString &arg1)
{
    emit updateWindow();
    ui->xCoordLineEdit->setText(arg1);
}


void cObjectInfo::on_xCoordLineEdit_editingFinished()
{
    bool state;
    auto xCoord = ui->xCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(cHash::hash(m_objectName), QVector3D(xCoord, 0.0f, 0.0f));
    }
    emit updateWindow();
}

void cObjectInfo::on_scaleLineEdit_editingFinished()
{
    bool state;
    auto scale = ui->scaleLineEdit->text().toFloat(&state);
    if(state){
        m_engine->scaleObject(cHash::hash(m_objectName), scale);
    }

    emit updateWindow();
}


void cObjectInfo::on_xCoordLineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->xCoordLineEdit->setCursorPosition(arg2);
    emit updateWindow();
}






void cObjectInfo::on_zCoordLineEdit_editingFinished()
{
    bool state;
    auto zCoord = ui->zCoordLineEdit->text().toFloat(&state);
    if(state){
        m_engine->translateObject(cHash::hash(m_objectName), QVector3D(0.0f, 0.0f, zCoord));
    }
    emit updateWindow();
}


void cObjectInfo::on_pushButton_clicked()
{
    m_engine->deleteObject(cHash::hash(m_objectName));
}
