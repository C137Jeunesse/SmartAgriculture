// gauge_widget.cpp
// 仪表盘控件实现文件，实现数值显示与动态颜色变化
#include "gauge_widget.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>

/**
 * @brief 构造函数，初始化仪表盘标题、单位、范围和颜色
 * @param title 仪表盘标题
 * @param unit 单位
 * @param parent 父窗口
 */
GaugeWidget::GaugeWidget(const QString &title, const QString &unit, QWidget *parent)
    : QWidget(parent),
    m_title(title),
    m_unit(unit),
    m_minValue(0.0),
    m_maxValue(100.0),
    m_currentValue(0.0),
    m_arcColor(Qt::green)
{
    setMinimumHeight(120);
}

/**
 * @brief 设置仪表盘数值范围
 * @param min 最小值
 * @param max 最大值
 */
void GaugeWidget::setRange(double min, double max)
{
    m_minValue = min;
    m_maxValue = max;
    update(); // 触发重绘
}

/**
 * @brief 设置当前数值，并根据数值区间动态调整颜色
 * @param value 当前值
 */
void GaugeWidget::setValue(double value)
{
    m_currentValue = qBound(m_minValue, value, m_maxValue);
    // 根据数值改变颜色
    double percentage = (m_currentValue - m_minValue) / (m_maxValue - m_minValue);
    if (percentage < 0.33) m_arcColor = QColor(52, 152, 219); // 蓝色
    else if (percentage < 0.66) m_arcColor = QColor(241, 196, 15); // 黄色
    else m_arcColor = QColor(231, 76, 60); // 红色
    update(); // 触发重绘
}

/**
 * @brief 重绘事件，绘制仪表盘背景、前景、数值、单位和标题
 * @param event 绘图事件
 */
void GaugeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int side = qMin(width(), height());
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制背景弧
    painter.setPen(QPen(QColor(220, 220, 220), 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawArc(-80, -80, 160, 160, -45 * 16, 270 * 16);
    // 绘制前景弧，颜色随数值变化
    double percentage = (m_currentValue - m_minValue) / (m_maxValue - m_minValue);
    int angle = static_cast<int>(percentage * 270.0);
    painter.setPen(QPen(m_arcColor, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawArc(-80, -80, 160, 160, -45 * 16, angle * 16);
    // 绘制中心数值
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPixelSize(36);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRectF(-50, -25, 100, 50), Qt::AlignCenter, QString::number(m_currentValue, 'f', 1));
    // 绘制单位
    font.setPixelSize(14);
    font.setBold(false);
    painter.setFont(font);
    painter.drawText(QRectF(-50, 15, 100, 20), Qt::AlignCenter, m_unit);
    // 绘制标题
    font.setPixelSize(16);
    painter.setFont(font);
    painter.drawText(QRectF(-100, 70, 200, 30), Qt::AlignCenter, m_title);
}

/**
 * @brief 析构函数
 */
GaugeWidget::~GaugeWidget() {}
