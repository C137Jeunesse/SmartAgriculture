// systemadviceform.cpp
// 系统建议表单窗口实现文件，实现农户/专家提交模型优化建议功能
#include "systemadviceform.h"
#include "ui_systemadviceform.h"
#include <QCloseEvent>
#include "databasemanager.h"
#include <QMessageBox>

/**
 * @brief 构造函数，初始化UI与信号连接
 * @param id 用户id
 * @param roleIndex 角色索引（0-农户，1-专家）
 * @param parent 父窗口
 */
SystemAdviceForm::SystemAdviceForm(int id, int roleIndex, QWidget *parent)
    : QWidget(parent),id(id),roleIndex(roleIndex)
    , ui(new Ui::SystemAdviceForm)
{
    ui->setupUi(this);
    connect(ui->submitButton, &QPushButton::clicked, this, &SystemAdviceForm::onSubmitButtonClicked);
}

/**
 * @brief 析构函数，释放UI资源
 */
SystemAdviceForm::~SystemAdviceForm()
{
    delete ui;
}

/**
 * @brief 重写关闭事件，发送关闭信号
 * @param event 关闭事件指针
 */
void SystemAdviceForm::closeEvent(QCloseEvent *event)
{
    emit closeSignal();
    event->accept();
}

/**
 * @brief 提交按钮点击槽，校验并提交建议内容
 */
void SystemAdviceForm::onSubmitButtonClicked()
{
    QString content = ui->adviceTextEdit->toPlainText().trimmed();
    if(content.isEmpty()) {
        QMessageBox::warning(this, "提示", "建议内容不能为空！");
        return;
    }
    bool ok = DataBaseManager::instance().AddModelOptimization(id, roleIndex, content);
    if(ok) {
        QMessageBox::information(this, "成功", "建议提交成功！");
        ui->adviceTextEdit->clear();
    } else {
        QMessageBox::critical(this, "错误", "建议提交失败：" + DataBaseManager::instance().GetLastError());
    }
}
