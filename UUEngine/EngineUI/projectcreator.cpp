#include "projectcreator.h"
#include "ui_projectcreator.h"

ProjectCreator::ProjectCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectCreator)
{
    ui->setupUi(this);
    m_fileRegex = QRegularExpression("[\\/\\:\\*\\?\"\\<\\>\\|]");
}

ProjectCreator::~ProjectCreator()
{
    delete ui;
}


void ProjectCreator::accept()
{
    QString projectPath = ui->folderPathLine->text(), projectName = ui->projectNameLine->text();
    QDir dir(projectPath);

    if(projectPath != "" && projectName != "" &&dir.exists() &&
        !dir.exists(projectName) && !projectName.contains(m_fileRegex)){

        emit getFolderPath(QString("%1 %2").arg(projectPath, projectName));
        QDialog::accept();
    }
    else{

        ui->errorLabel->setText("Can`t create project! Try again!");
    }
}


void ProjectCreator::on_findFolderButton_clicked()
{

    auto path = QFileDialog::getExistingDirectory(nullptr, "Выберите папку", "", QFileDialog::ShowDirsOnly);
    ui->folderPathLine->setText(path);
}


