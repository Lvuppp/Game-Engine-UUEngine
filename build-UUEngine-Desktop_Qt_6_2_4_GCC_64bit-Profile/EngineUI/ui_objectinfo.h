/********************************************************************************
** Form generated from reading UI file 'objectinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTINFO_H
#define UI_OBJECTINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectInfo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *defaultParams;
    QVBoxLayout *verticalLayout_2;
    QLabel *coordinates;
    QFormLayout *formLayout;
    QLabel *x;
    QLabel *y;
    QLabel *z;
    QLineEdit *zCoordLineEdit;
    QLineEdit *yCoordLineEdit;
    QLineEdit *xCoordLineEdit;
    QLabel *rotation;
    QFormLayout *formLayout_4;
    QLabel *xr;
    QLineEdit *xRotateLineEdit;
    QLabel *yr;
    QLineEdit *yRotateLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *scale;
    QLineEdit *scaleLineEdit;
    QFrame *specificalParams;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addScriptButton;

    void setupUi(QWidget *ObjectInfo)
    {
        if (ObjectInfo->objectName().isEmpty())
            ObjectInfo->setObjectName(QString::fromUtf8("ObjectInfo"));
        ObjectInfo->resize(370, 326);
        verticalLayout = new QVBoxLayout(ObjectInfo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        defaultParams = new QHBoxLayout();
        defaultParams->setObjectName(QString::fromUtf8("defaultParams"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        coordinates = new QLabel(ObjectInfo);
        coordinates->setObjectName(QString::fromUtf8("coordinates"));

        verticalLayout_2->addWidget(coordinates);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        x = new QLabel(ObjectInfo);
        x->setObjectName(QString::fromUtf8("x"));

        formLayout->setWidget(1, QFormLayout::LabelRole, x);

        y = new QLabel(ObjectInfo);
        y->setObjectName(QString::fromUtf8("y"));

        formLayout->setWidget(2, QFormLayout::LabelRole, y);

        z = new QLabel(ObjectInfo);
        z->setObjectName(QString::fromUtf8("z"));

        formLayout->setWidget(3, QFormLayout::LabelRole, z);

        zCoordLineEdit = new QLineEdit(ObjectInfo);
        zCoordLineEdit->setObjectName(QString::fromUtf8("zCoordLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, zCoordLineEdit);

        yCoordLineEdit = new QLineEdit(ObjectInfo);
        yCoordLineEdit->setObjectName(QString::fromUtf8("yCoordLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, yCoordLineEdit);

        xCoordLineEdit = new QLineEdit(ObjectInfo);
        xCoordLineEdit->setObjectName(QString::fromUtf8("xCoordLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, xCoordLineEdit);


        verticalLayout_2->addLayout(formLayout);

        rotation = new QLabel(ObjectInfo);
        rotation->setObjectName(QString::fromUtf8("rotation"));

        verticalLayout_2->addWidget(rotation);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        xr = new QLabel(ObjectInfo);
        xr->setObjectName(QString::fromUtf8("xr"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, xr);

        xRotateLineEdit = new QLineEdit(ObjectInfo);
        xRotateLineEdit->setObjectName(QString::fromUtf8("xRotateLineEdit"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, xRotateLineEdit);

        yr = new QLabel(ObjectInfo);
        yr->setObjectName(QString::fromUtf8("yr"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, yr);

        yRotateLineEdit = new QLineEdit(ObjectInfo);
        yRotateLineEdit->setObjectName(QString::fromUtf8("yRotateLineEdit"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, yRotateLineEdit);


        verticalLayout_2->addLayout(formLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        scale = new QLabel(ObjectInfo);
        scale->setObjectName(QString::fromUtf8("scale"));

        horizontalLayout_3->addWidget(scale);

        scaleLineEdit = new QLineEdit(ObjectInfo);
        scaleLineEdit->setObjectName(QString::fromUtf8("scaleLineEdit"));

        horizontalLayout_3->addWidget(scaleLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);


        defaultParams->addLayout(verticalLayout_2);


        verticalLayout->addLayout(defaultParams);

        specificalParams = new QFrame(ObjectInfo);
        specificalParams->setObjectName(QString::fromUtf8("specificalParams"));
        specificalParams->setFrameShape(QFrame::StyledPanel);
        specificalParams->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(specificalParams);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        verticalLayout->addWidget(specificalParams);

        addScriptButton = new QPushButton(ObjectInfo);
        addScriptButton->setObjectName(QString::fromUtf8("addScriptButton"));

        verticalLayout->addWidget(addScriptButton);


        retranslateUi(ObjectInfo);

        QMetaObject::connectSlotsByName(ObjectInfo);
    } // setupUi

    void retranslateUi(QWidget *ObjectInfo)
    {
        ObjectInfo->setWindowTitle(QCoreApplication::translate("ObjectInfo", "Form", nullptr));
        coordinates->setText(QCoreApplication::translate("ObjectInfo", "Coordinates", nullptr));
        x->setText(QCoreApplication::translate("ObjectInfo", "x:", nullptr));
        y->setText(QCoreApplication::translate("ObjectInfo", "y:", nullptr));
        z->setText(QCoreApplication::translate("ObjectInfo", "z:", nullptr));
        rotation->setText(QCoreApplication::translate("ObjectInfo", "Rotation", nullptr));
        xr->setText(QCoreApplication::translate("ObjectInfo", "x:", nullptr));
        yr->setText(QCoreApplication::translate("ObjectInfo", "y:", nullptr));
        scale->setText(QCoreApplication::translate("ObjectInfo", "Scale:", nullptr));
        addScriptButton->setText(QCoreApplication::translate("ObjectInfo", "Add scripts", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectInfo: public Ui_ObjectInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTINFO_H
