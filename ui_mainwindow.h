/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jan 12 19:00:53 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir_une_image;
    QAction *actionEnregistrer_l_image;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_1;
    QPushButton *pushButton_go;
    QGraphicsView *graphicsView_img;
    QSlider *Slider;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(723, 482);
        actionOuvrir_une_image = new QAction(MainWindow);
        actionOuvrir_une_image->setObjectName(QString::fromUtf8("actionOuvrir_une_image"));
        actionEnregistrer_l_image = new QAction(MainWindow);
        actionEnregistrer_l_image->setObjectName(QString::fromUtf8("actionEnregistrer_l_image"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton_1 = new QRadioButton(centralWidget);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));

        verticalLayout->addWidget(radioButton_1);

        pushButton_go = new QPushButton(centralWidget);
        pushButton_go->setObjectName(QString::fromUtf8("pushButton_go"));

        verticalLayout->addWidget(pushButton_go);


        horizontalLayout_3->addLayout(verticalLayout);

        graphicsView_img = new QGraphicsView(centralWidget);
        graphicsView_img->setObjectName(QString::fromUtf8("graphicsView_img"));
        graphicsView_img->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

        horizontalLayout_3->addWidget(graphicsView_img);


        verticalLayout_2->addLayout(horizontalLayout_3);

        Slider = new QSlider(centralWidget);
        Slider->setObjectName(QString::fromUtf8("Slider"));
        Slider->setMaximum(500);
        Slider->setSliderPosition(250);
        Slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Slider);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 723, 23));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionOuvrir_une_image);
        menuMenu->addAction(actionEnregistrer_l_image);
        menuMenu->addSeparator();
        menuMenu->addAction(actionQuitter);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOuvrir_une_image->setText(QApplication::translate("MainWindow", "Ouvrir une image...", 0, QApplication::UnicodeUTF8));
        actionOuvrir_une_image->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_l_image->setText(QApplication::translate("MainWindow", "Enregistrer l'image...", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_l_image->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter.", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Methode 2", 0, QApplication::UnicodeUTF8));
        radioButton_1->setText(QApplication::translate("MainWindow", "Methode 1", 0, QApplication::UnicodeUTF8));
        pushButton_go->setText(QApplication::translate("MainWindow", "Go", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
