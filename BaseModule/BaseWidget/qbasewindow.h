#ifndef QBASEWINDOW_H
#define QBASEWINDOW_H

#include <QMainWindow>
#include <QEventLoop>
#include <QPointer>
#include "../basemodule_global.h"
#include "IQBaseWindow.h"
#include "QBasePara.h"

namespace Ui { class QBaseWindow; };

class QBaseTitleBar;

class BASEMODULE_EXPORT QBaseWindow : public QMainWindow, public IQBaseWindow
{
	Q_OBJECT

public:
	explicit QBaseWindow(QWidget *parent = Q_NULLPTR);
	virtual ~QBaseWindow();

	/// @brief 显示窗体
	void showWindow(QWidget* parent = Q_NULLPTR);

	/// @brief 事件循环,窗体阻塞
	int execWindow(QWidget* parent = Q_NULLPTR);

	/// @brief 隐藏窗体
	void hideWindow(int _status = 0);

	/// @brief 关闭窗体
	void closeWindow(int _status = 0);

	/// @brief 设置启用或禁用工具栏
	void setEnableToolBar(bool _isEnable);

	/// @brief 设置显示或隐藏标题栏
	void setTitleBarVisible(bool _isVisible);

protected:

	/// @brief 处理窗体关闭事件，true关闭, false不关闭
	virtual void handleCloseEvent(bool& _isClose);

	/// @brief 设置标题栏按钮
	/// @param type 按钮类型
	void setWindowButtonType(int _type);

	/// @brief 设置工具栏actions
	void setToolBarActions(QList<QAction*> _list_action);

	/// @brief 清除actions
	void clearActions();

	/// @brief 显示对话框窗体
	bool showDialogWindow(QString _text, QString _title = "", int _buttonType = QBasePara::TypeDialog::OK);

	/// @brief 显示蒙板窗体
	void showMaskWindow(QString text = "");

	/// @brief 关闭蒙板
	void closeMaskWindow();
	
	/// @brief 设置控件错误样式
	void setWidgetError(QWidget* widget, QString _errorInfo);

	/// @brief 清除控件错误样式
	void clearWidgetError(QWidget* widget);

	/// @brief 设置窗体样式
	bool setWindowStyle(QString style = "");

	/// @brief 设置菜单栏是否可见
	void setMenuBarVisible(bool _isVisible);

	/// @brief 设置状态栏是否可见
	void setStatusBarVisible(bool _isVisible);


private:

	/// @brief 初始化窗体
	void initWindow();

	/// @brief 窗体显示事件
	void showEvent(QShowEvent*) override;

	/// @brief 窗体关闭事件
	void closeEvent(QCloseEvent* event) override;

	/// @brief 窗体大小改变事件
	void resizeEvent(QResizeEvent* event) override;

	/// @brief 改变子类控件的父对象
	void changeChildWidgetParent();

	/// @brief 设置窗体边框
	void setWindowBorder();

signals:
	/// @brief 窗体关闭信号
	void signals_WindowClose(bool& _isCanClose);

private slots:
	/// @brief 初始化数据
	virtual void initData();

private:
	Ui::QBaseWindow *ui;
	QPointer<QBaseTitleBar> mPtr_Titlebar;	//标题栏
	QEventLoop mLoop;	//循环事件
	QObjectList mList_BaseObject;	//缓存基类对象
	bool mIsMaskShowing = false;
	bool mIsAlreadyInitData = false;

};
#endif // QBASEWINDOW_H
