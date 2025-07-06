/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QScrollArea *adviceArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *adviceLayout;
    QLabel *emptyLabel;
    QPushButton *pushButton_refresh;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(800, 600);
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(titleLabel);

        adviceArea = new QScrollArea(centralwidget);
        adviceArea->setObjectName("adviceArea");
        adviceArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        adviceArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        adviceArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 780, 420));
        adviceLayout = new QVBoxLayout(scrollAreaWidgetContents);
        adviceLayout->setSpacing(15);
        adviceLayout->setObjectName("adviceLayout");
        adviceLayout->setContentsMargins(20, 15, 20, 15);
        emptyLabel = new QLabel(scrollAreaWidgetContents);
        emptyLabel->setObjectName("emptyLabel");
        emptyLabel->setAlignment(Qt::AlignCenter);

        adviceLayout->addWidget(emptyLabel);

        adviceArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(adviceArea);

        pushButton_refresh = new QPushButton(centralwidget);
        pushButton_refresh->setObjectName("pushButton_refresh");

        mainLayout->addWidget(pushButton_refresh);

        AdminWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdminWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        AdminWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdminWindow);
        statusbar->setObjectName("statusbar");
        AdminWindow->setStatusBar(statusbar);

        retranslateUi(AdminWindow);

        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "\347\263\273\347\273\237\344\274\230\345\214\226\345\273\272\350\256\256", nullptr));
        AdminWindow->setStyleSheet(QCoreApplication::translate("AdminWindow", "background-color: #f5f7fa;", nullptr));
        titleLabel->setText(QCoreApplication::translate("AdminWindow", "\347\263\273\347\273\237\344\274\230\345\214\226\345\273\272\350\256\256", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("AdminWindow", "font-size: 22px; font-weight: bold; color: #2c3e50; margin: 20px 0 10px 0;", nullptr));
        adviceArea->setStyleSheet(QCoreApplication::translate("AdminWindow", "\n"
"         QScrollArea { border: none; background: transparent; }\n"
"         QScrollBar:vertical { border: none; background: #f0f4f8; width: 8px; margin: 0; }\n"
"         QScrollBar::handle:vertical { background: #cbd2d9; border-radius: 4px; }\n"
"         QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }\n"
"       ", nullptr));
        emptyLabel->setText(QCoreApplication::translate("AdminWindow", "\346\232\202\346\227\240\347\263\273\347\273\237\344\274\230\345\214\226\345\273\272\350\256\256", nullptr));
        emptyLabel->setStyleSheet(QCoreApplication::translate("AdminWindow", "color: #95a5a6; font-size: 14px; padding: 30px;", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("AdminWindow", "\345\210\267\346\226\260", nullptr));
        pushButton_refresh->setStyleSheet(QCoreApplication::translate("AdminWindow", "\n"
"        QPushButton {\n"
"          background-color: #3498db;\n"
"          color: white;\n"
"          border-radius: 6px;\n"
"          padding: 10px 20px;\n"
"          font-size: 14px;\n"
"          font-weight: bold;\n"
"          border: none;\n"
"        }\n"
"        QPushButton:hover {\n"
"          background-color: #2980b9;\n"
"        }\n"
"        QPushButton:pressed {\n"
"          background-color: #21618c;\n"
"        }\n"
"       ", nullptr));
        statusbar->setStyleSheet(QCoreApplication::translate("AdminWindow", "background: #f0f4f8; color: #7f8c8d; padding: 0 10px;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
