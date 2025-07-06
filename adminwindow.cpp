// adminwindow.cpp
// 管理员主窗口类实现文件，实现建议列表的加载、刷新、卡片管理等功能
#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

/**
 * @brief 构造函数，初始化UI并自动加载建议列表
 * @param parent 父窗口指针
 */
AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    loadAdviceList(); // 进入界面自动加载
}

/**
 * @brief 析构函数，释放UI资源
 */
AdminWindow::~AdminWindow()
{
    delete ui;
}

/**
 * @brief 清空所有建议卡片，仅保留空提示标签
 */
void AdminWindow::clearAdviceCards()
{
    QLayout *layout = ui->adviceLayout;
    // 保留emptyLabel，其余全部删除
    for (int i = layout->count() - 1; i >= 0; --i) {
        QLayoutItem *item = layout->itemAt(i);
        QWidget *widget = item->widget();
        if (widget && widget != ui->emptyLabel) {
            delete widget;
        }
    }
}

/**
 * @brief 加载建议列表并显示到界面
 *        若无建议则显示空提示
 */
void AdminWindow::loadAdviceList()
{
    clearAdviceCards();
    DataBaseManager &db = DataBaseManager::instance();
    QVariantList adviceList = db.GetModelOptimizations();
    if (adviceList.isEmpty()) {
        ui->emptyLabel->setVisible(true);
        return;
    }
    ui->emptyLabel->setVisible(false);
    for (const QVariant &item : adviceList) {
        addAdviceCard(item.toList());
    }
}

/**
 * @brief 添加一条建议卡片到界面
 * @param advice 建议内容（QVariantList，包含id、user_id、role、content）
 */
void AdminWindow::addAdviceCard(const QVariantList &advice)
{
    // 假设字段顺序: id, user_id, role, content
    QString content = advice.value(3).toString();
    QString userId = advice.value(1).toString();
    QString role = advice.value(2).toString();
    QString id = advice.value(0).toString();
    QWidget *card = new QWidget();
    card->setMinimumHeight(80);
    card->setStyleSheet("QWidget { background: #ffffff; border-radius: 12px; padding: 18px; border: 1px solid #e0e6ed; margin-bottom: 8px; }");
    QVBoxLayout *vbox = new QVBoxLayout(card);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(6);
    QLabel *contentLabel = new QLabel(content);
    contentLabel->setStyleSheet("font-size: 15px; color: #2c3e50; font-weight: bold;");
    contentLabel->setWordWrap(true);
    vbox->addWidget(contentLabel);
    QLabel *metaLabel = new QLabel(QString("建议ID: %1  用户ID: %2  角色: %3").arg(id, userId, role));
    metaLabel->setStyleSheet("font-size: 12px; color: #95a5a6; margin-top: 4px;");
    vbox->addWidget(metaLabel);
    ui->adviceLayout->addWidget(card);
}

/**
 * @brief 刷新按钮点击槽函数，重新加载建议列表
 */
void AdminWindow::on_pushButton_refresh_clicked()
{
    clearAdviceCards();
    loadAdviceList();
}

