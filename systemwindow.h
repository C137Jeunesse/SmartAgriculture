// systemwindow.h
// 系统分析窗口类头文件，负责数据可视化、智能建议、仪表盘、导出等功能
#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <memory>
#include <vector>
#include "prediction.h"

QT_BEGIN_NAMESPACE
class QAction;
class QSplitter;
class QComboBox;
class QDateTimeEdit;
class QPushButton;
class QCheckBox;
class QSpinBox;
class QWidget;
class QLabel;
class QTimer;
class QTextEdit;
class QChartView;
class QChart;
class QLineSeries;
class QDateTimeAxis;
class QValueAxis;
class QPieSeries;
QT_END_NAMESPACE

class SystemSuggestionDialog;
class GaugeWidget;

/**
 * @brief 系统分析窗口类
 * 负责数据可视化、智能建议、仪表盘、导出等功能。
 */
class SystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param userCropIds 当前用户可访问的作物区ID列表
     * @param parent 父窗口指针
     */
    explicit SystemWindow(const std::vector<int>& userCropIds, QWidget *parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~SystemWindow();

    /**
     * @brief 初始化窗口，加载UI、数据库、模型等
     * @return 是否初始化成功
     */
    bool initialize();
    /**
     * @brief 刷新智能建议对话框内容
     * @param dialog 智能建议对话框指针
     */
    void refreshSuggestion(SystemSuggestionDialog* dialog);

private slots:
    /**
     * @brief 加载数据按钮点击槽
     */
    void onLoadDataClicked();
    /**
     * @brief 刷新按钮点击槽
     */
    void onRefreshClicked();
    /**
     * @brief 系统建议按钮点击槽
     */
    void onSystemSuggestionClicked();
    /**
     * @brief 重新训练模型按钮点击槽
     * @param isFirstRun 是否首次运行
     */
    void onRetrainModelClicked(bool isFirstRun = false);
    /**
     * @brief 导出数据按钮点击槽
     */
    void onExportDataClicked();
    /**
     * @brief 导出图片按钮点击槽
     */
    void onExportImageClicked();
    /**
     * @brief 关于按钮点击槽
     */
    void showAboutDialog();
    /**
     * @brief 折线图悬停事件槽
     * @param point 当前点
     * @param state 是否悬停
     */
    void onSeriesHovered(const QPointF &point, bool state);
    /**
     * @brief 自动刷新开关槽
     * @param enabled 是否启用
     */
    void onAutoRefreshToggled(bool enabled);
    /**
     * @brief 定时自动刷新数据槽
     */
    void updateDataAuto();
    /**
     * @brief 定时刷新仪表盘槽
     */
    void updateDashboard();
    /**
     * @brief 开始时间变化槽
     * @param dateTime 新的开始时间
     */
    void onStartTimeChanged(const QDateTime &dateTime);
    /**
     * @brief 结束时间变化槽
     * @param dateTime 新的结束时间
     */
    void onEndTimeChanged(const QDateTime &dateTime);

private:
    void initStyleSheet(); ///< 初始化样式表
    void initMenu(); ///< 初始化菜单栏
    bool initDatabase(); ///< 初始化数据库
    void initUI(); ///< 初始化UI布局
    void initChart(); ///< 初始化图表
    void setupConnections(); ///< 连接信号槽
    void populateCropAreaCombo(); ///< 填充作物区下拉框
    void loadAndDisplayData(); ///< 加载并显示数据（无参，默认用控件值）
    void loadAndDisplayData(const QDateTime &start, const QDateTime &end); ///< 加载并显示数据（指定时间区间）
    QString getCurrentEnvironmentData(); ///< 获取当前环境数据字符串
    void updatePieChart(int cropAreaId, const QDateTime &startTime, const QDateTime &endTime); ///< 更新饼图
    void initFertilizerPredictionSystem(); ///< 初始化肥料预测系统
    QString translateCropType(const QString& chineseCropType); ///< 作物类型中英文转换

    std::vector<int> m_userCropIds; ///< 当前用户可访问的作物区ID列表

    // --- UI 组件 ---
    QAction *m_retrainAction, *m_exportCsvAction, *m_exportImageAction, *m_aboutAction;
    QWidget *m_centralWidget;
    QSplitter *m_mainSplitter, *m_chartSplitter;
    GaugeWidget *m_tempGauge, *m_humidityGauge;
    QComboBox *m_cropAreaCombo, *m_dataTypeCombo;
    QDateTimeEdit *m_startTimeEdit, *m_endTimeEdit;
    QPushButton *m_loadButton, *m_systemSuggestionButton;
    QCheckBox *m_autoRefreshCheckBox;
    QSpinBox *m_refreshIntervalSpinBox;
    QLabel *m_chartTooltip;
    QChartView *m_chartView, *m_pieChartView;
    QChart *m_chart, *m_pieChart;
    QLineSeries *m_series;
    QPieSeries *m_pieSeries;
    QDateTimeAxis *m_axisX;
    QValueAxis *m_axisY;

    // --- 后端组件 ---
    QTimer *m_autoRefreshTimer, *m_dashboardUpdateTimer;
    std::unique_ptr<FertilizerPrediction::FertilizerPredictionSystem> m_predictionSystem;
    bool m_predictionSystemReady;
    QTimer *m_timeUpdateTimer; // 实时时间定时器

protected:
    /**
     * @brief 窗口关闭事件，发送关闭信号
     * @param event 关闭事件指针
     */
    void closeEvent(QCloseEvent *event) override;

signals:
    /**
     * @brief 窗口关闭信号
     */
    void closeSignal();
};

/**
 * @brief 系统智能建议对话框类
 * 展示智能施肥和灌溉建议。
 */
class SystemSuggestionDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param mainWindow 父窗口指针
     * @param parent 父窗口
     */
    explicit SystemSuggestionDialog(SystemWindow* mainWindow, QWidget *parent = nullptr);
    /**
     * @brief 设置建议内容
     * @param results 预测结果
     * @param wateringTip 灌溉建议
     */
    void setSuggestionData(const std::vector<FertilizerPrediction::PredictionResult> &results, const QString &wateringTip);
signals:
    /**
     * @brief 请求刷新建议信号
     * @param dialog 当前对话框指针
     */
    void refreshRequested(SystemSuggestionDialog* dialog);
private:
    QTextEdit *m_contentTextEdit; ///< 建议内容显示控件
    void setupUI(); ///< 初始化UI
};

#endif // SYSTEMWINDOW_H
