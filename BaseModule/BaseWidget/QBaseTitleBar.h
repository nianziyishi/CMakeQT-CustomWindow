#ifndef QTBASETITLE_H
#define QTBASETITLE_H

#include <QToolBar>

class TitleBarPrivate;

class QBaseTitleBar : public QToolBar
{
	Q_OBJECT
public:
	explicit QBaseTitleBar(QWidget* parent = Q_NULLPTR);
	~QBaseTitleBar();

	/// @brief 设置窗体按钮
	/// @param type 按钮类型
	void setWindowButtonType(int _type);

	/// @brief 获取窗体按钮类型
	/// @return 按钮类型
	int getWindowButtonType();

protected:

	/// @brief 被双击--标题栏被双击，放大还原
	/// @param event 鼠标双击事件
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	
	/// @brief 鼠标按下--拖拽移动效果
	/// @param event 鼠标按下事件
	virtual void mousePressEvent(QMouseEvent* event);
	
	/// @brief 鼠标抬起--拖拽移动效果
	/// @param event 鼠标释放事件
	virtual void mouseReleaseEvent(QMouseEvent* event);
	
	/// @brief 鼠标移动--拖拽移动效果
	/// @param event 鼠标移动事件
	virtual void mouseMoveEvent(QMouseEvent* event);
	
	/// @brief 事件过滤--修改标题、图标等操作
	/// @param obj 对象
	/// @param event 事件
	/// @return 
	virtual bool eventFilter(QObject* obj, QEvent* event);


private slots:
	
	/// @brief 最大化按钮被点击槽，当前已经最大化则还原，未最大化则最大化，系统还原和最大化分为两个槽不能直接connect
	void maximizeButtonClicked();
signals:
	/// @brief 窗体关闭信号
	void signals_WindowClose1(bool& _isCanClose);
private:
	TitleBarPrivate* mTitleBar;	//组成工具栏的控件类
	int mWindowButtonType;	//使用的按钮类型

};

#endif // QTBASETITLE_H
