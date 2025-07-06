#include <iostream>  
#include <fstream>   
#include <string>    
#include <vector>    
#include <sstream>   

int main() {
    std::string inputFile = "input.csv";
    std::string outputFile = "cleaned_data.csv";

    // ׼�����������ļ���
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "����: �޷��������ļ� " << inputFile << std::endl;
        return 1;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "����: �޷���������ļ� " << outputFile << std::endl;
        inFile.close();
        return 1;
    }

    // 1. д���׼���ɾ���CSVͷ��
    outFile << "id,Temperature,Humidity,Moisture,Soil_Type,Crop_Type,Nitrogen,Potassium,Phosphorous,Fertilizer_Name\n";

    // 2. ����ԭʼ�����ļ��ĵ�һ�У����淶��ͷ����
    std::string headerLine;
    std::getline(inFile, headerLine);

    std::string line;
    int lineCount = 0;

    // 3. ���ж�ȡ�ʹ�������
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
            std::cerr << "����: �и�ʽ����ȷ��������: " << line << std::endl;
            continue;
        }

        // 4. ���Ľ����߼������е��������м�������԰�ȫ�ش�������ո���ֶ� (�� Ground Nut)

        // ����ǰ5���̶��ֶ�
        std::string id = tokens[0];
        std::string temperature = tokens[1];
        std::string humidity = tokens[2];
        std::string moisture = tokens[3];
        std::string soilType = tokens[4];

        // ��ĩβ���������4���̶��ֶ�
        std::string fertilizerName = tokens.back();
        std::string phosphorous = tokens[tokens.size() - 2];
        std::string potassium = tokens[tokens.size() - 3];
        std::string nitrogen = tokens[tokens.size() - 4];

        // �м�ʣ��Ĳ��֣�������һ�����Ƕ�����ʣ������� Crop_Type
        std::string cropType = "";
        for (int i = 5; i < tokens.size() - 4; ++i) {
            cropType += tokens[i] + (i < tokens.size() - 5 ? " " : "");
        }

        // 5. ���ݱ�׼����������֪��OCR����
        if (cropType == "Ground Nu") {
            cropType = "Ground Nut";
        }
        if (cropType == "Oil seeds") {
            cropType = "Oilseed";
        }

        // 6. ����ϴ�������д�����ļ�
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

    std::cout << "������ϴ��ɣ��������� " << lineCount << " �����ݡ�" << std::endl;
    std::cout << "��ϴ��������ѱ��浽 " << outputFile << std::endl;

    return 0;
}