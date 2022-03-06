#ifndef IQBASEWINDOW_H
#define IQBASEWINDOW_H
#include <QObject>

/// @brief 基类窗体接口
class IQBaseWindow
{
public:
    /// @brief 显示窗体
    virtual void showWindow(QWidget* parent = Q_NULLPTR) = 0;

    /// @brief 事件循环,窗体阻塞显示
    virtual int execWindow(QWidget* parent = Q_NULLPTR) = 0;

    /// @brief 析构函数
    virtual ~IQBaseWindow() = default;
};

#endif // IQBASEWINDOW_H
