#include "changeinfowindow.h"
#include "ui_changeinfowindow.h"
#include "databasemanager.h"

#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QDebug>
#include <QCloseEvent>
#include <QRegularExpression>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

/**
 * @brief 构造函数，初始化UI、加载用户信息和作物区/领域
 * @param id 用户id
 * @param roleIndex 角色索引（0-农户，1-专家）
 * @param parent 父窗口指针
 */
ChangeInfoWindow::ChangeInfoWindow(int id, int roleIndex, QWidget *parent)
    : QMainWindow(parent), id(id), roleIndex(roleIndex)
    , ui(new Ui::ChangeInfoWindow)
{
    ui->setupUi(this);
    // 初始化界面，切换到对应角色页面
    ui->roleSpecificStack->setCurrentIndex(roleIndex);
    // 获取用户基本信息并填充
    DataBaseManager &db = DataBaseManager::instance();
    int userId;
    if(roleIndex == 0) {
        userId = db.GetUserIdByFarmerId(id);
    } else {
        userId = db.GetUserIdByExpertId(id);
    }
    if (userId != -1) {
        QVariantList info = db.GetUserInfo(userId);
        if (info.size() >= 4) {
            QString name = info.at(1).toString();
            QString phone = info.at(2).toString();
            ui->nameEdit->setText(name);
            ui->phoneEdit->setText(phone);
            ui->passwordEdit->clear();
            ui->confirmPasswordEdit->clear();
        }
    }
    // 初始化特定UI
    InitSpecificUi();
}

/**
 * @brief 析构函数，释放UI资源
 */
ChangeInfoWindow::~ChangeInfoWindow()
{
    delete ui;
}

/**
 * @brief 重写关闭事件，处理未保存修改，必要时弹窗提示保存
 * @param event 关闭事件指针
 */
void ChangeInfoWindow::closeEvent(QCloseEvent *event)
{
    // 检查是否有未保存更改
    QString name = ui->nameEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    QString field = ui->expertiseEdit->text().trimmed();
    bool changed = false;
    if(roleIndex == 0){
        DataBaseManager &db = DataBaseManager::instance();
        int userId = db.GetUserIdByFarmerId(id);
        QVariantList info = db.GetUserInfo(userId);
        QString oldName = info.value(1).toString();
        QString oldPhone = info.value(2).toString();
        changed = (name != oldName) || (phone != oldPhone);
        if (!password.isEmpty()) changed = true;
    }else{
        DataBaseManager &db = DataBaseManager::instance();
        int userId = db.GetUserIdByExpertId(id);
        QVariantList info = db.GetUserInfo(userId);
        QString oldName = info.value(1).toString();
        QString oldPhone = info.value(2).toString();
        QString oldField = db.GetExpertField(id);
        changed = (name != oldName) || (phone != oldPhone) || (field != oldField);
        if (!password.isEmpty()) changed = true;
    }
    if (changed) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "有未保存的更改", "检测到您的基本信息已修改，是否保存？",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );
        if (reply == QMessageBox::Yes) {
            // 自动调用保存逻辑
            on_saveButton_clicked();
            event->ignore();
            return;
        } else if (reply == QMessageBox::No) {
            emit closeSignal();
            QMainWindow::closeEvent(event);
        } else {
            event->ignore();
            return;
        }
    } else {
        if (!isLogout) {
            emit closeSignal();
        }
        QMainWindow::closeEvent(event);
    }
}

/**
 * @brief 取消按钮点击槽，关闭窗口
 */
void ChangeInfoWindow::on_cancelButton_clicked()
{
    this->close();
}

/**
 * @brief 初始化特定角色UI，农户加载作物区，专家加载领域
 */
void ChangeInfoWindow::InitSpecificUi()
{
    if (roleIndex == 0) {
        LoadCropAreas();
    } else {
        DataBaseManager &db = DataBaseManager::instance();
        QString field = db.GetExpertField(id);
        ui->expertiseEdit->setText(field);
    }
}

/**
 * @brief 加载农户作物区信息，并动态生成卡片
 */
void ChangeInfoWindow::LoadCropAreas(){
    // 清空原有作物区卡片
    ClearCropArea();
    DataBaseManager &db = DataBaseManager::instance();
    QVariantList cropAreas = db.GetCropAreas(id);
    int colCount = 6; // id, farmer_id, crop_type, area, location, detail
    if (cropAreas.isEmpty()) {
        ui->noCropLabel->setVisible(true);
        return;
    }
    ui->noCropLabel->setVisible(false);
    for (int i = 0; i + colCount - 1 < cropAreas.size(); i += colCount) {
        QVariantMap area;
        area["id"] = cropAreas[i + 0];
        area["farmer_id"] = cropAreas[i + 1];
        area["crop_type"] = cropAreas[i + 2];
        area["area"] = cropAreas[i + 3];
        area["location"] = cropAreas[i + 4];
        area["detail"] = cropAreas[i + 5];
        AddCropCard(area);
    }
}

/**
 * @brief 清空所有作物区卡片，仅保留空提示标签
 */
void ChangeInfoWindow::ClearCropArea(){
    QLayout *layout = ui->cropAreaLayout;
    for (int i = layout->count() - 1; i >= 0; --i) {
        QLayoutItem *item = layout->itemAt(i);
        QWidget *widget = item->widget();
        if (widget && widget != ui->noCropLabel) {
            layout->removeWidget(widget);
            delete widget;
        }
    }
}

/**
 * @brief 添加作物区卡片到界面，支持编辑和删除操作
 * @param area 作物区信息（QVariantMap）
 */
void ChangeInfoWindow::AddCropCard(const QVariantMap &area){
    // 创建卡片容器及内容
    QWidget *card = new QWidget();
    card->setMinimumHeight(110);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    card->setStyleSheet("background: #fff; border-radius: 16px; border: 2px solid #e0e6ed; margin-bottom: 22px; padding: 22px 18px 18px 22px;");
    QVBoxLayout *vbox = new QVBoxLayout(card);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(10);
    // 作物区ID
    QLabel *idLabel = new QLabel(QString("作物区ID：%1").arg(area["id"].toString()));
    idLabel->setStyleSheet("font-size: 13px; color: #888; margin-bottom: 2px;");
    vbox->addWidget(idLabel);
    // 顶部信息行
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setSpacing(18);
    QString info = QString("<b style='font-size:17px;'>%1</b> <span style='color:#aaa;font-size:14px;'>| %2亩 | %3</span>")
        .arg(area["crop_type"].toString())
        .arg(area["area"].toFloat())
        .arg(area["location"].toString());
    QLabel *infoLabel = new QLabel(info);
    infoLabel->setStyleSheet("font-size: 17px; color: #2c3e50; font-weight: bold;");
    infoLabel->setTextFormat(Qt::RichText);
    hbox->addWidget(infoLabel);
    // 编辑按钮
    QPushButton *editBtn = new QPushButton("编辑");
    editBtn->setStyleSheet("QPushButton { background: #f0fff4; color: #27ae60; border: 1.5px solid #27ae60; border-radius: 6px; padding: 8px 22px; font-size: 15px; font-weight: bold; } QPushButton:hover { background: #e0f7e0; }");
    hbox->addWidget(editBtn);
    // 删除按钮
    QPushButton *delBtn = new QPushButton("删除");
    delBtn->setStyleSheet("QPushButton { background: #fff0f0; color: #e74c3c; border: 1.5px solid #e74c3c; border-radius: 6px; padding: 8px 22px; font-size: 15px; font-weight: bold; } QPushButton:hover { background: #ffe0e0; }");
    hbox->addWidget(delBtn);
    hbox->addStretch();
    vbox->addLayout(hbox);
    // 说明
    QLabel *descLabel = new QLabel("说明：" + area["detail"].toString());
    descLabel->setStyleSheet("font-size: 15px; color: #888; background: #f8f9fa; border-radius: 9px; padding: 12px 18px; margin-top: 10px;");
    descLabel->setWordWrap(true);
    vbox->addWidget(descLabel);
    // 添加到布局（在noCropLabel前）
    int insertIdx = ui->cropAreaLayout->indexOf(ui->noCropLabel);
    ui->cropAreaLayout->insertWidget(insertIdx, card);
    // 优化滚动区域显示空间
    ui->cropAreaScroll->setMinimumHeight(400);
    ui->cropAreaScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 编辑按钮弹窗逻辑
    connect(editBtn, &QPushButton::clicked, this, [this, area]() {
        QDialog dialog(this);
        dialog.setWindowTitle("编辑作物区信息");
        dialog.setModal(true);
        dialog.resize(420, 340);
        dialog.setStyleSheet("QDialog { background: #fafdff; border-radius: 18px; }");
        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        mainLayout->setContentsMargins(24, 18, 24, 18);
        mainLayout->setSpacing(14);
        // 作物类型
        QLabel *typeLabel = new QLabel("作物类型：");
        QComboBox *typeCombo = new QComboBox();
        QStringList cropTypes = {"甘蔗", "小米/谷子", "大麦", "水稻", "豆类", "烟草", "花生", "玉米", "棉花", "小麦", "油籽作物"};
        typeCombo->addItems(cropTypes);
        int idx = cropTypes.indexOf(area["crop_type"].toString());
        if(idx >= 0) typeCombo->setCurrentIndex(idx);
        typeCombo->setStyleSheet("QComboBox { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
        // 面积
        QLabel *areaLabel = new QLabel("面积（亩）：");
        QDoubleSpinBox *areaSpin = new QDoubleSpinBox();
        areaSpin->setRange(0, 100000);
        areaSpin->setDecimals(2);
        areaSpin->setValue(area["area"].toFloat());
        areaSpin->setStyleSheet("QDoubleSpinBox { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
        // 位置
        QLabel *locLabel = new QLabel("位置：");
        QLineEdit *locEdit = new QLineEdit(area["location"].toString());
        locEdit->setPlaceholderText("请输入位置");
        locEdit->setStyleSheet("QLineEdit { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
        // 说明
        QLabel *descLabel = new QLabel("说明：");
        QTextEdit *descEdit = new QTextEdit(area["detail"].toString());
        descEdit->setPlaceholderText("请输入说明");
        descEdit->setStyleSheet("QTextEdit { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
        // 布局
        mainLayout->addWidget(typeLabel);
        mainLayout->addWidget(typeCombo);
        mainLayout->addWidget(areaLabel);
        mainLayout->addWidget(areaSpin);
        mainLayout->addWidget(locLabel);
        mainLayout->addWidget(locEdit);
        mainLayout->addWidget(descLabel);
        mainLayout->addWidget(descEdit);
        // 按钮
        QHBoxLayout *btnLayout = new QHBoxLayout();
        QPushButton *saveBtn = new QPushButton("保存");
        QPushButton *cancelBtn = new QPushButton("取消");
        saveBtn->setStyleSheet("QPushButton { background: #27ae60; color: white; border-radius: 8px; padding: 10px 32px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #219653; }");
        cancelBtn->setStyleSheet("QPushButton { background: #e0e6ed; color: #2c3e50; border-radius: 8px; padding: 10px 32px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #d0d6e0; }");
        btnLayout->addStretch();
        btnLayout->addWidget(saveBtn);
        btnLayout->addWidget(cancelBtn);
        mainLayout->addLayout(btnLayout);
        // 取消
        connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
        // 保存
        connect(saveBtn, &QPushButton::clicked, &dialog, [&, this]() {
            QString newType = typeCombo->currentText().trimmed();
            float newArea = areaSpin->value();
            QString newLoc = locEdit->text().trimmed();
            QString newDetail = descEdit->toPlainText().trimmed();
            if (newType.isEmpty() || newArea <= 0 || newLoc.isEmpty()) {
                QMessageBox::warning(&dialog, "警告", "作物类型、面积、位置不能为空且面积需大于0！");
                return;
            }
            // 更新数据库
            DataBaseManager &db = DataBaseManager::instance();
            bool ok = db.UpdateCropArea(area["id"].toInt(), newType, newArea, newLoc, newDetail);
            if (ok) {
                QMessageBox::information(&dialog, "成功", "作物区信息已更新！");
                dialog.accept();
                // 刷新作物区列表
                this->LoadCropAreas();
            } else {
                QMessageBox::critical(&dialog, "错误", "更新失败，请重试！\n" + db.GetLastError());
            }
        });
        dialog.exec();
    });
    // 删除按钮逻辑
    connect(delBtn, &QPushButton::clicked, this, [this, area]() {
        // 检查当前作物区数量，至少保留一个
        DataBaseManager &db = DataBaseManager::instance();
        QVariantList cropAreas = db.GetCropAreas(id); // id为farmerId
        int colCount = 6;
        int areaCount = cropAreas.size() / colCount;
        if (areaCount <= 1) {
            QMessageBox::warning(this, "操作被拒绝", "每个农户至少要有一个作物区，无法删除最后一个作物区！");
            return;
        }
        // 确认删除
        QMessageBox::StandardButton reply = QMessageBox::question(this, "确认删除", "确定要删除该作物区吗？此操作不可恢复。", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            bool ok = db.DeleteCropArea(area["id"].toInt());
            if (ok) {
                QMessageBox::information(this, "删除成功", "作物区已删除。");
                this->LoadCropAreas();
            } else {
                QMessageBox::critical(this, "删除失败", "删除失败，请重试！\n" + db.GetLastError());
            }
        }
    });
}

/**
 * @brief 添加作物区按钮点击槽，弹窗输入并添加新作物区
 */
void ChangeInfoWindow::on_addCropButton_clicked(){
    QDialog dialog(this);
    dialog.setWindowTitle("添加作物区");
    dialog.setModal(true);
    dialog.resize(420, 340);
    dialog.setStyleSheet("QDialog { background: #fafdff; border-radius: 18px; } ");
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(24, 18, 24, 18);
    mainLayout->setSpacing(14);
    // 作物类型
    QLabel *typeLabel = new QLabel("作物类型：");
    QComboBox *typeCombo = new QComboBox();
    QStringList cropTypes = {"甘蔗", "小米/谷子", "大麦", "水稻", "豆类", "烟草", "花生", "玉米", "棉花", "小麦", "油籽作物"};
    typeCombo->addItems(cropTypes);
    typeCombo->setStyleSheet("QComboBox { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
    // 面积
    QLabel *areaLabel = new QLabel("面积（亩）：");
    QDoubleSpinBox *areaSpin = new QDoubleSpinBox();
    areaSpin->setRange(0, 100000);
    areaSpin->setDecimals(2);
    areaSpin->setStyleSheet("QDoubleSpinBox { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
    // 位置
    QLabel *locLabel = new QLabel("位置：");
    QLineEdit *locEdit = new QLineEdit();
    locEdit->setPlaceholderText("请输入位置");
    locEdit->setStyleSheet("QLineEdit { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
    // 说明
    QLabel *descLabel = new QLabel("说明：");
    QTextEdit *descEdit = new QTextEdit();
    descEdit->setPlaceholderText("请输入说明");
    descEdit->setStyleSheet("QTextEdit { border: 1.5px solid #e0e6ed; border-radius: 7px; padding: 8px 12px; font-size: 15px; background: #fff; }");
    // 布局
    mainLayout->addWidget(typeLabel);
    mainLayout->addWidget(typeCombo);
    mainLayout->addWidget(areaLabel);
    mainLayout->addWidget(areaSpin);
    mainLayout->addWidget(locLabel);
    mainLayout->addWidget(locEdit);
    mainLayout->addWidget(descLabel);
    mainLayout->addWidget(descEdit);
    // 按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *saveBtn = new QPushButton("保存");
    QPushButton *cancelBtn = new QPushButton("取消");
    saveBtn->setStyleSheet("QPushButton { background: #27ae60; color: white; border-radius: 8px; padding: 10px 32px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #219653; }");
    cancelBtn->setStyleSheet("QPushButton { background: #e0e6ed; color: #2c3e50; border-radius: 8px; padding: 10px 32px; font-size: 16px; font-weight: bold; } QPushButton:hover { background: #d0d6e0; }");
    btnLayout->addStretch();
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);
    // 取消
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    // 保存
    connect(saveBtn, &QPushButton::clicked, &dialog, [&, this]() {
        QString newType = typeCombo->currentText().trimmed();
        float newArea = areaSpin->value();
        QString newLoc = locEdit->text().trimmed();
        QString newDetail = descEdit->toPlainText().trimmed();
        if (newType.isEmpty() || newArea <= 0 || newLoc.isEmpty() || newDetail.isEmpty()) {
            QMessageBox::warning(&dialog, "警告", "作物类型、面积、位置、说明不能为空且面积需大于0！");
            return;
        }
        // 添加到数据库
        DataBaseManager &db = DataBaseManager::instance();
        bool ok = db.AddCropArea(id, newType, newArea, newLoc, newDetail); // id为farmerId
        if (ok) {
            dialog.accept(); // 先关闭弹窗
            QMessageBox::information(this, "成功", "作物区添加成功！");
            this->LoadCropAreas();
        } else {
            QMessageBox::critical(&dialog, "错误", "添加失败，请重试！\n" + db.GetLastError());
        }
    });
    dialog.exec();
}

/**
 * @brief 保存按钮点击槽，校验并保存用户信息
 */
void ChangeInfoWindow::on_saveButton_clicked()
{
    // 获取当前输入
    QString name = ui->nameEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->confirmPasswordEdit->text();
    QString field = ui->expertiseEdit->text().trimmed();
    // 获取原始信息
    DataBaseManager &db = DataBaseManager::instance();
    int userId = (roleIndex == 0) ? db.GetUserIdByFarmerId(id) : db.GetUserIdByExpertId(id);
    QVariantList info = db.GetUserInfo(userId);
    QString oldName = info.value(1).toString();
    QString oldPhone = info.value(2).toString();
    QString oldPassword = info.value(3).toString();
    QString oldField = db.GetExpertField(id);
    // 检查是否有变化（密码只在有输入时才算变化）
    bool changed = (name != oldName) || (phone != oldPhone);
    if(roleIndex == 1){
        changed = (name != oldName) || (phone != oldPhone) || (field != oldField);
    }
    if (!password.isEmpty()) changed = true;
    if (!changed) {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
        msgBox.setWindowTitle("无更改");
        msgBox.setText("信息未发生变化，无需保存。");
        msgBox.exec();
        return;
    }
    // 校验
    if (name.isEmpty() || phone.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
        msgBox.setWindowTitle("警告");
        msgBox.setText("姓名、电话不能为空！");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    // 手机号格式校验
    QRegularExpression reg("^1\\d{10}$");
    if (!reg.match(phone).hasMatch()) {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
        msgBox.setWindowTitle("警告");
        msgBox.setText("手机号格式不正确，请输入11位以1开头的手机号！");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    // 手机号唯一性校验（允许自己原手机号，但不允许与他人重复）
    if (phone != oldPhone && db.IsUserExists(phone)) {
        QMessageBox msgBox;
        msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
        msgBox.setWindowTitle("警告");
        msgBox.setText("该手机号已被注册，请使用其他手机号！");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    // 密码校验（只有有输入时才校验）
    QString hashedPassword = oldPassword;
    if (!password.isEmpty()) {
        if (password != confirmPassword) {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("警告");
            msgBox.setText("两次输入的密码不一致！");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();
            return;
        }
        hashedPassword = DataBaseManager::hashPassword(password);
    }
    // 更新数据库
    QString role = info.value(4).toString();
    bool ok = false;
    if(roleIndex == 1){
        // 专家，开启事务
        if(!db.BeginTransaction()){
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("保存失败");
            msgBox.setText("无法开启数据库事务！");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }
        ok = db.UpdateUser(userId, name, phone, hashedPassword, role);
        if(ok){
            ok = db.UpdateExpert(id, field);
        }
        if(ok){
            if(!db.CommitTransaction()){
                db.RollbackTransaction();
                QMessageBox msgBox;
                msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
                msgBox.setWindowTitle("保存失败");
                msgBox.setText("提交事务失败！");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
                return;
            }
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("保存成功");
            msgBox.setText("用户信息已更新！");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }else{
            db.RollbackTransaction();
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("保存失败");
            msgBox.setText("更新失败，请重试！\n" + db.GetLastError());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
        return;
    }else{
        // 农户，单表更新
        ok = db.UpdateUser(userId, name, phone, hashedPassword, role);
        if (ok) {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("保存成功");
            msgBox.setText("用户信息已更新！");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QPushButton { color: black; background: white; }");
            msgBox.setWindowTitle("保存失败");
            msgBox.setText("更新失败，请重试！\n" + db.GetLastError());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

/**
 * @brief 登出按钮点击槽，发送登出信号并关闭窗口
 */
void ChangeInfoWindow::on_logoutButton_clicked()
{
    isLogout = true;
    emit logOut();
    this->close();
}
