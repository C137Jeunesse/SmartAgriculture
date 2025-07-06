#include "mainwindow.h"
#include "databasemanager.h"
#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/SA_icon.ico"));
    MainWindow w;
    w.show();

    //程序运行开始，直接初始化数据库
    DataBaseManager::instance().InitDataBase();

    //连接失败，提醒
    if(!DataBaseManager::instance().IsOpen()){
        // 连接数据库失败，弹出错误提示
        QMessageBox::critical(nullptr, "数据库连接失败！", "您联网了吗？您装驱动了吗？\n"
                                                  "请检查数据库连接配置！",
                              QMessageBox::Ok);
    } else {
        qDebug() << "Database connected successfully.";
    }

    return a.exec();
}
