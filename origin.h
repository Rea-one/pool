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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QWidget *Welcome;
    QPushButton *acts;
    QWidget *Activaties;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTabWidget *sidebar;
    QWidget *gfile_tree;
    QGridLayout *gridLayout_3;
    QStackedWidget *wfile;
    QWidget *file_welcome;
    QGridLayout *gridLayout_4;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QWidget *file_tree_page;
    QGridLayout *gridLayout_5;
    QTreeView *file_tree;
    QWidget *glogics;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QTextBrowser *textBrowser_2;
    QTextEdit *editer;
    QGroupBox *scripts;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(694, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        steps = new QStackedWidget(centralwidget);
        steps->setObjectName("steps");
        Welcome = new QWidget();
        Welcome->setObjectName("Welcome");
        acts = new QPushButton(Welcome);
        acts->setObjectName("acts");
        acts->setGeometry(QRect(350, 180, 88, 26));
        steps->addWidget(Welcome);
        Activaties = new QWidget();
        Activaties->setObjectName("Activaties");
        gridLayout_2 = new QGridLayout(Activaties);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        splitter = new QSplitter(Activaties);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        sidebar = new QTabWidget(splitter);
        sidebar->setObjectName("sidebar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebar->sizePolicy().hasHeightForWidth());
        sidebar->setSizePolicy(sizePolicy);
        sidebar->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        sidebar->setTabPosition(QTabWidget::TabPosition::West);
        sidebar->setTabShape(QTabWidget::TabShape::Rounded);
        sidebar->setTabsClosable(false);
        sidebar->setMovable(false);
        sidebar->setTabBarAutoHide(true);
        gfile_tree = new QWidget();
        gfile_tree->setObjectName("gfile_tree");
        gridLayout_3 = new QGridLayout(gfile_tree);
        gridLayout_3->setObjectName("gridLayout_3");
        wfile = new QStackedWidget(gfile_tree);
        wfile->setObjectName("wfile");
        file_welcome = new QWidget();
        file_welcome->setObjectName("file_welcome");
        gridLayout_4 = new QGridLayout(file_welcome);
        gridLayout_4->setObjectName("gridLayout_4");
        textBrowser = new QTextBrowser(file_welcome);
        textBrowser->setObjectName("textBrowser");

        gridLayout_4->addWidget(textBrowser, 0, 0, 1, 1);

        groupBox = new QGroupBox(file_welcome);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        gridLayout_4->addWidget(groupBox, 1, 0, 1, 1);

        wfile->addWidget(file_welcome);
        file_tree_page = new QWidget();
        file_tree_page->setObjectName("file_tree_page");
        gridLayout_5 = new QGridLayout(file_tree_page);
        gridLayout_5->setObjectName("gridLayout_5");
        file_tree = new QTreeView(file_tree_page);
        file_tree->setObjectName("file_tree");

        gridLayout_5->addWidget(file_tree, 0, 0, 1, 1);

        wfile->addWidget(file_tree_page);

        gridLayout_3->addWidget(wfile, 0, 0, 1, 1);

        sidebar->addTab(gfile_tree, QString());
        glogics = new QWidget();
        glogics->setObjectName("glogics");
        sidebar->addTab(glogics, QString());
        splitter->addWidget(sidebar);
        horizontalLayoutWidget = new QWidget(splitter);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        textBrowser_2 = new QTextBrowser(horizontalLayoutWidget);
        textBrowser_2->setObjectName("textBrowser_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser_2->sizePolicy().hasHeightForWidth());
        textBrowser_2->setSizePolicy(sizePolicy1);
        textBrowser_2->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_4->addWidget(textBrowser_2);

        editer = new QTextEdit(horizontalLayoutWidget);
        editer->setObjectName("editer");
        editer->setEnabled(true);
        sizePolicy.setHeightForWidth(editer->sizePolicy().hasHeightForWidth());
        editer->setSizePolicy(sizePolicy);
        editer->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);

        horizontalLayout_4->addWidget(editer);

        splitter->addWidget(horizontalLayoutWidget);

        verticalLayout->addWidget(splitter);

        scripts = new QGroupBox(Activaties);
        scripts->setObjectName("scripts");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scripts->sizePolicy().hasHeightForWidth());
        scripts->setSizePolicy(sizePolicy2);
        scripts->setMinimumSize(QSize(0, 60));
        scripts->setMaximumSize(QSize(16777215, 60));
        scripts->setAutoFillBackground(false);
        pushButton_2 = new QPushButton(scripts);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(12, 33, 20, 20));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy3);
        pushButton_2->setMinimumSize(QSize(20, 20));
        pushButton_2->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(scripts);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        steps->addWidget(Activaties);

        gridLayout->addWidget(steps, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 694, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(acts, SIGNAL(clicked()), MainWindow, SLOT(enter()));
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(to_file_tree()));

        steps->setCurrentIndex(0);
        sidebar->setCurrentIndex(0);
        wfile->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        acts->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\233\256\345\211\215\346\262\241\346\234\211\351\200\211\346\213\251\346\226\207\344\273\266\350\267\257\345\276\204\357\274\214\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271\344\273\245\347\273\247\347\273\255</p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        sidebar->setTabText(sidebar->indexOf(gfile_tree), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        sidebar->setTabText(sidebar->indexOf(glogics), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        scripts->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ORIGIN_H
