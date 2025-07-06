// farmerwindow.h
// 农户主窗口类头文件，负责农户建议查看、个人信息管理、系统建议、窗口切换等功能
#ifndef FARMERWINDOW_H
#define FARMERWINDOW_H
#include "changeinfowindow.h"
#include "systemadviceform.h"
#include "systemwindow.h"

#include <QMainWindow>
#include <QMap>

namespace Ui {
class FarmerWindow;
}

/**
 * @brief 农户主窗口类
 * 负责农户建议查看、个人信息管理、系统建议、窗口切换等功能。
 */
class FarmerWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param farmerId 当前农户ID
     * @param parent 父窗口指针
     */
    explicit FarmerWindow(int farmerId, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~FarmerWindow();

    /**
     * @brief 设置用户名显示
     * @param name 用户名
     */
    void setUserName(const QString &name);

private slots:
    /**
     * @brief 刷新建议卡片槽
     */
    void refreshSuggestions();
    /**
     * @brief 修改信息按钮点击槽
     */
    void UpdateButtonClicked();
    /**
     * @brief 重新显示主窗口槽
     */
    void ReShow();
    /**
     * @brief 系统建议按钮点击槽
     */
    void on_suggestButton_clicked();
    /**
     * @brief 查看系统建议按钮点击槽
     */
    void on_viewSystemAdviceButton_clicked();
    /**
     * @brief 登出槽
     */
    void onLogOut();

private:
    int currentFarmerId; ///< 当前农户ID
    Ui::FarmerWindow *ui; ///< UI指针

    ChangeInfoWindow *changeWindow; ///< 信息修改窗口指针
    SystemAdviceForm *systemAdviceForm; ///< 系统建议窗口指针
    SystemWindow *sysWin; ///< 系统分析窗口指针

    // 类别颜色映射
    QMap<QString, QString> categoryColors = {
        {"病虫害", "#e74c3c"},
        {"灌溉", "#3498db"},
        {"施肥", "#f39c12"},
        {"收获", "#27ae60"},
        {"其他", "#9b59b6"}
    };

    /**
     * @brief 初始化UI
     */
    void initUI();
    /**
     * @brief 加载建议卡片
     */
    void loadSuggestions();
    /**
     * @brief 创建建议卡片
     * @param suggestion 建议内容
     */
    void createSuggestionCard(const QVariantMap& suggestion);
    /**
     * @brief 清空所有建议卡片
     */
    void clearSuggestions();
    /**
     * @brief 显示建议详情对话框
     * @param suggestion 建议内容
     */
    void showSuggestionDetail(const QVariantMap& suggestion);

signals:
    /**
     * @brief 农户登出信号
     */
    void logout();
};

#endif // FARMERWINDOW_H
