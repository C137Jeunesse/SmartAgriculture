// expertadviceform.h
// 专家建议表单窗口头文件，支持专家对作物区填写建议
#ifndef EXPERTADVICEFORM_H
#define EXPERTADVICEFORM_H

#include <QWidget>

namespace Ui {
class ExpertAdviceForm;
}

/**
 * @brief 专家建议表单窗口类
 * 支持专家对作物区填写、管理建议。
 */
class ExpertAdviceForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param expertId 专家id
     * @param cropAreaId 作物区id
     * @param parent 父窗口
     */
    explicit ExpertAdviceForm(int expertId, int cropAreaId, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~ExpertAdviceForm();

private:
    int expertId; ///< 专家id
    int cropAreaId; ///< 作物区id
    Ui::ExpertAdviceForm *ui; ///< UI指针

    /**
     * @brief 重写关闭事件，发送关闭信号
     * @param event 关闭事件指针
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief 加载建议列表
     */
    void loadAdviceList();
    /**
     * @brief 清空建议卡片
     */
    void clearAdviceList();
    /**
     * @brief 添加建议卡片到界面
     * @param adviceInfo 建议信息（QVariantList）
     */
    void addAdviceCard(const QVariantList &adviceInfo);

signals:
    /**
     * @brief 窗口关闭信号
     */
    void closeSignal();
private slots:
    /**
     * @brief 添加建议按钮点击槽
     */
    void on_addAdviceButton_clicked();
};

#endif // EXPERTADVICEFORM_H
