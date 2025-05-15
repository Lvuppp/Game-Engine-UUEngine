#include "ObjectCreatorDialog.h"
#include "ui_ObjectCreatorDialog.h"

ObjectCreatorDialog::ObjectCreatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectCreatorDialog)
{
    ui->setupUi(this);
}

ObjectCreatorDialog::~ObjectCreatorDialog()
{
    delete ui;
}

void ObjectCreatorDialog::accept()
{
    QDialog::accept();
}