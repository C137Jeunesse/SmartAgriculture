/********************************************************************************
** Form generated from reading UI file 'farmerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FARMERWINDOW_H
#define UI_FARMERWINDOW_H

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

class Ui_FarmerWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *navLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *updateInfoButton;
    QPushButton *viewSystemAdviceButton;
    QPushButton *suggestButton;
    QScrollArea *suggestionArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *suggestionsLayout;
    QLabel *emptyLabel;
    QPushButton *refreshButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FarmerWindow)
    {
        if (FarmerWindow->objectName().isEmpty())
            FarmerWindow->setObjectName("FarmerWindow");
        FarmerWindow->resize(800, 600);
        centralwidget = new QWidget(FarmerWindow);
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
        subtitleLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        navLayout->addWidget(subtitleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        navLayout->addItem(horizontalSpacer);

        updateInfoButton = new QPushButton(centralwidget);
        updateInfoButton->setObjectName("updateInfoButton");

        navLayout->addWidget(updateInfoButton);

        viewSystemAdviceButton = new QPushButton(centralwidget);
        viewSystemAdviceButton->setObjectName("viewSystemAdviceButton");

        navLayout->addWidget(viewSystemAdviceButton);

        suggestButton = new QPushButton(centralwidget);
        suggestButton->setObjectName("suggestButton");

        navLayout->addWidget(suggestButton);


        mainLayout->addLayout(navLayout);

        suggestionArea = new QScrollArea(centralwidget);
        suggestionArea->setObjectName("suggestionArea");
        suggestionArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        suggestionArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        suggestionArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 788, 478));
        suggestionsLayout = new QVBoxLayout(scrollAreaWidgetContents);
        suggestionsLayout->setSpacing(15);
        suggestionsLayout->setObjectName("suggestionsLayout");
        suggestionsLayout->setContentsMargins(20, 15, 20, 15);
        emptyLabel = new QLabel(scrollAreaWidgetContents);
        emptyLabel->setObjectName("emptyLabel");
        emptyLabel->setAlignment(Qt::AlignCenter);

        suggestionsLayout->addWidget(emptyLabel);

        suggestionArea->setWidget(scrollAreaWidgetContents);

        mainLayout->addWidget(suggestionArea);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        mainLayout->addWidget(refreshButton);

        FarmerWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FarmerWindow);
        statusbar->setObjectName("statusbar");
        FarmerWindow->setStatusBar(statusbar);

        retranslateUi(FarmerWindow);

        QMetaObject::connectSlotsByName(FarmerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FarmerWindow)
    {
        FarmerWindow->setWindowTitle(QCoreApplication::translate("FarmerWindow", "\345\206\234\346\210\267\347\256\241\347\220\206\345\271\263\345\217\260", nullptr));
        FarmerWindow->setStyleSheet(QCoreApplication::translate("FarmerWindow", "background-color: #f5f7fa;", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
"            font-size: 22px;\n"
"            font-weight: bold;\n"
"            color: #2c3e50;\n"
"          ", nullptr));
        titleLabel->setText(QCoreApplication::translate("FarmerWindow", "\345\206\234\346\210\267\347\256\241\347\220\206\345\271\263\345\217\260", nullptr));
        subtitleLabel->setStyleSheet(QCoreApplication::translate("FarmerWindow", "font-size: 13px; color: #888; margin-bottom: 2px;", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("FarmerWindow", "\345\247\223\345\220\215\357\274\214\344\275\240\345\245\275\357\274\201", nullptr));
        updateInfoButton->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
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
        updateInfoButton->setText(QCoreApplication::translate("FarmerWindow", "\344\270\252\344\272\272\344\277\241\346\201\257\347\256\241\347\220\206", nullptr));
#if QT_CONFIG(tooltip)
        viewSystemAdviceButton->setToolTip(QCoreApplication::translate("FarmerWindow", "\347\202\271\345\207\273\346\237\245\347\234\213\347\263\273\347\273\237\344\270\272\346\202\250\346\216\250\351\200\201\347\232\204\345\273\272\350\256\256", nullptr));
#endif // QT_CONFIG(tooltip)
        viewSystemAdviceButton->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
"            QPushButton {\n"
"              background-color: #f39c12;\n"
"              color: white;\n"
"              border-radius: 6px;\n"
"              padding: 10px 24px;\n"
"              font-size: 15px;\n"
"              font-weight: bold;\n"
"              border: none;\n"
"              box-shadow: 0 2px 8px #f8c471;\n"
"            }\n"
"            QPushButton:hover {\n"
"              background-color: #e67e22;\n"
"            }\n"
"            QPushButton:pressed {\n"
"              background-color: #ca7c1b;\n"
"            }\n"
"          ", nullptr));
        viewSystemAdviceButton->setText(QCoreApplication::translate("FarmerWindow", "\346\237\245\347\234\213\347\263\273\347\273\237\346\212\245\345\221\212", nullptr));
        suggestButton->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
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
        suggestButton->setText(QCoreApplication::translate("FarmerWindow", "\347\273\231\347\263\273\347\273\237\346\235\245\347\202\271\345\273\272\350\256\256\357\274\237", nullptr));
        suggestionArea->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
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
        emptyLabel->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
"             color: #95a5a6;\n"
"             font-size: 14px;\n"
"             padding: 30px;\n"
"           ", nullptr));
        emptyLabel->setText(QCoreApplication::translate("FarmerWindow", "\346\232\202\346\227\240\344\270\223\345\256\266\345\273\272\350\256\256\357\274\214\347\263\273\347\273\237\345\260\206\346\240\271\346\215\256\346\202\250\347\232\204\347\247\215\346\244\215\346\203\205\345\206\265\345\256\236\346\227\266\346\216\250\351\200\201", nullptr));
        refreshButton->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
"        QPushButton {\n"
"          background-color: #3498db;  /* \350\223\235\350\211\262\350\203\214\346\231\257 */\n"
"          color: white;\n"
"          border-radius: 6px;  /* \345\234\206\350\247\222 */\n"
"          padding: 10px 20px;  /* \345\206\205\350\276\271\350\267\235 */\n"
"          font-size: 14px;\n"
"          font-weight: bold;\n"
"          border: none;\n"
"        }\n"
"        QPushButton:hover {\n"
"          background-color: #2980b9;  /* \346\202\254\346\265\256\346\227\266\351\242\234\350\211\262\345\217\230\346\267\261 */\n"
"        }\n"
"        QPushButton:pressed {\n"
"          background-color: #21618c;  /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"        }\n"
"       ", nullptr));
        refreshButton->setText(QCoreApplication::translate("FarmerWindow", "\345\210\267\346\226\260", nullptr));
        statusbar->setStyleSheet(QCoreApplication::translate("FarmerWindow", "\n"
"      background: #f0f4f8;\n"
"      color: #7f8c8d;\n"
"      padding: 0 10px;\n"
"    ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FarmerWindow: public Ui_FarmerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FARMERWINDOW_H
