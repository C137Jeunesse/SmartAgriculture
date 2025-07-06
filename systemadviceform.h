// systemadviceform.h
// 系统建议表单窗口头文件，支持农户/专家提交模型优化建议
#ifndef SYSTEMADVICEFORM_H
#define SYSTEMADVICEFORM_H

#include <QWidget>

namespace Ui {
class SystemAdviceForm;
}

/**
 * @brief 系统建议表单窗口类
 * 支持农户/专家提交模型优化建议。
 */
class SystemAdviceForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param id 用户id
     * @param roleIndex 角色索引（0-农户，1-专家）
     * @param parent 父窗口
     */
    explicit SystemAdviceForm(int id, int roleIndex, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~SystemAdviceForm();

signals:
    /**
     * @brief 窗口关闭信号
     */
    void closeSignal();

protected:
    /**
     * @brief 重写关闭事件，发送关闭信号
     * @param event 关闭事件指针
     */
    void closeEvent(QCloseEvent *event) override;

private slots:
    /**
     * @brief 提交按钮点击槽
     */
    void onSubmitButtonClicked();

private:
    int id; ///< 当前用户id
    int roleIndex; ///< 角色索引（0-农户，1-专家）
    Ui::SystemAdviceForm *ui; ///< UI指针
};

#endif // SYSTEMADVICEFORM_H
