/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *loginFrame;
    QVBoxLayout *loginLayout;
    QHBoxLayout *closeLayout;
    QSpacerItem *closeSpacer;
    QPushButton *pushButtonClose;
    QLabel *labelTitle;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelPhone;
    QLineEdit *lineEditPhone;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QLabel *labelRole;
    QComboBox *comboBoxRole;
    QHBoxLayout *buttonLayout;
    QPushButton *pushButtonLogin;
    QPushButton *pushButtonRegister;
    QPushButton *pushButtonSwitchMode;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("\n"
"     QWidget#centralwidget {\n"
"         background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f5f6fa, stop:1 #e9ecef);\n"
"     }\n"
"    "));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        loginFrame = new QFrame(centralwidget);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setMinimumSize(QSize(320, 340));
        loginFrame->setMaximumSize(QSize(16777215, 16777215));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginFrame->sizePolicy().hasHeightForWidth());
        loginFrame->setSizePolicy(sizePolicy);
        loginFrame->setStyleSheet(QString::fromUtf8("\n"
"        QFrame#loginFrame {\n"
"            background: #fff;\n"
"            border-radius: 20px;\n"
"            border: 1px solid #e0e0e0;\n"
"            box-shadow: 0 4px 24px rgba(60,60,60,0.08);\n"
"        }\n"
"       "));
        loginFrame->setFrameShape(QFrame::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Raised);
        loginLayout = new QVBoxLayout(loginFrame);
        loginLayout->setSpacing(12);
        loginLayout->setObjectName("loginLayout");
        loginLayout->setContentsMargins(24, 24, 24, 24);
        closeLayout = new QHBoxLayout();
        closeLayout->setObjectName("closeLayout");
        closeSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        closeLayout->addItem(closeSpacer);

        pushButtonClose = new QPushButton(loginFrame);
        pushButtonClose->setObjectName("pushButtonClose");
        pushButtonClose->setMinimumSize(QSize(24, 24));
        pushButtonClose->setMaximumSize(QSize(24, 24));
        pushButtonClose->setStyleSheet(QString::fromUtf8("\n"
"             QPushButton {\n"
"                 background: transparent;\n"
"                 color: #888;\n"
"                 font-size: 20px;\n"
"                 border: none;\n"
"                 border-radius: 12px;\n"
"             }\n"
"             QPushButton:hover {\n"
"                 background: #f44336;\n"
"                 color: #fff;\n"
"             }\n"
"            "));

        closeLayout->addWidget(pushButtonClose);


        loginLayout->addLayout(closeLayout);

        labelTitle = new QLabel(loginFrame);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setMinimumSize(QSize(0, 80));
        labelTitle->setMaximumSize(QSize(16777215, 80));
        labelTitle->setStyleSheet(QString::fromUtf8("\n"
"           font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"           font-size: 32px;\n"
"           font-weight: bold;\n"
"           color: #1b5e20;\n"
"           margin-bottom: 18px;\n"
"          "));
        labelTitle->setAlignment(Qt::AlignCenter);

        loginLayout->addWidget(labelTitle);

        labelName = new QLabel(loginFrame);
        labelName->setObjectName("labelName");
        labelName->setStyleSheet(QString::fromUtf8("font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif; font-size: 15px; color: #555;"));

        loginLayout->addWidget(labelName);

        lineEditName = new QLineEdit(loginFrame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setStyleSheet(QString::fromUtf8("\n"
"           font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"           border: 1px solid #bdbdbd;\n"
"           border-radius: 8px;\n"
"           padding-left: 10px;\n"
"           font-size: 16px;\n"
"           min-height: 38px;\n"
"          "));

        loginLayout->addWidget(lineEditName);

        labelPhone = new QLabel(loginFrame);
        labelPhone->setObjectName("labelPhone");
        labelPhone->setStyleSheet(QString::fromUtf8("font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif; font-size: 15px; color: #555;"));

        loginLayout->addWidget(labelPhone);

        lineEditPhone = new QLineEdit(loginFrame);
        lineEditPhone->setObjectName("lineEditPhone");
        lineEditPhone->setStyleSheet(QString::fromUtf8("\n"
"           font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"           border: 1px solid #bdbdbd;\n"
"           border-radius: 8px;\n"
"           padding-left: 10px;\n"
"           font-size: 16px;\n"
"           min-height: 38px;\n"
"          "));

        loginLayout->addWidget(lineEditPhone);

        labelPassword = new QLabel(loginFrame);
        labelPassword->setObjectName("labelPassword");
        labelPassword->setStyleSheet(QString::fromUtf8("font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif; font-size: 15px; color: #555;"));

        loginLayout->addWidget(labelPassword);

        lineEditPassword = new QLineEdit(loginFrame);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setStyleSheet(QString::fromUtf8("\n"
"           font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"           border: 1px solid #bdbdbd;\n"
"           border-radius: 8px;\n"
"           padding-left: 10px;\n"
"           font-size: 16px;\n"
"           min-height: 38px;\n"
"          "));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        loginLayout->addWidget(lineEditPassword);

        labelRole = new QLabel(loginFrame);
        labelRole->setObjectName("labelRole");
        labelRole->setStyleSheet(QString::fromUtf8("font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif; font-size: 15px; color: #555;"));

        loginLayout->addWidget(labelRole);

        comboBoxRole = new QComboBox(loginFrame);
        comboBoxRole->addItem(QString());
        comboBoxRole->addItem(QString());
        comboBoxRole->addItem(QString());
        comboBoxRole->setObjectName("comboBoxRole");
        comboBoxRole->setStyleSheet(QString::fromUtf8("\n"
"           font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"           border: 1px solid #bdbdbd;\n"
"           border-radius: 8px;\n"
"           font-size: 16px;\n"
"           padding-left: 10px;\n"
"           min-height: 38px;\n"
"           background: #fff;\n"
"          "));

        loginLayout->addWidget(comboBoxRole);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(12);
        buttonLayout->setObjectName("buttonLayout");
        pushButtonLogin = new QPushButton(loginFrame);
        pushButtonLogin->setObjectName("pushButtonLogin");
        pushButtonLogin->setMinimumWidth(100);
        pushButtonLogin->setMaximumWidth(180);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonLogin->sizePolicy().hasHeightForWidth());
        pushButtonLogin->setSizePolicy(sizePolicy1);
        pushButtonLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"background-color: #43a047;\n"
"color: #fff;\n"
"border-radius: 8px;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"min-height: 38px;\n"
"padding-left: 24px;\n"
"padding-right: 24px;\n"
"}\n"
"QPushButton:hover {\n"
"  background-color: #388e3c;\n"
"  border: 2px solid #66bb6a;\n"
"}"));

        buttonLayout->addWidget(pushButtonLogin);

        pushButtonRegister = new QPushButton(loginFrame);
        pushButtonRegister->setObjectName("pushButtonRegister");
        pushButtonRegister->setMinimumWidth(100);
        pushButtonRegister->setMaximumWidth(180);
        sizePolicy1.setHeightForWidth(pushButtonRegister->sizePolicy().hasHeightForWidth());
        pushButtonRegister->setSizePolicy(sizePolicy1);
        pushButtonRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"background-color: #1976d2;\n"
"color: #fff;\n"
"border-radius: 8px;\n"
"font-size: 18px;\n"
"font-weight: bold;\n"
"min-height: 38px;\n"
"padding-left: 24px;\n"
"padding-right: 24px;\n"
"}\n"
"QPushButton:hover {\n"
"  background-color: #1565c0;\n"
"  border: 2px solid #42a5f5;\n"
"}"));

        buttonLayout->addWidget(pushButtonRegister);


        loginLayout->addLayout(buttonLayout);

        pushButtonSwitchMode = new QPushButton(loginFrame);
        pushButtonSwitchMode->setObjectName("pushButtonSwitchMode");
        pushButtonSwitchMode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font-family: '\345\276\256\350\275\257\351\233\205\351\273\221', 'Microsoft YaHei', sans-serif;\n"
"background: transparent;\n"
"color: #1976d2;\n"
"border: none;\n"
"font-size: 15px;\n"
"text-decoration: underline;\n"
"font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"  color: #0d47a1;\n"
"  text-decoration: underline;\n"
"}"));

        loginLayout->addWidget(pushButtonSwitchMode);


        verticalLayout->addWidget(loginFrame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\231\272\346\205\247\345\206\234\344\270\232\347\231\273\345\275\225", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonClose->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        labelTitle->setText(QCoreApplication::translate("MainWindow", "\346\231\272\346\205\247\345\206\234\344\270\232\345\271\263\345\217\260", nullptr));
        labelName->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        labelPhone->setText(QCoreApplication::translate("MainWindow", "\346\211\213\346\234\272\345\217\267", nullptr));
        labelPassword->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        labelRole->setText(QCoreApplication::translate("MainWindow", "\350\247\222\350\211\262", nullptr));
        comboBoxRole->setItemText(0, QCoreApplication::translate("MainWindow", "\345\206\234\346\210\267", nullptr));
        comboBoxRole->setItemText(1, QCoreApplication::translate("MainWindow", "\344\270\223\345\256\266", nullptr));
        comboBoxRole->setItemText(2, QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230", nullptr));

        pushButtonLogin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        pushButtonRegister->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        pushButtonSwitchMode->setText(QCoreApplication::translate("MainWindow", "\346\262\241\346\234\211\350\264\246\345\217\267\357\274\237\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
