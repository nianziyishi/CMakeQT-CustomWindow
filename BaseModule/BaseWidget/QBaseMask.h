#ifndef QBASEMASK_H
#define QBASEMASK_H

#include <QWidget>

class  QBaseMask : public QWidget
{
public:
	explicit QBaseMask(QWidget* parent);
	~QBaseMask();

	/// @brief 显示窗体蒙板
	static void ShowBaseMaskWindow(QWidget* parent, QString text = "");
	/// @brief 关闭窗体蒙板
	static void CloseBaseMaskWindow();

private:
	/// @brief 创建控件
	static QWidget* CreateWidget(bool _isWindow);

private:
	static QPointer<QWidget> ptr_widget;	
};
#endif // QBASEMASK_H
