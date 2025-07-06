// expertwindow.h
// 专家主窗口类头文件，负责专家作物区管理、建议填写、系统建议、窗口切换等功能
#ifndef EXPERTWINDOW_H
#define EXPERTWINDOW_H

#include "changeinfowindow.h"
#include "expertadviceform.h"
#include "systemadviceform.h"
#include "systemwindow.h"

#include <QMainWindow>

namespace Ui {
class ExpertWindow;
}

/**
 * @brief 专家主窗口类
 * 负责专家作物区管理、建议填写、系统建议、窗口切换等功能。
 */
class ExpertWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param expertId 当前专家ID
     * @param parent 父窗口指针
     */
    explicit ExpertWindow(int expertId, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~ExpertWindow();

    /**
     * @brief 设置用户名显示
     * @param name 用户名
     */
    void setUserName(const QString &name);

private slots:
    /**
     * @brief 修改信息按钮点击槽
     */
    void on_updateInfoButton_clicked();
    /**
     * @brief 系统建议按钮点击槽
     */
    void on_suggestButton_clicked();
    /**
     * @brief 重新显示主窗口槽
     */
    void ReShow();
    /**
     * @brief 登出槽
     */
    void onLogOut();

private:
    int expertId; ///< 当前专家ID
    Ui::ExpertWindow *ui; ///< UI指针

    ChangeInfoWindow *changeInfoWindow; ///< 信息修改窗口指针
    ExpertAdviceForm *expertAdviceForm; ///< 专家建议窗口指针
    SystemAdviceForm *systemAdviceForm; ///< 系统建议窗口指针
    SystemWindow *sysWin; ///< 系统分析窗口指针
    // 动态加载作物区相关
    /**
     * @brief 动态加载作物区信息
     */
    void loadCropAreas();
    /**
     * @brief 清空作物区卡片
     */
    void clearCropAreas();
    /**
     * @brief 添加作物区卡片到界面
     * @param areaInfo 作物区信息
     * @param farmerPhone 农户手机号
     */
    void addCropCard(const QVariantList &areaInfo, const QString &farmerPhone);

signals:
    /**
     * @brief 专家登出信号
     */
    void logout();
};

#endif // EXPERTWINDOW_H
