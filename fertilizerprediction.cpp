// fertilizerprediction.cpp
// 肥料智能推荐系统核心算法实现文件，包含特征编码、决策树、随机森林、系统封装等实现
#include "prediction.h"
#include <random>
#include <cmath>
#include <numeric>
#include <sstream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace FertilizerPrediction {

// ================== FeatureEncoder 实现 ==================
/**
 * @brief 构造函数，初始化编码器
 */
FeatureEncoder::FeatureEncoder() : nextSoilTypeCode(0), nextCropTypeCode(0), nextFertilizerCode(0) {}

/**
 * @brief 编码土壤类型字符串为整数
 * @param type 土壤类型
 * @return 整数编码
 */
int FeatureEncoder::encodeSoilType(const std::string& type) {
    if (soilTypeMap.find(type) == soilTypeMap.end()) soilTypeMap[type] = nextSoilTypeCode++;
    return soilTypeMap.at(type);
}
/**
 * @brief 编码作物类型字符串为整数
 * @param type 作物类型
 * @return 整数编码
 */
int FeatureEncoder::encodeCropType(const std::string& type) {
    if (cropTypeMap.find(type) == cropTypeMap.end()) cropTypeMap[type] = nextCropTypeCode++;
    return cropTypeMap.at(type);
}
/**
 * @brief 编码肥料类型字符串为整数
 * @param type 肥料类型
 * @return 整数编码
 */
int FeatureEncoder::encodeFertilizer(const std::string& type) {
    if (fertilizerMap.find(type) == fertilizerMap.end()) fertilizerMap[type] = nextFertilizerCode++;
    return fertilizerMap.at(type);
}
/**
 * @brief 解码肥料类型整数为字符串
 * @param code 整数编码
 * @return 肥料类型字符串
 */
std::string FeatureEncoder::decodeFertilizer(int code) const {
    for (const auto& pair : fertilizerMap) if (pair.second == code) return pair.first;
    return "Unknown";
}
/**
 * @brief 序列化编码器到输出流
 * @param os 输出流
 */
void FeatureEncoder::serialize(std::ostream& os) const {
    auto write_map = [&](const std::unordered_map<std::string, int>& map) {
        uint32_t size = map.size();
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& pair : map) {
            uint32_t len = pair.first.length();
            os.write(reinterpret_cast<const char*>(&len), sizeof(len));
            os.write(pair.first.c_str(), len);
            os.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
        }
    };
    write_map(soilTypeMap); write_map(cropTypeMap); write_map(fertilizerMap);
    os.write(reinterpret_cast<const char*>(&nextSoilTypeCode), sizeof(nextSoilTypeCode));
    os.write(reinterpret_cast<const char*>(&nextCropTypeCode), sizeof(nextCropTypeCode));
    os.write(reinterpret_cast<const char*>(&nextFertilizerCode), sizeof(nextFertilizerCode));
}
/**
 * @brief 从输入流反序列化编码器
 * @param is 输入流
 */
void FeatureEncoder::deserialize(std::istream& is) {
    auto read_map = [&](std::unordered_map<std::string, int>& map) {
        uint32_t size; is.read(reinterpret_cast<char*>(&size), sizeof(size)); map.clear();
        for (uint32_t i = 0; i < size; ++i) {
            uint32_t len; is.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string key(len, '\0'); is.read(&key[0], len);
            int value; is.read(reinterpret_cast<char*>(&value), sizeof(value));
            map[key] = value;
        }
    };
    read_map(soilTypeMap); read_map(cropTypeMap); read_map(fertilizerMap);
    is.read(reinterpret_cast<char*>(&nextSoilTypeCode), sizeof(nextSoilTypeCode));
    is.read(reinterpret_cast<char*>(&nextCropTypeCode), sizeof(nextCropTypeCode));
    is.read(reinterpret_cast<char*>(&nextFertilizerCode), sizeof(nextFertilizerCode));
}

// ================== DecisionTreeClassifier 实现 ==================
struct DecisionTreeClassifier::DecisionTreeNode {
    int featureIndex = -1; ///< 特征索引
    int splitValue = -1;   ///< 分裂值
    std::string classLabel;///< 叶节点类别
    bool isLeaf = false;   ///< 是否为叶节点
    std::unique_ptr<DecisionTreeNode> left, right; ///< 左右子树
};

// 构造/析构/移动构造
DecisionTreeClassifier::DecisionTreeClassifier(FeatureEncoder* enc) : encoder(enc) {}
DecisionTreeClassifier::~DecisionTreeClassifier() = default;
DecisionTreeClassifier::DecisionTreeClassifier(DecisionTreeClassifier&& other) noexcept = default;
DecisionTreeClassifier& DecisionTreeClassifier::operator=(DecisionTreeClassifier&& other) noexcept = default;

namespace {
/**
 * @brief 连续特征离散化
 * @param value 连续值
 * @param bins 分箱边界
 * @return 离散化结果
 */
int discretize(double value, const std::vector<double>& bins) {
    return std::distance(bins.begin(), std::upper_bound(bins.begin(), bins.end(), value));
}
/**
 * @brief 计算Gini系数
 * @param data 数据集
 * @return Gini值
 */
double calculateGini(const std::vector<FertilizerDataPoint*>& data) {
    if (data.empty()) return 0.0;
    std::unordered_map<std::string, int> counts;
    for (const auto* p : data) counts[p->fertilizer]++;
    double impurity = 1.0;
    for (const auto& pair : counts) {
        double prob = static_cast<double>(pair.second) / data.size();
        impurity -= prob * prob;
    }
    return impurity;
}
/**
 * @brief 获取多数类别
 * @param data 数据集
 * @return 多数类别字符串
 */
std::string getMajorityClass(const std::vector<FertilizerDataPoint*>& data) {
    if (data.empty()) return "Unknown";
    std::unordered_map<std::string, int> counts;
    for (const auto* p : data) counts[p->fertilizer]++;
    return std::max_element(counts.begin(), counts.end(),
                            [](const auto& a, const auto& b){ return a.second < b.second; })->first;
}
}

/**
 * @brief 获取数据点的特征值（离散化/编码）
 * @param p 数据点
 * @param idx 特征索引
 * @return 整数特征值
 */
int DecisionTreeClassifier::getFeatureValue(const FertilizerDataPoint& p, int idx) const {
    static const std::vector<double> tempBins = {25, 30, 35};
    static const std::vector<double> humBins = {50, 65, 80};
    static const std::vector<double> moistBins = {30, 50, 70};
    static const std::vector<double> nutrientBins = {15, 30, 45};
    switch (idx) {
    case 0: return discretize(p.temperature, tempBins);
    case 1: return discretize(p.humidity, humBins);
    case 2: return discretize(p.moisture, moistBins);
    case 3: return encoder->encodeSoilType(p.soilType);
    case 4: return encoder->encodeCropType(p.cropType);
    case 5: return discretize(p.nitrogen, nutrientBins);
    case 6: return discretize(p.potassium, nutrientBins);
    case 7: return discretize(p.phosphorous, nutrientBins);
    default: return 0;
    }
}

/**
 * @brief 训练决策树
 * @param data 训练数据指针集合
 */
void DecisionTreeClassifier::train(const std::vector<FertilizerDataPoint*>& data) {
    if (data.empty()) return;
    std::function<std::unique_ptr<DecisionTreeNode>(std::vector<FertilizerDataPoint*>, int)> build =
        [&](std::vector<FertilizerDataPoint*> current_data, int depth) -> std::unique_ptr<DecisionTreeNode> {
        const int numFeatures = 8, minSamplesSplit = 5, maxDepth = 10;
        const int featuresToConsider = static_cast<int>(sqrt(numFeatures)) + 1;
        std::string majorityClass = getMajorityClass(current_data);
        auto node = std::make_unique<DecisionTreeNode>();
        if (depth >= maxDepth || current_data.size() < minSamplesSplit || calculateGini(current_data) < 1e-6) {
            node->isLeaf = true; node->classLabel = majorityClass; return node;
        }
        double bestGain = -1.0;
        int bestFeature = -1, bestValue = -1;
        std::vector<int> feature_indices(numFeatures);
        std::iota(feature_indices.begin(), feature_indices.end(), 0);
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(feature_indices.begin(), feature_indices.end(), rng);
        double parentGini = calculateGini(current_data);
        for (int i = 0; i < featuresToConsider; ++i) {
            int feature = feature_indices[i];
            std::unordered_set<int> unique_values;
            for(const auto* p : current_data) unique_values.insert(getFeatureValue(*p, feature));
            for (int val : unique_values) {
                std::vector<FertilizerDataPoint*> left, right;
                for (auto* p : current_data) (getFeatureValue(*p, feature) == val ? left : right).push_back(p);
                if (left.empty() || right.empty()) continue;
                double p_left = static_cast<double>(left.size())/current_data.size();
                double gain = parentGini - (p_left * calculateGini(left)) - ((1 - p_left) * calculateGini(right));
                if (gain > bestGain) { bestGain = gain; bestFeature = feature; bestValue = val; }
            }
        }
        if (bestGain <= 0) { node->isLeaf = true; node->classLabel = majorityClass; return node; }
        node->featureIndex = bestFeature; node->splitValue = bestValue;
        std::vector<FertilizerDataPoint*> left_data, right_data;
        for (auto* p : current_data) (getFeatureValue(*p, node->featureIndex) == node->splitValue ? left_data : right_data).push_back(p);
        node->left = build(left_data, depth + 1);
        node->right = build(right_data, depth + 1);
        return node;
    };
    root = build(data, 0);
}

/**
 * @brief 预测单个数据点的类别
 * @param point 数据点
 * @return 预测类别字符串
 */
std::string DecisionTreeClassifier::predict(const FertilizerDataPoint& point) const {
    if (!root) return "Unknown";
    return predictRecursive(root.get(), point);
}
/**
 * @brief 递归预测辅助函数
 * @param node 当前节点
 * @param point 数据点
 * @return 预测类别
 */
std::string DecisionTreeClassifier::predictRecursive(const DecisionTreeNode* node, const FertilizerDataPoint& point) const {
    if (!node) return "Unknown";
    if (node->isLeaf) return node->classLabel;
    int val = getFeatureValue(point, node->featureIndex);
    auto next_node = (val == node->splitValue) ? node->left.get() : node->right.get();
    return next_node ? predictRecursive(next_node, point) : node->classLabel;
}
/**
 * @brief 序列化决策树到输出流
 * @param os 输出流
 */
void DecisionTreeClassifier::serialize(std::ostream& os) const {
    std::function<void(const DecisionTreeNode*)> write =
        [&](const DecisionTreeNode* node) {
            bool is_null = !node;
            os.write(reinterpret_cast<const char*>(&is_null), sizeof(is_null));
            if (is_null) return;
            os.write(reinterpret_cast<const char*>(&node->isLeaf), sizeof(node->isLeaf));
            if (node->isLeaf) {
                uint32_t len = node->classLabel.size();
                os.write(reinterpret_cast<const char*>(&len), sizeof(len));
                os.write(node->classLabel.c_str(), len);
            } else {
                os.write(reinterpret_cast<const char*>(&node->featureIndex), sizeof(node->featureIndex));
                os.write(reinterpret_cast<const char*>(&node->splitValue), sizeof(node->splitValue));
                write(node->left.get());
                write(node->right.get());
            }
        };
    write(root.get());
}
/**
 * @brief 从输入流反序列化决策树
 * @param is 输入流
 */
void DecisionTreeClassifier::deserialize(std::istream& is) {
    std::function<std::unique_ptr<DecisionTreeNode>()> read =
        [&]() -> std::unique_ptr<DecisionTreeNode> {
        bool is_null; is.read(reinterpret_cast<char*>(&is_null), sizeof(is_null));
        if(is.fail() || is_null) return nullptr;
        auto node = std::make_unique<DecisionTreeNode>();
        is.read(reinterpret_cast<char*>(&node->isLeaf), sizeof(node->isLeaf));
        if (node->isLeaf) {
            uint32_t len; is.read(reinterpret_cast<char*>(&len), sizeof(len));
            node->classLabel.resize(len); is.read(&node->classLabel[0], len);
        } else {
            is.read(reinterpret_cast<char*>(&node->featureIndex), sizeof(node->featureIndex));
            is.read(reinterpret_cast<char*>(&node->splitValue), sizeof(node->splitValue));
            node->left = read();
            node->right = read();
        }
        return node;
    };
    root = read();
}

// ================== RandomForestClassifier 实现 ==================
/**
 * @brief 构造函数，初始化森林参数
 * @param enc 特征编码器
 * @param n_trees 树的数量
 */
RandomForestClassifier::RandomForestClassifier(FeatureEncoder* enc, int n_trees)
    : encoder(enc), numTrees(n_trees) {}

/**
 * @brief 训练随机森林
 * @param data 训练数据集
 */
void RandomForestClassifier::train(std::vector<FertilizerDataPoint>& data) {
    if (data.empty()) return;
    trees.clear();
    trees.reserve(numTrees);
    std::vector<FertilizerDataPoint*> data_ptrs;
    data_ptrs.reserve(data.size());
    for(auto& d : data) {
        data_ptrs.push_back(&d);
    }
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, data.size() - 1);
    std::vector<FertilizerDataPoint*> sample_ptrs;
    sample_ptrs.reserve(data.size());
    for (int i = 0; i < numTrees; ++i) {
        sample_ptrs.clear();
        for (size_t j = 0; j < data.size(); ++j) {
            sample_ptrs.push_back(data_ptrs[dist(rng)]);
        }
        trees.push_back(std::make_unique<DecisionTreeClassifier>(encoder));
        trees.back()->train(sample_ptrs);
    }
}

/**
 * @brief 随机森林预测，返回置信度排序的前3个结果及灌溉建议
 * @param input 输入字符串
 * @return 预测结果及建议
 */
std::pair<std::vector<PredictionResult>, std::string> RandomForestClassifier::predictWithConfidence(const std::string& input) {
    if (trees.empty()) return {};
    FertilizerDataPoint point = parseInputString(input);
    std::unordered_map<std::string, int> votes;
    for (const auto& tree : trees) {
        votes[tree->predict(point)]++;
    }
    std::vector<PredictionResult> results;
    for(const auto& v : votes) {
        results.push_back({v.first, static_cast<double>(v.second) / trees.size()});
    }
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b){ return a.confidence > b.confidence; });
    if (results.size() > 3) {
        results.resize(3);
    }
    std::string tip = (point.moisture < 40&&point.humidity<80) ? "土壤湿度和空气湿度较低，建议及时浇水！" : "土壤湿度和空气湿度适中，暂无需浇水。";
    return {results, tip};
}
/**
 * @brief 序列化森林到输出流
 * @param os 输出流
 */
void RandomForestClassifier::serialize(std::ostream& os) const {
    uint32_t tree_count = trees.size();
    os.write(reinterpret_cast<const char*>(&tree_count), sizeof(tree_count));
    for(const auto& tree : trees) {
        tree->serialize(os);
    }
}
/**
 * @brief 从输入流反序列化森林
 * @param is 输入流
 */
void RandomForestClassifier::deserialize(std::istream& is) {
    uint32_t tree_count;
    is.read(reinterpret_cast<char*>(&tree_count), sizeof(tree_count));
    trees.clear();
    trees.reserve(tree_count);
    for (size_t i = 0; i < tree_count; ++i) {
        auto tree = std::make_unique<DecisionTreeClassifier>(encoder);
        tree->deserialize(is);
        trees.push_back(std::move(tree));
    }
}

// ================== FertilizerPredictionSystem 实现 ==================
/**
 * @brief 构造函数，初始化系统
 */
FertilizerPredictionSystem::FertilizerPredictionSystem()
    : model(std::make_unique<RandomForestClassifier>(&encoder)), isModelTrained(false) {}

/**
 * @brief 析构函数
 */
FertilizerPredictionSystem::~FertilizerPredictionSystem() = default;

/**
 * @brief 从CSV文件加载训练数据
 * @param filename 文件名
 * @return 是否加载成功
 */
bool FertilizerPredictionSystem::loadDataFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        qCritical() << "无法打开CSV文件:" << QString::fromStdString(filename);
        return false;
    }
    trainingData.clear();
    std::string line;
    std::getline(file, line); // 跳过表头
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while(std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 10) {
            try {
                FertilizerDataPoint p;
                p.temperature = std::stod(tokens[1]);
                p.humidity = std::stod(tokens[2]);
                p.moisture = std::stod(tokens[3]);
                p.soilType = tokens[4];
                p.cropType = tokens[5];
                p.nitrogen = std::stod(tokens[6]);
                p.potassium = std::stod(tokens[7]);
                p.phosphorous = std::stod(tokens[8]);
                p.fertilizer = tokens[9];
                trainingData.push_back(p);
            } catch(...) {
                continue;
            }
        }
    }
    qDebug() << "从" << QString::fromStdString(filename) << "成功加载" << trainingData.size() << "条数据";
    return !trainingData.empty();
}

/**
 * @brief 训练模型
 * @return 是否训练成功
 */
bool FertilizerPredictionSystem::trainModel() {
    if (trainingData.empty()) { qCritical("训练数据为空，无法训练模型。"); return false; }
    for (const auto& p : trainingData) {
        encoder.encodeSoilType(p.soilType);
        encoder.encodeCropType(p.cropType);
        encoder.encodeFertilizer(p.fertilizer);
    }
    qDebug() << "开始训练模型，使用" << trainingData.size() << "条数据...";
    model->train(trainingData);
    isModelTrained = true;
    qDebug() << "模型训练完成！";
    return true;
}

/**
 * @brief 判断模型是否已训练
 * @return 是否已训练
 */
bool FertilizerPredictionSystem::isModelReady() const { return isModelTrained; }

/**
 * @brief 预测接口，返回肥料推荐及灌溉建议
 * @param input 输入字符串
 * @return 预测结果及建议
 */
std::pair<std::vector<PredictionResult>, std::string> FertilizerPredictionSystem::predict(const std::string& input) {
    if (!isModelTrained) { qWarning("模型尚未训练，无法预测。"); return {}; }
    return model->predictWithConfidence(input);
}

/**
 * @brief 保存模型到文件
 * @param filename 文件名
 * @return 是否保存成功
 */
bool FertilizerPredictionSystem::saveModel(const std::string& filename) {
    if (!isModelTrained) return false;
    std::ofstream file(filename, std::ios::binary);
    if(!file) return false;
    encoder.serialize(file);
    model->serialize(file);
    return true;
}

/**
 * @brief 从文件加载模型
 * @param filename 文件名
 * @return 是否加载成功
 */
bool FertilizerPredictionSystem::loadModel(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if(!file) return false;
    encoder.deserialize(file);
    model->deserialize(file);
    isModelTrained = true;
    return true;
}

/**
 * @brief 字符串解析为数据点
 * @param input 输入字符串
 * @return 解析后的数据点
 */
FertilizerDataPoint parseInputString(const std::string& input) {
    FertilizerDataPoint p;
    std::stringstream ss(input);
    ss >> p.temperature >> p.humidity >> p.moisture >> p.soilType >> p.cropType
        >> p.nitrogen >> p.potassium >> p.phosphorous;
    return p;
}

} // namespace
