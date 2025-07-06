// expertadviceform.cpp
// 专家建议表单窗口实现文件，实现专家对作物区建议的增删与展示
#include "expertadviceform.h"
#include "ui_expertadviceform.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QCloseEvent>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QMessageBox>

/**
 * @brief 构造函数，初始化UI并加载建议列表
 * @param expertId 专家id
 * @param cropAreaId 作物区id
 * @param parent 父窗口
 */
ExpertAdviceForm::ExpertAdviceForm(int expertId, int cropAreaId, QWidget *parent)
    : QWidget(parent), expertId(expertId), cropAreaId(cropAreaId), ui(new Ui::ExpertAdviceForm)
{
    ui->setupUi(this);
    loadAdviceList();
}

/**
 * @brief 析构函数，释放UI资源
 */
ExpertAdviceForm::~ExpertAdviceForm()
{
    delete ui;
}

/**
 * @brief 重写关闭事件，发送关闭信号
 * @param event 关闭事件指针
 */
void ExpertAdviceForm::closeEvent(QCloseEvent *event)
{
    emit closeSignal();
    event->accept();
}

/**
 * @brief 加载专家建议列表，动态生成卡片
 */
void ExpertAdviceForm::loadAdviceList()
{
    clearAdviceList();
    DataBaseManager &db = DataBaseManager::instance();
    QVariantList adviceList = db.GetExpertAdviceList(expertId, cropAreaId);
    QVBoxLayout *layout = ui->adviceLayout;
    if (adviceList.isEmpty()) {
        QLabel *emptyLabel = new QLabel("暂无建议");
        layout->addWidget(emptyLabel);
        return;
    }
    for (const QVariant &item : adviceList) {
        QVariantList advice = item.toList();
        addAdviceCard(advice);
    }
}

/**
 * @brief 清空所有建议卡片
 */
void ExpertAdviceForm::clearAdviceList()
{
    QLayout *layout = ui->adviceLayout;
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            delete widget;
        }
        delete item;
    }
}

/**
 * @brief 添加建议卡片到界面，支持撤回操作
 * @param advice 建议信息（QVariantList）
 */
void ExpertAdviceForm::addAdviceCard(const QVariantList &advice)
{
    QWidget *card = new QWidget();
    card->setStyleSheet("background: #fff; border-radius: 8px; border: 1px solid #e0e6ed; margin-bottom: 10px; padding: 10px 12px 10px 16px;");
    QHBoxLayout *hbox = new QHBoxLayout(card);
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(8);

    QString title = advice[1].toString();
    QString content = advice[2].toString();
    QString timeStr = advice[3].toString();
    QString category = advice[4].toString();
    int adviceId = advice[0].toInt();

    QLabel *titleLabel = new QLabel(title);
    QLabel *contentLabel = new QLabel(content);
    QLabel *timeLabel = new QLabel("时间: " + timeStr);
    QLabel *categoryLabel = new QLabel("类别: " + category);

    titleLabel->setStyleSheet("font-size: 15px; color: #2c3e50;");
    contentLabel->setStyleSheet("font-size: 15px; color: #2c3e50;");
    timeLabel->setStyleSheet("font-size: 12px; color: #888; margin-left: 12px;");
    categoryLabel->setStyleSheet("font-size: 12px; color: #888; margin-left: 12px;");

    hbox->addWidget(titleLabel);
    hbox->addWidget(contentLabel);
    hbox->addWidget(timeLabel);
    hbox->addWidget(categoryLabel);
    hbox->addStretch();

    QPushButton *retractBtn = new QPushButton("撤回");
    retractBtn->setStyleSheet("QPushButton { background: #fff0f0; color: #e74c3c; border: 1px solid #e74c3c; border-radius: 4px; padding: 4px 12px; font-size: 13px; font-weight: bold; } QPushButton:hover { background: #ffeaea; }");
    hbox->addWidget(retractBtn);

    // 撤回按钮功能实现
    connect(retractBtn, &QPushButton::clicked, this, [this, adviceId]() {
        if (QMessageBox::question(this, "确认撤回", "确定要撤回该建议吗？") == QMessageBox::Yes) {
            DataBaseManager &db = DataBaseManager::instance();
            bool ok = db.DeleteExpertAdvice(adviceId);
            if (!ok) {
                QMessageBox::critical(this, "错误", "撤回失败！\n" + db.GetLastError());
                return;
            }
            loadAdviceList();
            QMessageBox::information(this, "成功", "撤回成功！");
        }
    });

    ui->adviceLayout->addWidget(card);
}

/**
 * @brief 添加建议按钮点击槽，弹窗输入并添加新建议
 */
void ExpertAdviceForm::on_addAdviceButton_clicked() {
    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("添加专家建议");
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    // 标题
    QHBoxLayout *titleLayout = new QHBoxLayout();
    QLabel *titleLabel = new QLabel("标题：");
    QLineEdit *titleEdit = new QLineEdit();
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleEdit);
    mainLayout->addLayout(titleLayout);

    // 内容
    QHBoxLayout *contentLayout = new QHBoxLayout();
    QLabel *contentLabel = new QLabel("内容：");
    QTextEdit *contentEdit = new QTextEdit();
    contentLayout->addWidget(contentLabel);
    contentLayout->addWidget(contentEdit);
    mainLayout->addLayout(contentLayout);

    // 类别
    QHBoxLayout *categoryLayout = new QHBoxLayout();
    QLabel *categoryLabel = new QLabel("类别：");
    QComboBox *categoryCombo = new QComboBox();
    categoryCombo->addItems(QStringList() << "病虫害" << "灌溉" << "施肥" << "收获" << "其他");
    categoryLayout->addWidget(categoryLabel);
    categoryLayout->addWidget(categoryCombo);
    mainLayout->addLayout(categoryLayout);

    // 按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *okBtn = new QPushButton("确定");
    QPushButton *cancelBtn = new QPushButton("取消");
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);

    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString title = titleEdit->text().trimmed();
        QString content = contentEdit->toPlainText().trimmed();
        QString category = categoryCombo->currentText();

        if (title.isEmpty() || content.isEmpty()) {
            QMessageBox::warning(this, "提示", "标题和内容不能为空！");
            return;
        }

        // 使用DataBaseManager接口添加建议
        DataBaseManager &db = DataBaseManager::instance();
        bool ok = db.AddExpertAdvice(expertId, cropAreaId, title, content, category);
        if (!ok) {
            QMessageBox::critical(this, "错误", "添加建议失败！\n" + db.GetLastError());
            return;
        }
        loadAdviceList();
        QMessageBox::information(this, "成功", "添加建议成功！");
    }
}