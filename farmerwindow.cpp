// FarmerWindow.cpp
// 农户主窗口类实现文件，实现农户建议查看、个人信息管理、系统建议、窗口切换等功能
#include "FarmerWindow.h"
#include "ui_FarmerWindow.h"
#include "databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QFrame>
#include <QScrollArea>
#include <QSpacerItem>
#include "mainwindow.h"

/**
 * @brief 构造函数，初始化UI、加载建议、连接信号槽
 * @param farmerId 当前农户ID
 * @param parent 父窗口指针
 */
FarmerWindow::FarmerWindow(int farmerId, QWidget *parent)
    : QMainWindow(parent), currentFarmerId(farmerId), ui(new Ui::FarmerWindow)
{
    ui->setupUi(this);
    initUI();
    loadSuggestions();
    changeWindow = nullptr;
    systemAdviceForm = nullptr;
    sysWin = nullptr;
    // 连接按钮信号槽
    connect(ui->updateInfoButton,&QPushButton::clicked,this, &FarmerWindow::UpdateButtonClicked);
    connect(ui->viewSystemAdviceButton, &QPushButton::clicked, this, &FarmerWindow::on_viewSystemAdviceButton_clicked);
    connect(ui->suggestButton, &QPushButton::clicked, this, &FarmerWindow::on_suggestButton_clicked);
}

/**
 * @brief 析构函数，释放UI资源
 */
FarmerWindow::~FarmerWindow()
{
    delete ui;
}

/**
 * @brief 初始化UI，设置类别颜色映射、连接刷新按钮
 */
void FarmerWindow::initUI()
{
    // 初始化类别颜色映射
    categoryColors = {
        {"病虫害", "#e74c3c"},
        {"灌溉", "#3498db"},
        {"施肥", "#f39c12"},
        {"收获", "#27ae60"},
        {"其他", "#9b59b6"}
    };
    // 连接刷新按钮
    connect(ui->refreshButton, &QPushButton::clicked, this, &FarmerWindow::refreshSuggestions);
}

/**
 * @brief 加载农户所有专家建议卡片
 */
void FarmerWindow::loadSuggestions()
{
    // 清空现有卡片
    clearSuggestions();
    DataBaseManager &db = DataBaseManager::instance();
    // 从数据库获取当前农户的建议
    QVariantList suggestions = db.GetFarmerExpertAdvices(currentFarmerId);
    if (suggestions.isEmpty()) {
        ui->emptyLabel->setVisible(true);
        return;
    }
    ui->emptyLabel->setVisible(false);
    // 创建卡片
    for (const QVariant& item : suggestions) {
        createSuggestionCard(item.toMap());
    }
}

/**
 * @brief 创建建议卡片并添加到界面
 * @param suggestion 建议内容
 */
void FarmerWindow::createSuggestionCard(const QVariantMap& suggestion)
{
    // 创建卡片容器
    QWidget* card = new QWidget();
    card->setMinimumHeight(120);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 获取数据
    QString title = suggestion["title"].toString();
    QString content = suggestion["content"].toString();
    QString expert = suggestion["expert_name"].toString();
    QString date = QDateTime::fromString(suggestion["created_at"].toString(), Qt::ISODate)
                       .toString("yyyy-MM-dd");
    QString category = suggestion["category"].toString();
    QString cropType = suggestion["crop_type"].toString();
    QString cropLocation = suggestion["crop_location"].toString();
    // 获取类别颜色
    QString borderColor = categoryColors.value(category, "#3498db");
    // 设置卡片样式
    card->setStyleSheet(QString(
                            "QWidget {"
                            "  background: #ffffff;"
                            "  border-radius: 12px;"
                            "  padding: 20px;"
                            "  border: 1px solid #e0e6ed;"
                            "  border-left: 4px solid %1;"
                            "  border-top: 1px solid rgba(0,0,0,0.05);"
                            "  border-right: 1px solid rgba(0,0,0,0.05);"
                            "  border-bottom: 2px solid rgba(0,0,0,0.08);"
                            "}"
                            ).arg(borderColor));
    // 主布局
    QHBoxLayout* cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(0, 0, 0, 0);
    // 左侧信息区
    QWidget* infoWidget = new QWidget();
    QVBoxLayout* infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    // 标题
    QLabel* titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");
    infoLayout->addWidget(titleLabel);
    // 作物信息
    QLabel* cropLabel = new QLabel(QString("%1 · %2").arg(cropType).arg(cropLocation));
    cropLabel->setStyleSheet("font-size: 12px; color: #7f8c8d; margin-top: 3px;");
    infoLayout->addWidget(cropLabel);
    // 内容预览
    QString preview = content.length() > 100 ? content.left(100) + "..." : content;
    QLabel* previewLabel = new QLabel(preview);
    previewLabel->setStyleSheet("font-size: 14px; color: #7f8c8d; margin-top: 8px;");
    previewLabel->setWordWrap(true);
    infoLayout->addWidget(previewLabel);
    // 专家和日期
    QLabel* expertLabel = new QLabel(QString("%1 · %2").arg(expert).arg(date));
    expertLabel->setStyleSheet("font-size: 12px; color: #95a5a6; margin-top: 10px;");
    infoLayout->addWidget(expertLabel);
    cardLayout->addWidget(infoWidget, 4);
    // 添加弹性空间
    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    cardLayout->addItem(spacer);
    // 详情按钮
    QPushButton* detailButton = new QPushButton("查看详情");
    detailButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #e1f0fa;"
        "  color: #3498db;"
        "  border-radius: 6px;"
        "  padding: 8px 16px;"
        "  font-size: 13px;"
        "  font-weight: bold;"
        "  border: 1px solid #3498db;"
        "}"
        "QPushButton:hover {"
        "  background-color: #d0e6f7;"
        "}"
        );
    // 连接详情按钮
    connect(detailButton, &QPushButton::clicked, this, [this, suggestion]() {
        showSuggestionDetail(suggestion);
    });
    cardLayout->addWidget(detailButton, 1);
    // 添加到布局
    ui->suggestionsLayout->insertWidget(ui->suggestionsLayout->count() - 1, card);
}

/**
 * @brief 清空所有建议卡片
 */
void FarmerWindow::clearSuggestions()
{
    // 删除除空状态标签外的所有卡片
    for (int i = ui->suggestionsLayout->count() - 1; i >= 0; --i) {
        QLayoutItem* item = ui->suggestionsLayout->itemAt(i);
        if (item->widget() && item->widget() != ui->emptyLabel) {
            delete item->widget();
        }
    }
}

/**
 * @brief 显示建议详情对话框
 * @param suggestion 建议内容
 */
void FarmerWindow::showSuggestionDetail(const QVariantMap& suggestion)
{
    // 创建详情对话框
    QDialog detailDialog(this);
    detailDialog.setWindowTitle("专家建议详情");
    detailDialog.resize(600, 500);
    QVBoxLayout* mainLayout = new QVBoxLayout(&detailDialog);
    // 标题
    QLabel* titleLabel = new QLabel(suggestion["title"].toString());
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 15px; color: #2c3e50;");
    mainLayout->addWidget(titleLabel);
    // 元信息网格
    QGridLayout* metaLayout = new QGridLayout();
    metaLayout->setColumnStretch(1, 1);
    // 专家
    metaLayout->addWidget(new QLabel("专家:"), 0, 0);
    QLabel* expertValue = new QLabel(suggestion["expert_name"].toString());
    expertValue->setStyleSheet("font-weight: bold;");
    metaLayout->addWidget(expertValue, 0, 1);
    // 日期
    metaLayout->addWidget(new QLabel("日期:"), 1, 0);
    QString date = QDateTime::fromString(suggestion["created_at"].toString(), Qt::ISODate)
                       .toString("yyyy-MM-dd hh:mm");
    QLabel* dateValue = new QLabel(date);
    metaLayout->addWidget(dateValue, 1, 1);
    // 类别
    metaLayout->addWidget(new QLabel("类别:"), 2, 0);
    QLabel* categoryValue = new QLabel(suggestion["category"].toString());
    categoryValue->setStyleSheet(QString("color: %1; font-weight: bold;")
                                     .arg(categoryColors.value(suggestion["category"].toString(), "#3498db")));
    metaLayout->addWidget(categoryValue, 2, 1);
    // 作物类型
    metaLayout->addWidget(new QLabel("作物类型:"), 3, 0);
    metaLayout->addWidget(new QLabel(suggestion["crop_type"].toString()), 3, 1);
    // 位置
    metaLayout->addWidget(new QLabel("位置:"), 4, 0);
    metaLayout->addWidget(new QLabel(suggestion["crop_location"].toString()), 4, 1);
    mainLayout->addLayout(metaLayout);
    // 分隔线
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("margin: 15px 0;");
    mainLayout->addWidget(line);
    // 内容
    QLabel* contentLabel = new QLabel("建议内容:");
    contentLabel->setStyleSheet("font-weight: bold; font-size: 16px; margin-bottom: 10px;");
    mainLayout->addWidget(contentLabel);
    QTextEdit* contentEdit = new QTextEdit();
    contentEdit->setPlainText(suggestion["content"].toString());
    contentEdit->setReadOnly(true);
    contentEdit->setStyleSheet("border: 1px solid #e0e6ed; border-radius: 8px; padding: 10px;");
    mainLayout->addWidget(contentEdit, 1);
    // 关闭按钮
    QPushButton* closeButton = new QPushButton("关闭");
    closeButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #3498db;"
        "  color: white;"
        "  border-radius: 6px;"
        "  padding: 10px 20px;"
        "  font-size: 14px;"
        "  font-weight: bold;"
        "  border: none;"
        "}"
        "QPushButton:hover {"
        "  background-color: #2980b9;"
        "}"
        );
    connect(closeButton, &QPushButton::clicked, &detailDialog, &QDialog::accept);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);
    detailDialog.exec();
}

/**
 * @brief 刷新建议卡片槽
 */
void FarmerWindow::refreshSuggestions()
{
    loadSuggestions();
    qDebug()<<"刷新";
}

/**
 * @brief 修改信息按钮点击槽，弹出信息修改窗口
 */
void FarmerWindow::UpdateButtonClicked(){
    this->hide();
    if(changeWindow==nullptr){
        changeWindow = new ChangeInfoWindow(currentFarmerId,0);
        connect(changeWindow,&ChangeInfoWindow::closeSignal,this,&FarmerWindow::ReShow);
        connect(changeWindow, &ChangeInfoWindow::logOut, this, &FarmerWindow::onLogOut);
    }
    changeWindow->show();
}

/**
 * @brief 查看系统建议按钮点击槽，弹出系统分析窗口
 */
void FarmerWindow::on_viewSystemAdviceButton_clicked()
{
    // 查询当前农户所有作物区
    DataBaseManager &db = DataBaseManager::instance();
    QVariantList cropAreas = db.GetCropAreas(currentFarmerId);
    std::vector<int> cropIds;
    int colCount = 6; // id, farmer_id, crop_type, area, location, detail
    for(int i=0;i<cropAreas.size();i+=colCount){
        cropIds.push_back(cropAreas[i].toInt());
    }
    if (sysWin) {
        disconnect(sysWin, &SystemWindow::closeSignal, this, &FarmerWindow::ReShow);
        delete sysWin;
        sysWin = nullptr;
    }
    sysWin = new SystemWindow(cropIds);
    connect(sysWin, &SystemWindow::closeSignal, this, &FarmerWindow::ReShow);
    sysWin->initialize();
    sysWin->show();
    this->hide();
}

/**
 * @brief 重新显示主窗口槽，释放子窗口资源并刷新建议
 */
void FarmerWindow::ReShow(){
    this->show();
    if(changeWindow != nullptr){
        disconnect(changeWindow, &ChangeInfoWindow::closeSignal, this, &FarmerWindow::ReShow);
        delete changeWindow;
        changeWindow = nullptr;
    }
    if(systemAdviceForm != nullptr){
        disconnect(systemAdviceForm, &SystemAdviceForm::closeSignal, this, &FarmerWindow::ReShow);
        delete systemAdviceForm;
        systemAdviceForm = nullptr;
    }
    if(sysWin != nullptr){
        disconnect(sysWin, &SystemWindow::closeSignal, this, &FarmerWindow::ReShow);
        delete sysWin;
        sysWin = nullptr;
    }
    refreshSuggestions();
}

/**
 * @brief 系统建议按钮点击槽，弹出系统建议窗口
 */
void FarmerWindow::on_suggestButton_clicked()
{
    this->hide();
    if (systemAdviceForm == nullptr) {
        systemAdviceForm = new SystemAdviceForm(currentFarmerId,0);
        connect(systemAdviceForm, &SystemAdviceForm::closeSignal, this, &FarmerWindow::ReShow);
    }
    systemAdviceForm->show();
    systemAdviceForm->raise();
    systemAdviceForm->activateWindow();
}

/**
 * @brief 登出槽，发送登出信号
 */
void FarmerWindow::onLogOut()
{
    emit logout();
}

/**
 * @brief 设置用户名显示
 * @param name 用户名
 */
void FarmerWindow::setUserName(const QString &name) {
    if (ui->subtitleLabel) {
        ui->subtitleLabel->setText(name + "，你好！");
    }
}
