/********************************************************************************
** Form generated from reading UI file 'projectcreator.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTCREATOR_H
#define UI_PROJECTCREATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProjectCreator
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *info;
    QLabel *errorLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *projectNameLabel;
    QLineEdit *projectNameLine;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *folderPathLine;
    QPushButton *findFolderButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProjectCreator)
    {
        if (ProjectCreator->objectName().isEmpty())
            ProjectCreator->setObjectName(QString::fromUtf8("ProjectCreator"));
        ProjectCreator->resize(400, 300);
        ProjectCreator->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 56, 70);"));
        verticalLayout = new QVBoxLayout(ProjectCreator);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        info = new QLabel(ProjectCreator);
        info->setObjectName(QString::fromUtf8("info"));
        info->setStyleSheet(QString::fromUtf8("color: #fff;\n"
"font: 800 21pt \"Cantarell\";"));

        verticalLayout->addWidget(info);

        errorLabel = new QLabel(ProjectCreator);
        errorLabel->setObjectName(QString::fromUtf8("errorLabel"));

        verticalLayout->addWidget(errorLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        projectNameLabel = new QLabel(ProjectCreator);
        projectNameLabel->setObjectName(QString::fromUtf8("projectNameLabel"));

        horizontalLayout->addWidget(projectNameLabel);

        projectNameLine = new QLineEdit(ProjectCreator);
        projectNameLine->setObjectName(QString::fromUtf8("projectNameLine"));

        horizontalLayout->addWidget(projectNameLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(ProjectCreator);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        folderPathLine = new QLineEdit(ProjectCreator);
        folderPathLine->setObjectName(QString::fromUtf8("folderPathLine"));

        horizontalLayout_2->addWidget(folderPathLine);

        findFolderButton = new QPushButton(ProjectCreator);
        findFolderButton->setObjectName(QString::fromUtf8("findFolderButton"));

        horizontalLayout_2->addWidget(findFolderButton);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(ProjectCreator);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProjectCreator);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ProjectCreator, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ProjectCreator, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ProjectCreator);
    } // setupUi

    void retranslateUi(QDialog *ProjectCreator)
    {
        ProjectCreator->setWindowTitle(QCoreApplication::translate("ProjectCreator", "Dialog", nullptr));
        info->setText(QCoreApplication::translate("ProjectCreator", "Create Project", nullptr));
        errorLabel->setText(QString());
        projectNameLabel->setText(QCoreApplication::translate("ProjectCreator", "Project name:", nullptr));
        label->setText(QCoreApplication::translate("ProjectCreator", "Folder: ", nullptr));
        findFolderButton->setText(QCoreApplication::translate("ProjectCreator", "Find folder...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectCreator: public Ui_ProjectCreator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCREATOR_H
