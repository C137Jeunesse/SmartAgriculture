#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <limits>
#include <set>
#include <random> 
#include <chrono> 

// 定义π，用于高斯概率密度函数
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 用于存储单行数据的结构体
struct DataPoint {
    int id;
    int temperature;
    int humidity;
    int moisture;
    std::string soil_type;
    std::string crop_type;
    int nitrogen;
    int potassium;
    int phosphorus;
    std::string fertilizer_name;
};

// 1. 数据加载与异常值检测

// 辅助函数：从字符串中移除多余空格
void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// 从CSV文件加载数据
std::vector<DataPoint> loadData(const std::string& filename) {
    std::vector<DataPoint> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    // 跳过标题行
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        DataPoint dp;

        try {
            // 解析CSV的每一列
            std::getline(ss, field, ','); dp.id = std::stoi(field);
            std::getline(ss, field, ','); dp.temperature = std::stoi(field);
            std::getline(ss, field, ','); dp.humidity = std::stoi(field);
            std::getline(ss, field, ','); dp.moisture = std::stoi(field);

            std::getline(ss, field, ','); trim(field); dp.soil_type = field;

            std::getline(ss, field, ',');
            trim(field);
            // 处理 "Ground Nu" -> "Ground Nut" 的情况
            if (field == "Ground Nu") field = "Ground Nut";
            dp.crop_type = field;

            std::getline(ss, field, ','); dp.nitrogen = std::stoi(field);
            std::getline(ss, field, ','); dp.potassium = std::stoi(field);
            std::getline(ss, field, ','); dp.phosphorus = std::stoi(field);

            std::getline(ss, field, ','); trim(field); dp.fertilizer_name = field;

            data.push_back(dp);
        }
        catch (const std::invalid_argument& e) {
            // std::cerr << "Warning: Skipping malformed line: " << line << std::endl;
        }
    }
    file.close();
    return data;
}

// 异常值检测函数（IQR方法）
std::vector<DataPoint> detectAndHandleAnomalies(const std::vector<DataPoint>& data) {
    std::cout << "Anomaly Detection" << std::endl;
    if (data.empty()) return {};

    std::vector<DataPoint> cleaned_data = data;
    std::set<int> outlier_ids; // 使用set防止重复报告

    // 对每个数值特征进行检测
    std::map<std::string, std::vector<int>> features;
    for (const auto& dp : data) {
        features["Temperature"].push_back(dp.temperature);
        features["Humidity"].push_back(dp.humidity);
        features["Moisture"].push_back(dp.moisture);
        features["Nitrogen"].push_back(dp.nitrogen);
        features["Potassium"].push_back(dp.potassium);
        features["Phosphorus"].push_back(dp.phosphorus);
    }

    for (const auto& pair : features) {
        const std::string& name = pair.first;
        const std::vector<int>& values = pair.second;

        std::vector<int> sorted_values = values;
        std::sort(sorted_values.begin(), sorted_values.end());

        int n = sorted_values.size();
        double q1 = sorted_values[n / 4];
        double q3 = sorted_values[3 * n / 4];
        double iqr = q3 - q1;

        double lower_bound = q1 - 1.5 * iqr;
        double upper_bound = q3 + 1.5 * iqr;

        for (const auto& dp : data) {
            int value;
            if (name == "Temperature") value = dp.temperature;
            else if (name == "Humidity") value = dp.humidity;
            else if (name == "Moisture") value = dp.moisture;
            else if (name == "Nitrogen") value = dp.nitrogen;
            else if (name == "Potassium") value = dp.potassium;
            else if (name == "Phosphorus") value = dp.phosphorus;
            else continue;

            if (value < lower_bound || value > upper_bound) {
                if (outlier_ids.find(dp.id) == outlier_ids.end()) {
                    std::cout << "Anomaly Detected: ID " << dp.id << ", Feature '" << name
                        << "' with value " << value << " is an outlier."
                        << " (Bounds: [" << lower_bound << ", " << upper_bound << "])" << std::endl;
                    outlier_ids.insert(dp.id);
                }
            }
        }
    }

    // 从数据中移除异常值
    cleaned_data.erase(std::remove_if(cleaned_data.begin(), cleaned_data.end(),
        [&outlier_ids](const DataPoint& dp) {
            return outlier_ids.count(dp.id);
        }), cleaned_data.end());

    std::cout << "Original data size: " << data.size() << std::endl;
    std::cout << "Anomalies found and removed: " << outlier_ids.size() << std::endl;
    std::cout << "Cleaned data size: " << cleaned_data.size() << std::endl;
    return cleaned_data;
}




int main() {
    // 1. 加载数据
    std::cout << "Loading data from fertilizer_data.csv..." << std::endl;
    auto all_data = loadData("fertilizer_data.csv");
    if (all_data.empty()) {
        std::cerr << "Failed to load data. Please ensure 'FertilizerData.csv' is in the same directory and has the correct format." << std::endl;
        return 1;
    }
    std::cout << "Data loaded successfully." << std::endl << std::endl;

    // 2. 异常值检测和处理
    auto cleaned_data = detectAndHandleAnomalies(all_data);
    if (cleaned_data.size() < 10) {
        std::cerr << "Not enough data to perform train/test split after anomaly detection." << std::endl;
        return 1;
    }

    return 0;
}