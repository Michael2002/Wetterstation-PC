/********************************************************************************
** Form generated from reading UI file 'wetterstation.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WETTERSTATION_H
#define UI_WETTERSTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WetterstationClass
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *_plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WetterstationClass)
    {
        if (WetterstationClass->objectName().isEmpty())
            WetterstationClass->setObjectName(QStringLiteral("WetterstationClass"));
        WetterstationClass->resize(600, 400);
        centralWidget = new QWidget(WetterstationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        _plainTextEdit = new QPlainTextEdit(centralWidget);
        _plainTextEdit->setObjectName(QStringLiteral("_plainTextEdit"));
        _plainTextEdit->setGeometry(QRect(310, 10, 171, 291));
        WetterstationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WetterstationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        WetterstationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WetterstationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WetterstationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WetterstationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WetterstationClass->setStatusBar(statusBar);

        retranslateUi(WetterstationClass);

        QMetaObject::connectSlotsByName(WetterstationClass);
    } // setupUi

    void retranslateUi(QMainWindow *WetterstationClass)
    {
        WetterstationClass->setWindowTitle(QApplication::translate("WetterstationClass", "Wetterstation", 0));
    } // retranslateUi

};

namespace Ui {
    class WetterstationClass: public Ui_WetterstationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WETTERSTATION_H
