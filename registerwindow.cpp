// registerwindow.cpp
// 注册窗口类实现文件，实现用户注册、表单校验、窗口拖动等功能
#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "databasemanager.h"

#include <QRegularExpression>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPushButton>
#include <QMouseEvent>

static bool islegal=false;

/**
 * @brief 构造函数，初始化UI、信号槽、窗口属性等
 * @param parent 父窗口指针
 */
RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    // 初始化界面信息
    ui->labelPhoneTip->setText("输入正确的手机号");
    ui->labelPhoneTip->setStyleSheet("color:grey;");
    ui->labelAreaTip->setText("允许最多 4 位整数和最多 2 位小数");
    ui->labelAreaTip->setStyleSheet("color:grey;");
    // 作物区面积输入正则
    QRegularExpression reg("^[0-9]{1,4}(\\.[0-9]{1,2})?$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(reg, this);
    ui->lineEditArea->setValidator(validator);
    // 连接手机号输入变化信号
    connect(ui->lineEditPhone, &QLineEdit::textChanged, this, &RegisterWindow::onPhoneTextChanged);
    // 设置无边框极简风格
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    // 关闭按钮
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &RegisterWindow::close);
    // 窗口自适应内容并禁止缩放
    this->adjustSize();
    this->setFixedSize(this->size());
}

/**
 * @brief 析构函数，释放UI资源
 */
RegisterWindow::~RegisterWindow()
{
    delete ui;
}

/**
 * @brief 手机号输入变化槽，实时校验手机号格式
 * @param text 当前输入内容
 */
void RegisterWindow::onPhoneTextChanged(const QString &text)
{
    QRegularExpression reg("^1\\d{10}$");
    if (reg.match(text).hasMatch()) {
        ui->labelPhoneTip->setText("格式正确");
        ui->labelPhoneTip->setStyleSheet("color:green;");
        islegal=true;
    } else {
        ui->labelPhoneTip->setText("手机号格式不正确");
        ui->labelPhoneTip->setStyleSheet("color:red;");
        islegal=false;
    }
}

/**
 * @brief 注册按钮点击槽，处理注册逻辑
 */
void RegisterWindow::on_pushButtonRegister_clicked()
{
    if(!islegal){
        QMessageBox::critical(this, "错误", "手机号格式不正确，请重新输入！");
        return;
    }
    DataBaseManager &db=DataBaseManager::instance();
    // 判断数据库是否连接
    if (!db.TestConnection()) {
        QMessageBox::warning(this, "警告", "数据库连接不稳定，请检查网络后重试！");
        return;
    }
    // 查询注册用户是否存在
    QString phone = ui->lineEditPhone->text();
    if (db.IsUserExists(phone)) {
        QMessageBox::warning(this, "警告", "该手机号已被注册，请使用其他手机号！");
        ui->lineEditPhone->clear();
        return;
    }
    // 获取输入的用户名、密码、角色
    QString username = ui->lineEditName->text();
    QString password = ui->lineEditPassword->text();
    QString role=ui->comboBoxRole->currentText();
    // 角色转英文
    if (role == "农户"){
        role = "farmer";
    } else if (role == "专家") {
        role = "expert";
    }
    // 检查用户名和密码是否为空
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空，请重新输入！");
        return;
    }
    // 注册用户，开启事务
    if (!db.BeginTransaction()) {
        QMessageBox::critical(this, "错误", "无法开启数据库事务");
        return;
    }
    QString sqlErrorMsg;
    QString hashedPassword = DataBaseManager::hashPassword(password);
    int userId = db.AddUser(username, phone, hashedPassword, role, &sqlErrorMsg);
    if (userId != -1) {
        // 用户表注册成功，根据用户注册不同表
        bool success;
        if(role == "farmer"){
            // 获取农户相关作物区信息
            QString cropType = ui->comboBoxCropType->currentText();
            float area = ui->lineEditArea->text().toFloat();
            QString location = ui->lineEditLocation->text();
            QString detail = ui->lineEditDetail->text();
            // 检查相关作物区信息是否为空
            if(cropType.isEmpty() || area <= 0 || location.isEmpty() || detail.isEmpty()){
                QMessageBox::warning(this, "警告", "作物区信息不能为空，请重新输入！");
                return;
            }
            // 注册农户作物区信息
            int farmerId = db.AddFarmerUser(userId);
            success = db.AddCropArea(farmerId, cropType, area, location, detail);
            if(!success){
                sqlErrorMsg = db.GetLastError();
                QMessageBox::critical(this, "错误", QString("信息注册失败，请稍后再试！\n错误信息：%1").arg(sqlErrorMsg));
                return;
            }
        }else{
            // 检查领域信息是否为空
            QString field = ui->lineEditField->text();
            if(field.isEmpty()){
                QMessageBox::warning(this, "警告", "领域信息不能为空，请重新输入！");
                return;
            }
            // 注册专家领域信息
            success = db.AddExpertUser(userId, field);
            if(!success){
                sqlErrorMsg = db.GetLastError();
                QMessageBox::critical(this, "错误", QString("信息注册失败，请稍后再试！\n错误信息：%1").arg(sqlErrorMsg));
                return;
            }
        }
        // 提交事务
        if (!db.CommitTransaction()) {
            db.RollbackTransaction();
            QMessageBox::critical(this, "错误", "提交注册信息失败");
            return;
        }
        QMessageBox::information(this, "成功", "注册成功！");
        this->close();
    } else {
        QMessageBox::critical(this, "错误", QString("注册失败，请稍后再试！\n错误信息：%1").arg(sqlErrorMsg));
        return;
    }
}

/**
 * @brief 页面关闭事件，发送关闭信号
 */
void RegisterWindow::closeEvent(QCloseEvent *event)
{
    emit closedSignal();
    QMainWindow::closeEvent(event);
}

/**
 * @brief 角色下拉框激活槽，切换注册表单内容
 * @param index 当前选中索引
 */
void RegisterWindow::on_comboBoxRole_activated(int index)
{
    if(index==1){
        ui->labelField->setVisible(true);
        ui->lineEditField->setVisible(true);
        ui->labelCropType->setVisible(false);
        ui->comboBoxCropType->setVisible(false);
        ui->labelArea->setVisible(false);
        ui->lineEditArea->setVisible(false);
        ui->labelLocation->setVisible(false);
        ui->lineEditLocation->setVisible(false);
        ui->labelDetail->setVisible(false);
        ui->lineEditDetail->setVisible(false);
        ui->labelAreaTip->setVisible(false);
    }else{
        ui->labelField->setVisible(false);
        ui->lineEditField->setVisible(false);
        ui->labelCropType->setVisible(true);
        ui->comboBoxCropType->setVisible(true);
        ui->labelArea->setVisible(true);
        ui->lineEditArea->setVisible(true);
        ui->labelLocation->setVisible(true);
        ui->lineEditLocation->setVisible(true);
        ui->labelDetail->setVisible(true);
        ui->lineEditDetail->setVisible(true);
        ui->labelAreaTip->setVisible(true);
    }
}

/**
 * @brief 鼠标按下事件，处理窗口拖动
 */
void RegisterWindow::mousePressEvent(QMouseEvent *event)
{
    // 只允许左键拖动，且在registerFrame区域内
    if (event->button() == Qt::LeftButton && ui->registerFrame->geometry().contains(event->pos())) {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
        event->accept();
    }
}

/**
 * @brief 鼠标移动事件，处理窗口拖动
 */
void RegisterWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        this->move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

/**
 * @brief 鼠标释放事件，处理窗口拖动
 */
void RegisterWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    QMainWindow::mouseReleaseEvent(event);
}
