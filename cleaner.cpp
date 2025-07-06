#include <iostream>  
#include <fstream>   
#include <string>    
#include <vector>    
#include <sstream>   

int main() {
    std::string inputFile = "input.csv";
    std::string outputFile = "cleaned_data.csv";

    // 准备输入和输出文件流
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "错误: 无法打开输入文件 " << inputFile << std::endl;
        return 1;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "错误: 无法创建输出文件 " << outputFile << std::endl;
        inFile.close();
        return 1;
    }

    // 1. 写入标准、干净的CSV头部
    outFile << "id,Temperature,Humidity,Moisture,Soil_Type,Crop_Type,Nitrogen,Potassium,Phosphorous,Fertilizer_Name\n";

    // 2. 跳过原始数据文件的第一行（不规范的头部）
    std::string headerLine;
    std::getline(inFile, headerLine);

    std::string line;
    int lineCount = 0;

    // 3. 逐行读取和处理数据
    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() < 10) {
            std::cerr << "警告: 行格式不正确，已跳过: " << line << std::endl;
            continue;
        }

        // 4. 核心解析逻辑：从行的两端向中间解析，以安全地处理包含空格的字段 (如 Ground Nut)

        // 解析前5个固定字段
        std::string id = tokens[0];
        std::string temperature = tokens[1];
        std::string humidity = tokens[2];
        std::string moisture = tokens[3];
        std::string soilType = tokens[4];

        // 从末尾反向解析后4个固定字段
        std::string fertilizerName = tokens.back();
        std::string phosphorous = tokens[tokens.size() - 2];
        std::string potassium = tokens[tokens.size() - 3];
        std::string nitrogen = tokens[tokens.size() - 4];

        // 中间剩余的部分，无论是一个还是多个单词，都属于 Crop_Type
        std::string cropType = "";
        for (int i = 5; i < tokens.size() - 4; ++i) {
            cropType += tokens[i] + (i < tokens.size() - 5 ? " " : "");
        }

        // 5. 数据标准化，修正已知的OCR错误
        if (cropType == "Ground Nu") {
            cropType = "Ground Nut";
        }
        if (cropType == "Oil seeds") {
            cropType = "Oilseed";
        }

        // 6. 将清洗后的数据写入新文件
        outFile << id << ","
            << temperature << ","
            << humidity << ","
            << moisture << ","
            << soilType << ","
            << cropType << ","
            << nitrogen << ","
            << potassium << ","
            << phosphorous << ","
            << fertilizerName << "\n";

        lineCount++;
    }

    inFile.close();
    outFile.close();

    std::cout << "数据清洗完成！共处理了 " << lineCount << " 行数据。" << std::endl;
    std::cout << "清洗后的数据已保存到 " << outputFile << std::endl;

    return 0;
}