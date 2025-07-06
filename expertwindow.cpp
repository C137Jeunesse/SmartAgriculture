// expertwindow.cpp
// 专家主窗口类实现文件，实现专家作物区管理、建议填写、系统建议、窗口切换等功能
#include "expertwindow.h"
#include "ui_expertwindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include "systemadviceform.h"

/**
 * @brief 构造函数，初始化UI、加载作物区、连接信号槽
 * @param expertId 当前专家ID
 * @param parent 父窗口指针
 */
ExpertWindow::ExpertWindow(int expertId, QWidget *parent)
    : QMainWindow(parent),expertId(expertId),
    ui(new Ui::ExpertWindow)
{
    ui->setupUi(this);
    changeInfoWindow = nullptr;
    expertAdviceForm = nullptr;
    systemAdviceForm = nullptr;
    sysWin = nullptr;
    loadCropAreas();
    connect(ui->refreshButton, &QPushButton::clicked, this, &ExpertWindow::loadCropAreas);
}

/**
 * @brief 析构函数，释放UI资源
 */
ExpertWindow::~ExpertWindow()
{
    delete ui;
}

/**
 * @brief 修改信息按钮点击槽，弹出信息修改窗口
 */
void ExpertWindow::on_updateInfoButton_clicked()
{
    this->hide();
    if(changeInfoWindow == nullptr){
        changeInfoWindow = new ChangeInfoWindow(expertId, 1);
        connect(changeInfoWindow, &ChangeInfoWindow::closeSignal, this, &ExpertWindow::ReShow);
        connect(changeInfoWindow, &ChangeInfoWindow::logOut, this, &ExpertWindow::onLogOut);
    }
    changeInfoWindow->show();
}

/**
 * @brief 重新显示主窗口槽，释放子窗口资源
 */
void ExpertWindow::ReShow(){
    this->show();
    if(changeInfoWindow != nullptr){
        disconnect(changeInfoWindow, &ChangeInfoWindow::closeSignal, this, &ExpertWindow::ReShow);
        delete changeInfoWindow;
        changeInfoWindow = nullptr;
    }
    if(expertAdviceForm != nullptr){
        disconnect(expertAdviceForm, &ExpertAdviceForm::closeSignal, this, &ExpertWindow::ReShow);
        delete expertAdviceForm;
        expertAdviceForm = nullptr;
    }
    if(systemAdviceForm != nullptr){
        disconnect(systemAdviceForm, &SystemAdviceForm::closeSignal, this, &ExpertWindow::ReShow);
        delete systemAdviceForm;
        systemAdviceForm = nullptr;
    }
    if(sysWin != nullptr){
        disconnect(sysWin, &SystemWindow::closeSignal, this, &ExpertWindow::ReShow);
        delete sysWin;
        sysWin = nullptr;
    }
}

/**
 * @brief 动态加载所有作物区卡片
 */
void ExpertWindow::loadCropAreas()
{
    clearCropAreas();
    DataBaseManager &db = DataBaseManager::instance();
    QVariantList cropAreas = db.GetAllCropAreas();
    int colCount = 6; // id, farmer_id, crop_type, area, location, detail
    if (cropAreas.isEmpty()) {
        ui->emptyLabel->setVisible(true);
        return;
    }
    ui->emptyLabel->setVisible(false);
    for (const QVariant &item : cropAreas) {
        QVariantList area = item.toList();
        if (area.size() < colCount) continue;
        int farmerId = area[1].toInt();
        int userId = db.GetUserIdByFarmerId(farmerId);
        QString farmerPhone;
        if (userId != -1) {
            QVariantList userInfo = db.GetUserInfo(userId);
            if (userInfo.size() >= 3) {
                farmerPhone = userInfo[2].toString();
            }
        }
        addCropCard(area, farmerPhone);
    }
}

/**
 * @brief 清空所有作物区卡片
 */
void ExpertWindow::clearCropAreas()
{
    QLayout *layout = ui->cropsLayout;
    for (int i = layout->count() - 1; i >= 0; --i) {
        QLayoutItem *item = layout->itemAt(i);
        QWidget *widget = item->widget();
        if (widget && widget != ui->emptyLabel) {
            layout->removeWidget(widget);
            delete widget;
        }
    }
}

/**
 * @brief 添加作物区卡片到界面，包含查看系统报告和填写建议按钮
 * @param area 作物区信息
 * @param farmerPhone 农户手机号
 */
void ExpertWindow::addCropCard(const QVariantList &area, const QString &farmerPhone)
{
    // area: [id, farmer_id, crop_type, area, location, detail]
    QWidget *card = new QWidget();
    card->setMinimumHeight(70);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    card->setStyleSheet("background: #fff; border-radius: 8px; border: 1px solid #e0e6ed; margin-bottom: 10px; padding: 10px 12px 10px 16px;");
    QVBoxLayout *vbox = new QVBoxLayout(card);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(4);
    // 顶部信息+按钮行
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setSpacing(8);
    QString info = QString("<b style='font-size:15px;'>%1</b> <span style='color:#888;font-size:13px;'>| %2亩 | %3</span>")
        .arg(area[2].toString())
        .arg(area[3].toFloat())
        .arg(area[4].toString());
    QLabel *infoLabel = new QLabel(info);
    infoLabel->setStyleSheet("font-size: 15px; color: #2c3e50; font-weight: bold;");
    infoLabel->setTextFormat(Qt::RichText);
    hbox->addWidget(infoLabel);
    // 农户电话
    QLabel *phoneLabel = new QLabel("农户电话: " + farmerPhone);
    phoneLabel->setStyleSheet("font-size: 13px; color: #888; margin-left: 8px;");
    hbox->addWidget(phoneLabel);
    hbox->addStretch();
    // 查看系统数据按钮
    QPushButton *viewBtn = new QPushButton("查看系统报告");
    viewBtn->setStyleSheet("QPushButton { background: #f0f4ff; color: #3498db; border: 1px solid #3498db; border-radius: 4px; padding: 4px 12px; font-size: 13px; font-weight: bold; } QPushButton:hover { background: #e0f0ff; }");
    hbox->addWidget(viewBtn);
    // 提供建议按钮
    QPushButton *adviceBtn = new QPushButton("提供建议");
    adviceBtn->setStyleSheet("QPushButton { background: #f0fff4; color: #27ae60; border: 1px solid #27ae60; border-radius: 4px; padding: 4px 12px; font-size: 13px; font-weight: bold; } QPushButton:hover { background: #e0f7e0; }");
    hbox->addWidget(adviceBtn);
    vbox->addLayout(hbox);
    // 说明（折叠/展开）
    QString fullDesc = area[5].toString();
    int maxLen = 40;
    bool needFold = fullDesc.length() > maxLen;
    QString shortDesc = fullDesc.left(maxLen) + (needFold ? "..." : "");
    QLabel *descLabel = new QLabel("说明：" + (needFold ? shortDesc : fullDesc));
    descLabel->setStyleSheet("font-size: 12px; color: #888; background: #f8f9fa; border-radius: 5px; padding: 6px 10px; margin-top: 2px;");
    descLabel->setWordWrap(true);
    vbox->addWidget(descLabel);
    QPushButton *foldBtn = nullptr;
    if (needFold) {
        foldBtn = new QPushButton("展开");
        foldBtn->setStyleSheet("QPushButton { background: transparent; color: #3498db; border: none; font-size: 12px; } QPushButton:hover { color: #217dbb; }");
        QFont font = foldBtn->font();
        font.setUnderline(true);
        foldBtn->setFont(font);
        vbox->addWidget(foldBtn, 0, Qt::AlignLeft);
        bool *isFolded = new bool(true); // 用于lambda捕获
        connect(foldBtn, &QPushButton::clicked, card, [descLabel, foldBtn, fullDesc, shortDesc, isFolded]() mutable {
            if (*isFolded) {
                descLabel->setText("说明：" + fullDesc);
                foldBtn->setText("收起");
            } else {
                descLabel->setText("说明：" + shortDesc);
                foldBtn->setText("展开");
            }
            *isFolded = !*isFolded;
        });
    }
    // 添加到布局（在emptyLabel前）
    int insertIdx = ui->cropsLayout->indexOf(ui->emptyLabel);
    ui->cropsLayout->insertWidget(insertIdx, card);
    // 按钮信号
    connect(viewBtn, &QPushButton::clicked, this, [this, area]() {
        std::vector<int> cropIds = { area[0].toInt() };
        if (sysWin) {
            disconnect(sysWin, &SystemWindow::closeSignal, this, &ExpertWindow::ReShow);
            delete sysWin;
            sysWin = nullptr;
        }
        sysWin = new SystemWindow(cropIds);
        connect(sysWin, &SystemWindow::closeSignal, this, &ExpertWindow::ReShow);
        sysWin->initialize();
        sysWin->show();
        this->hide();
    });
    connect(adviceBtn, &QPushButton::clicked, this, [this, area]() {
        if (expertAdviceForm != nullptr) {
            disconnect(expertAdviceForm, &ExpertAdviceForm::closeSignal, this, &ExpertWindow::ReShow);
            delete expertAdviceForm;
            expertAdviceForm = nullptr;
        }
        expertAdviceForm = new ExpertAdviceForm(expertId, area[0].toInt());
        connect(expertAdviceForm, &ExpertAdviceForm::closeSignal, this, &ExpertWindow::ReShow);
        this->hide();
        expertAdviceForm->show();
    });
}

/**
 * @brief 系统建议按钮点击槽，弹出系统建议窗口
 */
void ExpertWindow::on_suggestButton_clicked()
{
    this->hide();
    if (systemAdviceForm == nullptr) {
        systemAdviceForm = new SystemAdviceForm(expertId,1);
        connect(systemAdviceForm, &SystemAdviceForm::closeSignal, this, &ExpertWindow::ReShow);
    }
    systemAdviceForm->show();
}

/**
 * @brief 登出槽，发送登出信号
 */
void ExpertWindow::onLogOut()
{
    emit logout();
}

/**
 * @brief 设置用户名显示
 * @param name 用户名
 */
void ExpertWindow::setUserName(const QString &name) {
    if (ui->subtitleLabel) {
        ui->subtitleLabel->setText(name + "，你好！");
    }
}

