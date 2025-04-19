#include "ProjectCreator.h"
#include "ui_projectCreator.h"

cProjectCreator::cProjectCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectCreator)
{
    ui->setupUi(this);
    m_fileRegex = QRegularExpression("[\\/\\:\\*\\?\"\\<\\>\\|]");
}

cProjectCreator::~cProjectCreator()
{
    delete ui;
}

void cProjectCreator::accept()
{
    std::string projectPath = ui->folderPathLine->text().toStdString();
    std::string projectName = ui->projectNameLine->text().toStdString();
    QDir dir(QString::fromStdString(projectPath));

    if (!projectPath.empty() && !projectName.empty() && dir.exists() &&
        !dir.exists(QString::fromStdString(projectName)) &&
        !m_fileRegex.match(QString::fromStdString(projectName)).hasMatch()) {

        emit getFolderPath(projectPath + " " + projectName);
        QDialog::accept();
    } else {
        ui->errorLabel->setText("Can`t create project! Try again!");
    }
}

void cProjectCreator::on_findFolderButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(nullptr, "Выберите папку", "", QFileDialog::ShowDirsOnly);
    ui->folderPathLine->setText(path);
}


