/********************************************************************************
** Form generated from reading UI file 'expertwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPERTWINDOW_H
#define UI_EXPERTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExpertWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *navLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *updateInfoButton;
    QPushButton *suggestButton;
    QScrollArea *cropArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *cropsLayout;
    QLabel *emptyLabel;
    QPushButton *refreshButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ExpertWindow)
    {
        if (ExpertWindow->objectName().isEmpty())
            ExpertWindow->setObjectName("ExpertWindow");
        ExpertWindow->resize(800, 600);
        centralwidget = new QWidget(ExpertWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        navLayout = new QHBoxLayout();
        navLayout->setSpacing(20);
        navLayout->setObjectName("navLayout");
        navLayout->setContentsMargins(20, 0, 20, 0);
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        navLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");
        subtitleLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

        navLayout->addWidget(subtitleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        navLayout->addItem(horizontalSpacer);

        updateInfoButton = new QPushButton(centralwidget);
        updateInfoButton->setObjectName("updateInfoButton");

        navLayout->addWidget(updateInfoButton);

        suggestButton = new QPushButton(centralwidget);
        suggestButton->setObjectName("suggestButton");

        navLayout->addWidget(suggestButton);


        mainLayout->addLayout(navLayout);

        cropArea = new QScrollArea(centralwidget);
        cropArea->setObjectName("cropArea");
        cropArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        cropArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        cropArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 788, 470));
        cropsLayout = new QVBoxLayout(scrollAreaWidgetContents);
        cropsLayout->setSpacing(15);
        cropsLayout->setObjectName("cropsLayout");
        cropsLayout->setContentsMargins(20, 15, 20, 15);
        emptyLabel = new QLabel(scrollAreaWidgetContents);
        emptyLabel->setObjectName("emptyLabel");
        emptyLabel->setAlignment(Qt::AlignCenter);

        cropsLayout->addWidget(emptyLabel);

        cropArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(cropArea);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        mainLayout->addWidget(refreshButton);

        ExpertWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ExpertWindow);
        statusbar->setObjectName("statusbar");
        ExpertWindow->setStatusBar(statusbar);

        retranslateUi(ExpertWindow);

        QMetaObject::connectSlotsByName(ExpertWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ExpertWindow)
    {
        ExpertWindow->setWindowTitle(QCoreApplication::translate("ExpertWindow", "\344\270\223\345\256\266\347\256\241\347\220\206\345\271\263\345\217\260", nullptr));
        ExpertWindow->setStyleSheet(QCoreApplication::translate("ExpertWindow", "background-color: #f5f7fa;", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"            font-size: 22px;\n"
"            font-weight: bold;\n"
"            color: #2c3e50;\n"
"          ", nullptr));
        titleLabel->setText(QCoreApplication::translate("ExpertWindow", "\344\270\223\345\256\266\347\256\241\347\220\206\345\271\263\345\217\260", nullptr));
        subtitleLabel->setStyleSheet(QCoreApplication::translate("ExpertWindow", "font-size: 13px; color: #888; margin-bottom: 2px;", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("ExpertWindow", "\345\247\223\345\220\215\357\274\214\344\275\240\345\245\275\357\274\201", nullptr));
        updateInfoButton->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"            QPushButton {\n"
"              background-color: #3498db;\n"
"              color: white;\n"
"              border-radius: 6px;\n"
"              padding: 10px 20px;\n"
"              font-size: 14px;\n"
"              font-weight: bold;\n"
"              border: none;\n"
"            }\n"
"            QPushButton:hover {\n"
"              background-color: #2980b9;\n"
"            }\n"
"          ", nullptr));
        updateInfoButton->setText(QCoreApplication::translate("ExpertWindow", "\344\270\252\344\272\272\344\277\241\346\201\257\347\256\241\347\220\206", nullptr));
        suggestButton->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"            QPushButton {\n"
"              background-color: #27ae60;\n"
"              color: white;\n"
"              border-radius: 6px;\n"
"              padding: 10px 20px;\n"
"              font-size: 14px;\n"
"              font-weight: bold;\n"
"              border: none;\n"
"            }\n"
"            QPushButton:hover {\n"
"              background-color: #219653;\n"
"            }\n"
"          ", nullptr));
        suggestButton->setText(QCoreApplication::translate("ExpertWindow", "\347\273\231\347\263\273\347\273\237\346\235\245\347\202\271\345\273\272\350\256\256\357\274\237", nullptr));
        cropArea->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"         QScrollArea {\n"
"           border: none;\n"
"           background: transparent;\n"
"         }\n"
"         QScrollBar:vertical {\n"
"           border: none;\n"
"           background: #f0f4f8;\n"
"           width: 8px;\n"
"           margin: 0;\n"
"         }\n"
"         QScrollBar::handle:vertical {\n"
"           background: #cbd2d9;\n"
"           border-radius: 4px;\n"
"         }\n"
"         QScrollBar::add-line:vertical, \n"
"         QScrollBar::sub-line:vertical {\n"
"           height: 0;\n"
"         }\n"
"       ", nullptr));
        emptyLabel->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"             color: #95a5a6;\n"
"             font-size: 14px;\n"
"             padding: 30px;\n"
"           ", nullptr));
        emptyLabel->setText(QCoreApplication::translate("ExpertWindow", "\346\232\202\346\227\240\344\275\234\347\211\251\345\214\272\345\212\250\346\200\201\357\274\214\347\263\273\347\273\237\345\260\206\345\256\236\346\227\266\346\216\250\351\200\201\346\234\200\346\226\260\344\275\234\347\211\251\345\214\272\344\277\241\346\201\257", nullptr));
        refreshButton->setText(QCoreApplication::translate("ExpertWindow", "\345\210\267\346\226\260", nullptr));
        refreshButton->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
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
        statusbar->setStyleSheet(QCoreApplication::translate("ExpertWindow", "\n"
"      background: #f0f4f8;\n"
"      color: #7f8c8d;\n"
"      padding: 0 10px;\n"
"    ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExpertWindow: public Ui_ExpertWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPERTWINDOW_H
