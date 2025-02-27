/********************************************************************************
** Form generated from reading UI file 'origin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ORIGIN_H
#define ORIGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QStackedWidget *steps;
    QWidget *page_3;
    QPushButton *pushButton_5;
    QWidget *page_4;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QPushButton *gfile_tree;
    QPushButton *glogics;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QStackedWidget *sidebar;
    QWidget *page_2;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *messages;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QTreeView *file_tree;
    QWidget *logics;
    QTextEdit *editer;
    QGroupBox *groupBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        steps = new QStackedWidget(centralwidget);
        steps->setObjectName("steps");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        pushButton_5 = new QPushButton(page_3);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(350, 180, 88, 26));
        steps->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        gridLayout_5 = new QGridLayout(page_4);
        gridLayout_5->setObjectName("gridLayout_5");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        groupBox_2 = new QGroupBox(page_4);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setEnabled(true);
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName("verticalLayout");
        gfile_tree = new QPushButton(groupBox_2);
        gfile_tree->setObjectName("gfile_tree");

        verticalLayout->addWidget(gfile_tree);

        glogics = new QPushButton(groupBox_2);
        glogics->setObjectName("glogics");

        verticalLayout->addWidget(glogics);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBox_2);

        sidebar = new QStackedWidget(page_4);
        sidebar->setObjectName("sidebar");
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        gridLayout_3 = new QGridLayout(page_2);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName("groupBox");
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_4->addWidget(pushButton_2, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        messages = new QTextBrowser(page_2);
        messages->setObjectName("messages");

        gridLayout_3->addWidget(messages, 0, 0, 1, 1);

        sidebar->addWidget(page_2);
        page = new QWidget();
        page->setObjectName("page");
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setObjectName("gridLayout_2");
        file_tree = new QTreeView(page);
        file_tree->setObjectName("file_tree");

        gridLayout_2->addWidget(file_tree, 0, 0, 1, 1);

        sidebar->addWidget(page);
        logics = new QWidget();
        logics->setObjectName("logics");
        sidebar->addWidget(logics);

        horizontalLayout->addWidget(sidebar);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        editer = new QTextEdit(page_4);
        editer->setObjectName("editer");

        gridLayout_5->addWidget(editer, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(page_4);
        groupBox_3->setObjectName("groupBox_3");

        gridLayout_5->addWidget(groupBox_3, 1, 0, 1, 2);

        steps->addWidget(page_4);

        gridLayout->addWidget(steps, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(gfile_tree, SIGNAL(clicked()), MainWindow, SLOT(to_file_tree()));
        QObject::connect(glogics, SIGNAL(clicked()), MainWindow, SLOT(to_logics()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), MainWindow, SLOT(enter()));

        steps->setCurrentIndex(1);
        sidebar->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        gfile_tree->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        glogics->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\217\257\344\273\245\344\275\277\347\224\250\347\232\204\345\212\237\350\203\275", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ORIGIN_H
