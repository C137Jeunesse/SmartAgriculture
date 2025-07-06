/********************************************************************************
** Form generated from reading UI file 'systemadviceform.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMADVICEFORM_H
#define UI_SYSTEMADVICEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemAdviceForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QTextEdit *adviceTextEdit;
    QPushButton *submitButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SystemAdviceForm)
    {
        if (SystemAdviceForm->objectName().isEmpty())
            SystemAdviceForm->setObjectName("SystemAdviceForm");
        SystemAdviceForm->resize(400, 250);
        verticalLayout = new QVBoxLayout(SystemAdviceForm);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(SystemAdviceForm);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        labelTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; margin-bottom: 10px;"));

        verticalLayout->addWidget(labelTitle);

        adviceTextEdit = new QTextEdit(SystemAdviceForm);
        adviceTextEdit->setObjectName("adviceTextEdit");
        adviceTextEdit->setStyleSheet(QString::fromUtf8("font-size: 15px; border-radius: 8px; padding: 8px; background: #f8f8f8; border: 1px solid #d0d0d0;"));
        adviceTextEdit->setMinimumHeight(100);

        verticalLayout->addWidget(adviceTextEdit);

        submitButton = new QPushButton(SystemAdviceForm);
        submitButton->setObjectName("submitButton");
        submitButton->setStyleSheet(QString::fromUtf8("font-size: 16px; padding: 8px 32px; border-radius: 16px; background: #4CAF50; color: white; font-weight: bold; margin-top: 15px;"));
        submitButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(submitButton);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SystemAdviceForm);

        QMetaObject::connectSlotsByName(SystemAdviceForm);
    } // setupUi

    void retranslateUi(QWidget *SystemAdviceForm)
    {
        SystemAdviceForm->setWindowTitle(QCoreApplication::translate("SystemAdviceForm", "\347\263\273\347\273\237\345\273\272\350\256\256", nullptr));
        labelTitle->setText(QCoreApplication::translate("SystemAdviceForm", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\345\273\272\350\256\256\357\274\232", nullptr));
        adviceTextEdit->setPlaceholderText(QCoreApplication::translate("SystemAdviceForm", "\345\234\250\346\255\244\350\276\223\345\205\245\346\202\250\347\232\204\345\256\235\350\264\265\345\273\272\350\256\256...", nullptr));
        submitButton->setText(QCoreApplication::translate("SystemAdviceForm", "\346\217\220\344\272\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemAdviceForm: public Ui_SystemAdviceForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMADVICEFORM_H
