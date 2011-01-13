/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jan 13 13:00:38 2011
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
#include <QtGui/QCheckBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOuvrir_une_image;
    QAction *actionEnregistrer_l_image;
    QAction *actionQuitter;
    QAction *actionEnregistrer_le_masque;
    QAction *actionOuvrir_un_masque;
    QAction *actionUtilisation;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_masque;
    QToolButton *toolButton_write;
    QSpinBox *spinBox_size;
    QToolButton *toolButton_erase;
    QPushButton *pushButton_clear;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_go;
    QCheckBox *checkBox_res;
    QGraphicsView *graphicsView_img;
    QSlider *Slider;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuAide;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 600);
        MainWindow->setMinimumSize(QSize(900, 600));
        actionOuvrir_une_image = new QAction(MainWindow);
        actionOuvrir_une_image->setObjectName(QString::fromUtf8("actionOuvrir_une_image"));
        actionEnregistrer_l_image = new QAction(MainWindow);
        actionEnregistrer_l_image->setObjectName(QString::fromUtf8("actionEnregistrer_l_image"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionEnregistrer_le_masque = new QAction(MainWindow);
        actionEnregistrer_le_masque->setObjectName(QString::fromUtf8("actionEnregistrer_le_masque"));
        actionOuvrir_un_masque = new QAction(MainWindow);
        actionOuvrir_un_masque->setObjectName(QString::fromUtf8("actionOuvrir_un_masque"));
        actionUtilisation = new QAction(MainWindow);
        actionUtilisation->setObjectName(QString::fromUtf8("actionUtilisation"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        checkBox_masque = new QCheckBox(widget);
        checkBox_masque->setObjectName(QString::fromUtf8("checkBox_masque"));
        checkBox_masque->setChecked(true);

        gridLayout->addWidget(checkBox_masque, 0, 0, 1, 1);

        toolButton_write = new QToolButton(widget);
        toolButton_write->setObjectName(QString::fromUtf8("toolButton_write"));

        gridLayout->addWidget(toolButton_write, 1, 0, 1, 1);

        spinBox_size = new QSpinBox(widget);
        spinBox_size->setObjectName(QString::fromUtf8("spinBox_size"));
        spinBox_size->setMinimum(1);
        spinBox_size->setMaximum(5);
        spinBox_size->setValue(3);

        gridLayout->addWidget(spinBox_size, 1, 1, 1, 1);

        toolButton_erase = new QToolButton(widget);
        toolButton_erase->setObjectName(QString::fromUtf8("toolButton_erase"));

        gridLayout->addWidget(toolButton_erase, 2, 0, 1, 1);

        pushButton_clear = new QPushButton(widget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        gridLayout->addWidget(pushButton_clear, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        radioButton_1 = new QRadioButton(widget);
        radioButton_1->setObjectName(QString::fromUtf8("radioButton_1"));
        radioButton_1->setChecked(true);

        verticalLayout->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        pushButton_go = new QPushButton(widget);
        pushButton_go->setObjectName(QString::fromUtf8("pushButton_go"));

        verticalLayout->addWidget(pushButton_go);

        checkBox_res = new QCheckBox(widget);
        checkBox_res->setObjectName(QString::fromUtf8("checkBox_res"));

        verticalLayout->addWidget(checkBox_res);


        horizontalLayout_3->addWidget(widget);

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
        menuBar->setGeometry(QRect(0, 0, 900, 23));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuAide->menuAction());
        menuMenu->addAction(actionOuvrir_une_image);
        menuMenu->addAction(actionEnregistrer_l_image);
        menuMenu->addAction(actionOuvrir_un_masque);
        menuMenu->addAction(actionEnregistrer_le_masque);
        menuMenu->addSeparator();
        menuMenu->addAction(actionQuitter);
        menuAide->addAction(actionUtilisation);
        menuAide->addSeparator();
        menuAide->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ct\302\262 Inpainting", 0, QApplication::UnicodeUTF8));
        actionOuvrir_une_image->setText(QApplication::translate("MainWindow", "Ouvrir une image...", 0, QApplication::UnicodeUTF8));
        actionOuvrir_une_image->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_l_image->setText(QApplication::translate("MainWindow", "Enregistrer l'image resultat...", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_l_image->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_le_masque->setText(QApplication::translate("MainWindow", "Enregistrer le masque...", 0, QApplication::UnicodeUTF8));
        actionOuvrir_un_masque->setText(QApplication::translate("MainWindow", "Ouvrir un masque...", 0, QApplication::UnicodeUTF8));
        actionUtilisation->setText(QApplication::translate("MainWindow", "Utilisation..", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        checkBox_masque->setText(QApplication::translate("MainWindow", "Afficher masque", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton_write->setToolTip(QApplication::translate("MainWindow", "Active le pinceau", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_write->setText(QApplication::translate("MainWindow", "Pinceau", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        spinBox_size->setToolTip(QApplication::translate("MainWindow", "Taille du pinceau", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        toolButton_erase->setToolTip(QApplication::translate("MainWindow", "Active la gomme", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton_erase->setText(QApplication::translate("MainWindow", "Gomme", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_clear->setToolTip(QApplication::translate("MainWindow", "Efface le masque", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_clear->setText(QApplication::translate("MainWindow", "Effacer masque", 0, QApplication::UnicodeUTF8));
        radioButton_1->setText(QApplication::translate("MainWindow", "Methode 1", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindow", "Methode 2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_go->setToolTip(QApplication::translate("MainWindow", "Lance l'inpainting", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_go->setText(QApplication::translate("MainWindow", "Go", 0, QApplication::UnicodeUTF8));
        checkBox_res->setText(QApplication::translate("MainWindow", "Afficher resultat", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        Slider->setToolTip(QApplication::translate("MainWindow", "Zoom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        Slider->setWhatsThis(QApplication::translate("MainWindow", "Zoom", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
        menuAide->setTitle(QApplication::translate("MainWindow", "Aide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
