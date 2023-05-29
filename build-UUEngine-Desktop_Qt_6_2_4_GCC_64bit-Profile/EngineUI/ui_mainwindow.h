/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionClose;
    QAction *actionCreate;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QFrame *objectParamsFrame;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *cameraMove;
    QPushButton *moveButton;
    QPushButton *rotateButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QOpenGLWidget *openGLWidget;
    QFrame *projectHierarchyFrame;
    QFrame *directories;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuGoofy;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1204, 662);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 56, 70);"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setCheckable(true);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("folder-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionOpen->setIcon(icon);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setCheckable(true);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("folder-new");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave->setIcon(icon1);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave_as->setCheckable(true);
        QIcon icon2;
        iconThemeName = QString::fromUtf8("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionSave_as->setIcon(icon2);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setCheckable(true);
        QIcon icon3;
        iconThemeName = QString::fromUtf8("folder-visiting");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionClose->setIcon(icon3);
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionCreate->setCheckable(true);
        actionCreate->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        objectParamsFrame = new QFrame(centralwidget);
        objectParamsFrame->setObjectName(QString::fromUtf8("objectParamsFrame"));
        objectParamsFrame->setStyleSheet(QString::fromUtf8("background-color : rgb(65, 65, 75);"));
        objectParamsFrame->setFrameShape(QFrame::StyledPanel);
        objectParamsFrame->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(objectParamsFrame, 1, 2, 1, 1);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMaximumSize(QSize(16777215, 16777215));
        frame_3->setStyleSheet(QString::fromUtf8("background-color : rgb(65, 65, 75);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(frame_3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cameraMove = new QPushButton(frame_3);
        cameraMove->setObjectName(QString::fromUtf8("cameraMove"));
        cameraMove->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(cameraMove);

        moveButton = new QPushButton(frame_3);
        moveButton->setObjectName(QString::fromUtf8("moveButton"));
        moveButton->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(moveButton);

        rotateButton = new QPushButton(frame_3);
        rotateButton->setObjectName(QString::fromUtf8("rotateButton"));
        rotateButton->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(rotateButton);

        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(frame_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(pushButton_4);


        gridLayout_2->addWidget(frame_3, 0, 1, 1, 1);

        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(800, 400));

        gridLayout_2->addWidget(openGLWidget, 1, 1, 1, 1);

        projectHierarchyFrame = new QFrame(centralwidget);
        projectHierarchyFrame->setObjectName(QString::fromUtf8("projectHierarchyFrame"));
        projectHierarchyFrame->setStyleSheet(QString::fromUtf8("background-color : rgb(65, 65, 75);"));
        projectHierarchyFrame->setFrameShape(QFrame::StyledPanel);
        projectHierarchyFrame->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(projectHierarchyFrame, 2, 2, 1, 1);

        directories = new QFrame(centralwidget);
        directories->setObjectName(QString::fromUtf8("directories"));
        directories->setStyleSheet(QString::fromUtf8("background-color : rgb(65, 65, 75);"));
        directories->setFrameShape(QFrame::StyledPanel);
        directories->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(directories, 2, 1, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 2, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 30);
        gridLayout_2->setRowStretch(2, 15);
        gridLayout_2->setColumnStretch(1, 30);
        gridLayout_2->setColumnStretch(2, 15);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1204, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuGoofy = new QMenu(menubar);
        menuGoofy->setObjectName(QString::fromUtf8("menuGoofy"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuGoofy->menuAction());
        menuFile->addAction(actionCreate);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionCreate->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
#if QT_CONFIG(shortcut)
        actionCreate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        cameraMove->setText(QString());
        moveButton->setText(QString());
        rotateButton->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start game", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Project", nullptr));
        menuGoofy->setTitle(QCoreApplication::translate("MainWindow", "Goofy sounds", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
