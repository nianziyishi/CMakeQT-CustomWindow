#ifndef IQBASEWINDOW_H
#define IQBASEWINDOW_H
#include <QObject>

/// @brief ���ര��ӿ�
class IQBaseWindow
{
public:
    /// @brief ��ʾ����
    virtual void showWindow(QWidget* parent = Q_NULLPTR) = 0;

    /// @brief �¼�ѭ��,����������ʾ
    virtual int execWindow(QWidget* parent = Q_NULLPTR) = 0;

    /// @brief ��������
    virtual ~IQBaseWindow() = default;
};

#endif // IQBASEWINDOW_H
