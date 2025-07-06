// adminwindow.h
// 管理员主窗口类头文件，负责显示和管理系统建议信息
#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminWindow;
}

/**
 * @brief 管理员主窗口类
 * 负责显示系统建议列表，刷新建议，添加和清空建议卡片等功能。
 */
class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     */
    explicit AdminWindow(QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~AdminWindow();

private slots:
    /**
     * @brief 刷新按钮点击槽函数，刷新建议列表
     */
    void on_pushButton_refresh_clicked();

private:
    /**
     * @brief 加载建议列表并显示到界面
     */
    void loadAdviceList();
    /**
     * @brief 添加一条建议卡片到界面
     * @param advice 建议内容（QVariantList，包含id、user_id、role、content）
     */
    void addAdviceCard(const QVariantList &advice);
    /**
     * @brief 清空所有建议卡片（保留空提示标签）
     */
    void clearAdviceCards();
    /**
     * @brief UI指针
     */
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
