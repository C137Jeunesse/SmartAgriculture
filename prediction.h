// prediction.h
// 肥料智能推荐系统核心算法声明头文件，包含数据结构与主要算法接口
#ifndef PREDICTION_H
#define PREDICTION_H

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <iosfwd>
#include <QDebug>
#include <QFileInfo>

namespace FertilizerPrediction {

// ================== 数据结构 ==================
/**
 * @brief 肥料数据点结构体
 * 存储一条环境与作物及施肥数据
 */
struct FertilizerDataPoint {
    double temperature;   ///< 温度
    double humidity;      ///< 空气湿度
    double moisture;      ///< 土壤湿度
    double nitrogen;      ///< 氮含量
    double potassium;     ///< 钾含量
    double phosphorous;   ///< 磷含量
    std::string soilType; ///< 土壤类型
    std::string cropType; ///< 作物类型
    std::string fertilizer;///< 肥料类型（标签）
};

/**
 * @brief 预测结果结构体
 * 存储肥料类型及置信度
 */
struct PredictionResult {
    std::string fertilizer; ///< 肥料类型
    double confidence;      ///< 置信度（0~1）
};

// ================== 类声明 ==================
class FeatureEncoder;
class DecisionTreeClassifier;
class RandomForestClassifier;
class FertilizerPredictionSystem;

// ================== 主要类定义（声明） ==================
/**
 * @brief 特征编码器
 * 负责土壤、作物、肥料类型的字符串与整数编码互转
 */
class FeatureEncoder {
public:
    FeatureEncoder();
    int encodeSoilType(const std::string& type);
    int encodeCropType(const std::string& type);
    int encodeFertilizer(const std::string& type);
    std::string decodeFertilizer(int code) const;
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
private:
    friend class DecisionTreeClassifier;
    std::unordered_map<std::string, int> soilTypeMap; ///< 土壤类型编码表
    std::unordered_map<std::string, int> cropTypeMap; ///< 作物类型编码表
    std::unordered_map<std::string, int> fertilizerMap; ///< 肥料类型编码表
    int nextSoilTypeCode; ///< 下一个土壤类型编码
    int nextCropTypeCode; ///< 下一个作物类型编码
    int nextFertilizerCode; ///< 下一个肥料类型编码
};

/**
 * @brief 决策树分类器
 * 用于单棵树的训练与预测
 */
class DecisionTreeClassifier {
public:
    explicit DecisionTreeClassifier(FeatureEncoder* encoder);
    ~DecisionTreeClassifier();
    DecisionTreeClassifier(DecisionTreeClassifier&& other) noexcept;
    DecisionTreeClassifier& operator=(DecisionTreeClassifier&& other) noexcept;

    void train(const std::vector<FertilizerDataPoint*>& data);
    std::string predict(const FertilizerDataPoint& point) const;
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
private:
    struct DecisionTreeNode; ///< 决策树节点结构体
    FeatureEncoder* encoder; ///< 特征编码器指针
    std::unique_ptr<DecisionTreeNode> root; ///< 树根节点
    int getFeatureValue(const FertilizerDataPoint& point, int featureIndex) const;
    std::string predictRecursive(const DecisionTreeNode* node, const FertilizerDataPoint& point) const;
};

/**
 * @brief 随机森林分类器
 * 由多棵决策树组成，提升预测准确率
 */
class RandomForestClassifier {
public:
    explicit RandomForestClassifier(FeatureEncoder* encoder, int n_trees = 50);
    void train(std::vector<FertilizerDataPoint>& data);
    std::pair<std::vector<PredictionResult>, std::string> predictWithConfidence(const std::string& input);
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
private:
    std::vector<std::unique_ptr<DecisionTreeClassifier>> trees; ///< 决策树集合
    FeatureEncoder* encoder; ///< 特征编码器指针
    int numTrees; ///< 树的数量
};

/**
 * @brief 肥料智能推荐系统
 * 封装数据加载、模型训练、预测、模型保存/加载等功能
 */
class FertilizerPredictionSystem {
public:
    FertilizerPredictionSystem();
    ~FertilizerPredictionSystem();
    bool loadDataFromCSV(const std::string& filename);
    bool trainModel();
    bool isModelReady() const;
    std::pair<std::vector<PredictionResult>, std::string> predict(const std::string& input);
    bool saveModel(const std::string& filename);
    bool loadModel(const std::string& filename);
private:
    FeatureEncoder encoder; ///< 特征编码器
    std::unique_ptr<RandomForestClassifier> model; ///< 随机森林模型
    std::vector<FertilizerDataPoint> trainingData; ///< 训练数据集
    bool isModelTrained; ///< 模型训练状态
};

/**
 * @brief 字符串解析为数据点
 * @param input 输入字符串
 * @return 解析后的数据点
 */
FertilizerDataPoint parseInputString(const std::string& input);

} // namespace
#endif // PREDICTION_H
