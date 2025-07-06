// registerwindow.h
// 注册窗口类头文件，负责用户注册、表单校验、窗口拖动等功能
#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class RegisterWindow;
}

/**
 * @brief 注册窗口类
 * 负责用户注册、表单校验、窗口拖动等功能。
 */
class RegisterWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit RegisterWindow(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~RegisterWindow();

private:
    Ui::RegisterWindow *ui; ///< UI指针

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
    /**
     * @brief 页面关闭事件，发送关闭信号
     */
    void closeEvent(QCloseEvent *event);

private slots:
    /**
     * @brief 手机号输入变化槽，实时校验手机号格式
     * @param text 当前输入内容
     */
    void onPhoneTextChanged(const QString &text);
    /**
     * @brief 注册按钮点击槽，处理注册逻辑
     */
    void on_pushButtonRegister_clicked();
    /**
     * @brief 角色下拉框激活槽，切换注册表单内容
     * @param index 当前选中索引
     */
    void on_comboBoxRole_activated(int index);

signals:
    /**
     * @brief 注册窗口关闭信号
     */
    void closedSignal();
};

#endif // REGISTERWINDOW_H
