// changeinfowindow.h
// 用户信息修改窗口类头文件，支持农户/专家信息及作物区管理
#ifndef CHANGEINFOWINDOW_H
#define CHANGEINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeInfoWindow;
}

/**
 * @brief 用户信息修改窗口类
 * 支持农户/专家信息修改、作物区动态管理、登出等功能。
 */
class ChangeInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param id 用户id（农户或专家）
     * @param roleIndex 角色索引（0-农户，1-专家）
     * @param parent 父窗口指针
     */
    explicit ChangeInfoWindow(int id, int roleIndex, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~ChangeInfoWindow();

private:
    int id;                ///< 当前用户id
    int roleIndex;         ///< 角色索引（0-农户，1-专家）
    Ui::ChangeInfoWindow *ui; ///< UI指针
    bool isLogout = false; ///< 是否为登出操作

    /**
     * @brief 重写关闭事件，处理未保存修改和信号发送
     * @param event 关闭事件指针
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief 初始化特定角色UI（农户加载作物区，专家加载领域）
     */
    void InitSpecificUi();
    /**
     * @brief 加载农户作物区信息
     */
    void LoadCropAreas();
    /**
     * @brief 清空作物区卡片
     */
    void ClearCropArea();
    /**
     * @brief 添加作物区卡片到界面
     * @param area 作物区信息（QVariantMap）
     */
    void AddCropCard(const QVariantMap &area);

signals:
    /**
     * @brief 窗口关闭信号
     */
    void closeSignal();
    /**
     * @brief 登出信号
     */
    void logOut();

private slots:
    /**
     * @brief 取消按钮点击槽，关闭窗口
     */
    void on_cancelButton_clicked();
    /**
     * @brief 添加作物区按钮点击槽
     */
    void on_addCropButton_clicked();
    /**
     * @brief 保存按钮点击槽
     */
    void on_saveButton_clicked();
    /**
     * @brief 登出按钮点击槽
     */
    void on_logoutButton_clicked();
};

#endif // CHANGEINFOWINDOW_H
