// mainwindow.h
// 主窗口类头文件，负责登录、注册、窗口切换及主界面拖动等功能
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registerwindow.h"
#include "adminwindow.h"
#include "farmerwindow.h"
#include "expertwindow.h"
#include "changeinfowindow.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief 主窗口类
 * 负责登录、注册、窗口切换、主界面拖动等功能。
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~MainWindow();

public slots:
    /**
     * @brief 登出槽函数，关闭子窗口并显示主窗口
     */
    void onLogout();

private slots:
    /**
     * @brief 注册按钮点击槽，切换到注册窗口
     */
    void on_pushButtonRegister_clicked();
    /**
     * @brief 注册窗口关闭后重新显示主窗口
     */
    void ReShow();
    /**
     * @brief 登录按钮点击槽，处理登录逻辑
     */
    void on_pushButtonLogin_clicked();

private:
    Ui::MainWindow *ui; ///< UI指针
    RegisterWindow *rWindow; ///< 注册窗口指针
    AdminWindow *aWindow;    ///< 管理员窗口指针
    FarmerWindow *fWindow;   ///< 农户窗口指针
    ExpertWindow *eWindow;   ///< 专家窗口指针

    // 拖动窗口相关
    bool m_dragging = false; ///< 是否正在拖动
    QPoint m_dragPosition;   ///< 拖动起始位置

protected:
    /**
     * @brief 鼠标按下事件，处理窗口拖动
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * @brief 鼠标移动事件，处理窗口拖动
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /**
     * @brief 鼠标释放事件，处理窗口拖动
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
