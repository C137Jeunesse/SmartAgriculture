// mainwindow.cpp
// 主窗口类实现文件，实现登录、注册、窗口切换、主界面拖动等功能
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QPalette>
#include <QMessageBox>
#include <QProgressDialog>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

static bool islegal=false;

/**
 * @brief 构造函数，初始化UI、信号槽、窗口属性等
 * @param parent 父窗口指针
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rWindow=nullptr;
    aWindow=nullptr;
    fWindow=nullptr;
    eWindow=nullptr;

    // 手机号正则验证
    QRegularExpression phoneReg("^1\\d{10}$");
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(phoneReg, this);
    ui->lineEditPhone->setValidator(phoneValidator);
    connect(ui->lineEditPhone, &QLineEdit::textChanged, this, [this](const QString &text){
        if (text.isEmpty()) {
            ui->lineEditPhone->setStyleSheet("border: 1px solid #bdbdbd; border-radius: 6px; padding-left: 8px; font-size: 15px;");
            islegal=false;
        } else if (ui->lineEditPhone->hasAcceptableInput()) {
            ui->lineEditPhone->setStyleSheet("border: 1px solid #4caf50; border-radius: 6px; padding-left: 8px; font-size: 15px; background: #e8f5e9;");
            islegal=true;
        } else {
            ui->lineEditPhone->setStyleSheet("border: 1px solid #e53935; border-radius: 6px; padding-left: 8px; font-size: 15px; background: #ffebee;");
            islegal=false;
        }
    });

    // 切换到注册界面
    connect(ui->pushButtonSwitchMode, &QPushButton::clicked, this, &MainWindow::on_pushButtonRegister_clicked);

    // 窗口自适应内容并禁止缩放
    this->adjustSize();
    this->setFixedSize(this->size());
    // 设置无边框极简风格
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    // 关闭按钮
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &MainWindow::close);
}

/**
 * @brief 析构函数，释放UI资源
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 注册按钮点击槽，切换到注册窗口
 */
void MainWindow::on_pushButtonRegister_clicked()
{
    qDebug() << "Switching to Register Window";
    this->hide();
    if(rWindow==nullptr){
        rWindow=new RegisterWindow();
        qDebug() << "Creating new RegisterWindow instance";
        connect(rWindow, &RegisterWindow::closedSignal, this, &MainWindow::ReShow);
    }
    rWindow->show();
}

/**
 * @brief 注册窗口关闭后重新显示主窗口
 */
void MainWindow::ReShow(){
    this->show();
    disconnect(rWindow, &RegisterWindow::closedSignal, this, &MainWindow::ReShow);
    delete rWindow;
    rWindow=nullptr;
}

/**
 * @brief 登录按钮点击槽，处理登录逻辑
 */
void MainWindow::on_pushButtonLogin_clicked()
{
    if(!islegal) {
        QMessageBox::critical(this, "错误", "手机号格式不正确，请重新输入！");
        return;
    }
    QString name = ui->lineEditName->text();
    if (name.isEmpty()) {  
        QMessageBox::warning(this, "警告", "用户名不能为空，请输入用户名！");
        return;
    }
    QString phone = ui->lineEditPhone->text();
    QString password = ui->lineEditPassword->text();
    QString role = ui->comboBoxRole->currentText();
    if(role == "管理员") {
        role = "admin";
    } else if(role == "农户") {
        role = "farmer";
    }else if(role == "专家") {
        role = "expert";
    } 
    // 显示进度条
    QProgressDialog *progress = new QProgressDialog("正在登录，请稍候...", QString(), 0, 0, this);
    progress->setWindowModality(Qt::WindowModal);
    progress->setCancelButton(nullptr);
    progress->setMinimumDuration(0);
    progress->setStyleSheet(
        "QProgressDialog { background: white; border: 2px solid #3498db; border-radius: 10px; }"
        "QLabel { color: #3498db; font-size: 16px; }"
        "QProgressBar { height: 16px; border-radius: 8px; background: #e0e0e0; }"
        "QProgressBar::chunk { background: #3498db; }"
    );
    progress->show();
    qApp->processEvents();
    // 用QFutureWatcher监控线程
    QFutureWatcher<QPair<bool, QString>> *watcher = new QFutureWatcher<QPair<bool, QString>>(this);
    // 登录逻辑放到子线程
    QFuture<QPair<bool, QString>> future = QtConcurrent::run([=]() -> QPair<bool, QString> {
        DataBaseManager &db = DataBaseManager::instance();
        if (!db.TestConnection()) {
            return qMakePair(false, QString("数据库连接不稳定，请检查网络后重试！"));
        }
        QString userRole;
        if (db.CheckUserLogin(name, phone, password, userRole)) {
            if (userRole == role) {
                return qMakePair(true, userRole);
            } else {
                return qMakePair(false, QString("登录失败，请检查手机号、密码和角色是否匹配！"));
            }
        } else {
            return qMakePair(false, QString("登录失败，请检查手机号和密码是否正确！"));
        }
    });
    watcher->setFuture(future);
    connect(watcher, &QFutureWatcher<QPair<bool, QString>>::finished, this, [=]() {
        QPair<bool, QString> result = watcher->result();
        if (result.first) {
            // 登录成功，主线程跳转
            if (role == "admin") {
                aWindow = new AdminWindow();
                aWindow->show();
            } else if (role == "farmer") {
                DataBaseManager &db = DataBaseManager::instance();
                int userId = db.GetUserIdByPhone(phone);
                int farmerId = db.GetFarmerId(userId);
                fWindow = new FarmerWindow(farmerId);
                fWindow->setUserName(name);
                connect(fWindow,&FarmerWindow::logout,this,&MainWindow::show);
                fWindow->show();
            } else if (role == "expert") {
                DataBaseManager &db = DataBaseManager::instance();
                int userId = db.GetUserIdByPhone(phone);
                int expertId = db.GetExpertId(userId);
                eWindow = new ExpertWindow(expertId);
                eWindow->setUserName(name);
                connect(eWindow, &ExpertWindow::logout, this, &MainWindow::show);
                eWindow->show();
            }
            progress->close();
            progress->deleteLater();
            this->hide();
        } else {
            progress->close();
            progress->deleteLater();
            QMessageBox::warning(this, "登录失败", result.second);
        }
        watcher->deleteLater();
    });
}

/**
 * @brief 登出槽函数，关闭子窗口并显示主窗口
 */
void MainWindow::onLogout() {
    if (fWindow) { fWindow->close(); delete fWindow; fWindow = nullptr; }
    if (eWindow) { eWindow->close(); delete eWindow; eWindow = nullptr; }
    if (aWindow) { aWindow->close(); delete aWindow; aWindow = nullptr; }
    this->show();
}

/**
 * @brief 鼠标按下事件，处理窗口拖动
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 只允许左键拖动，且在loginFrame区域内
    if (event->button() == Qt::LeftButton && ui->loginFrame->geometry().contains(event->pos())) {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
        event->accept();
    }
}

/**
 * @brief 鼠标移动事件，处理窗口拖动
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        this->move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

/**
 * @brief 鼠标释放事件，处理窗口拖动
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    QMainWindow::mouseReleaseEvent(event);
}
