/********************************************************************************
** Form generated from reading UI file 'expertadviceform.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPERTADVICEFORM_H
#define UI_EXPERTADVICEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExpertAdviceForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *adviceLayout;
    QPushButton *addAdviceButton;

    void setupUi(QWidget *ExpertAdviceForm)
    {
        if (ExpertAdviceForm->objectName().isEmpty())
            ExpertAdviceForm->setObjectName("ExpertAdviceForm");
        ExpertAdviceForm->resize(480, 400);
        verticalLayout = new QVBoxLayout(ExpertAdviceForm);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(ExpertAdviceForm);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet(QString::fromUtf8("font-size:18px;font-weight:bold;margin:10px 0;"));

        verticalLayout->addWidget(titleLabel);

        scrollArea = new QScrollArea(ExpertAdviceForm);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 440, 300));
        adviceLayout = new QVBoxLayout(scrollAreaWidgetContents);
        adviceLayout->setSpacing(8);
        adviceLayout->setObjectName("adviceLayout");
        adviceLayout->setContentsMargins(8, 8, 8, 8);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        addAdviceButton = new QPushButton(ExpertAdviceForm);
        addAdviceButton->setObjectName("addAdviceButton");
        addAdviceButton->setStyleSheet(QString::fromUtf8("font-size:15px;padding:8px 24px;background:#f0f4ff;color:#3498db;border:1px solid #3498db;border-radius:6px;font-weight:bold;"));

        verticalLayout->addWidget(addAdviceButton);

        verticalLayout->setStretch(1, 1);

        retranslateUi(ExpertAdviceForm);

        QMetaObject::connectSlotsByName(ExpertAdviceForm);
    } // setupUi

    void retranslateUi(QWidget *ExpertAdviceForm)
    {
        titleLabel->setText(QCoreApplication::translate("ExpertAdviceForm", "\344\270\223\345\256\266\345\273\272\350\256\256", nullptr));
        addAdviceButton->setText(QCoreApplication::translate("ExpertAdviceForm", "\346\267\273\345\212\240\345\273\272\350\256\256", nullptr));
        (void)ExpertAdviceForm;
    } // retranslateUi

};

namespace Ui {
    class ExpertAdviceForm: public Ui_ExpertAdviceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPERTADVICEFORM_H
