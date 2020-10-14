/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "QVideoWidget"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVideoWidget *container;
    QListWidget *listCamera;
    QLabel *camName;
    QLabel *distance;
    QWidget *tab_2;
    QListWidget *settingWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *applyButton;
    QLabel *label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1119, 619);
        MainWindow->setAutoFillBackground(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1101, 601));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        container = new QVideoWidget(tab);
        container->setObjectName(QStringLiteral("container"));
        container->setGeometry(QRect(10, 30, 821, 521));
        container->setAutoFillBackground(false);
        listCamera = new QListWidget(tab);
        listCamera->setObjectName(QStringLiteral("listCamera"));
        listCamera->setGeometry(QRect(850, 10, 231, 551));
        camName = new QLabel(tab);
        camName->setObjectName(QStringLiteral("camName"));
        camName->setGeometry(QRect(10, 10, 391, 17));
        distance = new QLabel(tab);
        distance->setObjectName(QStringLiteral("distance"));
        distance->setGeometry(QRect(660, 10, 171, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        settingWidget = new QListWidget(tab_2);
        settingWidget->setObjectName(QStringLiteral("settingWidget"));
        settingWidget->setGeometry(QRect(20, 20, 881, 481));
        settingWidget->setSortingEnabled(true);
        addButton = new QPushButton(tab_2);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(920, 10, 171, 24));
        deleteButton = new QPushButton(tab_2);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setGeometry(QRect(920, 50, 171, 24));
        saveButton = new QPushButton(tab_2);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(920, 90, 171, 24));
        applyButton = new QPushButton(tab_2);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        applyButton->setGeometry(QRect(920, 230, 171, 24));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 510, 321, 51));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        camName->setText(QApplication::translate("MainWindow", "Camera Identifier :", nullptr));
        distance->setText(QApplication::translate("MainWindow", "Distance :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Video Stream", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "Add Item", nullptr));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete Item", nullptr));
        saveButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        applyButton->setText(QApplication::translate("MainWindow", "Apply", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt;\">Note that Camera Name and IP Address is delimited by &quot;\\&quot;: </span></p><p><span style=\" font-size:8pt;\">Formatting Camera Item. Example &lt;NameOfCamera&gt;\\&lt;IPAddress&gt;.</span></p><p><br/></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
