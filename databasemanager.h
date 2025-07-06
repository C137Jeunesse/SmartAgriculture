// databasemanager.h
// 数据库管理类头文件，负责所有数据库操作的接口定义（用户、农户、专家、作物区、建议、传感器等）
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

/**
 * @brief 数据库管理类（单例）
 * 负责系统所有数据库相关的增删改查操作，包括用户、农户、专家、作物区、建议、传感器等。
 */
class DataBaseManager
{
public:
    /**
     * @brief 构造函数，初始化数据库
     */
    DataBaseManager();
    /**
     * @brief 析构函数，关闭数据库
     */
    ~DataBaseManager();

    /**
     * @brief 初始化数据库连接
     * @return 是否成功
     */
    bool InitDataBase();
    /**
     * @brief 检查数据库是否打开
     * @return 是否已打开
     */
    bool IsOpen() const;

    // 用户相关接口
    int AddUser(const QString& name, const QString& phone, const QString& password, const QString& role); ///< 添加用户，返回用户id
    int AddUser(const QString& name, const QString& phone, const QString& password, const QString& role, QString* errorOut); ///< 添加用户（带错误信息）
    bool UpdateUser(int userId, const QString& name, const QString& phone, const QString& password, const QString& role); ///< 更新用户信息
    bool DeleteUser(int userId); ///< 删除用户
    bool CheckUserLogin(const QString& name, const QString& phone, const QString& password, QString& role); ///< 检查用户登录
    bool IsUserExists(const QString& phone); ///< 检查用户是否存在
    QVariantList GetUserInfo(int userId); ///< 获取指定用户信息
    QVariantList GetAllUsers(); ///< 获取所有用户信息
    int GetUserIdByPhone(const QString& phone); ///< 通过手机号获取用户id
    int GetUserIdByFarmerId(int FarmerId); ///< 通过农户id获取用户id
    int GetUserIdByExpertId(int ExperId); ///< 通过专家id获取用户id

    // 农户相关接口
    int AddFarmerUser(const int userId); ///< 添加农户用户
    bool DeleteFarmerUser(const int farmerId); ///< 删除农户用户
    int GetFarmerId(const int userId); ///< 通过用户id获取农户id

    // 专家相关接口
    bool AddExpertUser(const int userId,const QString& field); ///< 添加专家用户
    bool DeleteExpertUser(const int expertId); ///< 删除专家用户
    int GetExpertId(const int userId); ///< 通过用户id获取专家id
    QString GetExpertField(const int expertId); ///< 获取专家领域
    bool UpdateExpert(int expertId, const QString& field); ///< 更新专家领域

    // 作物区相关接口
    bool AddCropArea(int farmerId, const QString& cropType, float area, const QString& location, const QString& detail); ///< 添加作物区
    bool UpdateCropArea(int cropAreaId, const QString& cropType, float area, const QString& location, const QString& detail); ///< 更新作物区信息
    bool DeleteCropArea(int cropAreaId); ///< 删除作物区
    QVariantList GetCropAreas(int farmerId); ///< 获取指定农户的作物区
    QVariantList GetAllCropAreas(); ///< 获取所有作物区

    // 专家建议相关接口
    bool AddExpertAdvice(int expertId, int cropAreaId, const QString& title, const QString& content, const QString& category); ///< 添加专家建议
    bool UpdateExpertAdvice(int adviceId, const QString& title, const QString& content, const QString& category); ///< 更新专家建议
    bool DeleteExpertAdvice(int adviceId); ///< 删除专家建议
    QVariantList GetExpertAdvices(int cropAreaId); ///< 获取指定作物区的专家建议
    QVariantList GetFarmerExpertAdvices(int farmerId); ///< 获取当前农户所有专家建议
    QVariantList GetAllExpertAdvices(); ///< 获取所有专家建议

    // 模型优化建议相关接口
    bool AddModelOptimization(int userId, int role, const QString& content); ///< 添加模型优化建议
    bool UpdateModelOptimization(int optimizationId, const QString& content); ///< 更新模型优化建议
    bool DeleteModelOptimization(int optimizationId); ///< 删除模型优化建议
    QVariantList GetModelOptimizations(); ///< 获取所有模型优化建议
    QVariantList GetAllModelOptimizations(); ///< 获取所有模型优化建议

    // 传感器相关接口
    QVariantList GetSensorInfo(int sensorId); ///< 获取指定传感器信息
    QVariantList GetAllSensors(); ///< 获取所有传感器信息
    QVariantList GetSAThData(int cropAreaId, const QString& startTime, const QString& endTime); ///< 获取指定作物区、时间段内所有SA_TH数据
    QVariantList GetSASoilData(int cropAreaId, const QString& startTime, const QString& endTime); ///< 获取指定作物区、时间段内所有SA_soil数据
    QVariantMap GetLatestSoilAndThData(int cropAreaId); ///< 获取指定作物区最新一条SA_soil和SA_th数据

    // 查询某专家对某作物区的所有建议
    QVariantList GetExpertAdviceList(int expertId, int cropAreaId);

    // 单例获取接口
    static DataBaseManager& instance(); ///< 获取单例对象

    // 获取上一条错误信息
    QString GetLastError() const;

    // 保证单次操作的原子性
    bool BeginTransaction();
    bool CommitTransaction();
    bool RollbackTransaction();

    // 超时连接检测
    bool TestConnection();

    // 测试函数：测试新增的sensor相关接口
    void TestPrintSensorFunctions(int cropAreaId, const QString& startTime, const QString& endTime);
    void TestPrintAllSensors();

    // 新增：密码哈希工具
    static QString hashPassword(const QString &password);

private:
    QSqlDatabase db; ///< 数据库连接对象

    // 单例相关
    DataBaseManager(const DataBaseManager&) = delete;
    DataBaseManager& operator=(const DataBaseManager&) = delete;
};

#endif // DATABASEMANAGER_H
