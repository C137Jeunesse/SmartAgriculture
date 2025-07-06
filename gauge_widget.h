// gauge_widget.h
// 仪表盘控件头文件，支持数值显示与动态颜色变化
#ifndef GAUGE_WIDGET_H
#define GAUGE_WIDGET_H

#include <QWidget>
#include <QColor>
#include <QString>

/**
 * @brief 仪表盘控件类
 * 用于显示实时数值，支持动态颜色变化。
 */
class GaugeWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param title 仪表盘标题
     * @param unit 单位字符串
     * @param parent 父窗口
     */
    explicit GaugeWidget(const QString &title, const QString &unit, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~GaugeWidget() override;
    /**
     * @brief 设置数值范围
     * @param min 最小值
     * @param max 最大值
     */
    void setRange(double min, double max);
    /**
     * @brief 设置当前数值
     * @param value 当前值
     */
    void setValue(double value);

protected:
    /**
     * @brief 重绘事件，绘制仪表盘
     * @param event 绘图事件
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_title;      ///< 仪表盘标题
    QString m_unit;       ///< 单位
    double m_minValue;    ///< 最小值
    double m_maxValue;    ///< 最大值
    double m_currentValue;///< 当前值
    QColor m_arcColor;    ///< 弧线颜色
};

#endif // GAUGE_WIDGET_H
