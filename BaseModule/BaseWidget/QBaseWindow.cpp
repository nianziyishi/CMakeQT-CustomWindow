#include "qbasewindow.h"
#include "ui_QBaseWindow.h"
#include <QDesktopWidget>
#include <QStyle>
#include <QCloseEvent>
#include <QTimer>
#include <QDebug>

#include "QBaseConfig.h"
#include "QBaseTitleBar.h"
#include "QBaseMask.h"
#include "QBaseDialog.h"
#include "QStyleHelper.h"

QBaseWindow::QBaseWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mPtr_Titlebar = new QBaseTitleBar(this);
	ui = new Ui::QBaseWindow();
	ui->setupUi(this);

	initWindow();
	QTimer::singleShot(0, this, &QBaseWindow::changeChildWidgetParent);

}

QBaseWindow::~QBaseWindow()
{
	delete ui;
}

void QBaseWindow::initWindow()
{
	/// @brief 初始化窗体

	//窗体关闭后释放内存
	setAttribute(Qt::WA_DeleteOnClose);
	//默认为模态
	setWindowModality(Qt::WindowModality::NonModal);	
	//设置窗体图标
	setWindowIcon(QIcon(QBaseConfig::m_icon_titlebar));
	//设置窗体样式
	setWindowStyle();
	
	//隐藏菜单栏
	ui->menuBar->hide();
	//隐藏状态栏
	ui->statusBar->hide();
	//设置工具栏
	ui->mainToolBar->hide();
	ui->mainToolBar->setMovable(false);
	ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

	//设置窗体边框
	setWindowBorder();

	//缓存基类对象
	foreach (auto var, this->children())
	{
		mList_BaseObject.append(var);
	}
	 
}


void QBaseWindow::showWindow(QWidget* parent)
{
	/// @brief 显示窗体

	auto pDesk = QApplication::desktop();
	this->setParent(parent, this->windowFlags());
	this->move((pDesk->width() - this->width()) / 2, (pDesk->height() - this->height()) / 2);
	this->show();
}

int QBaseWindow::execWindow(QWidget* parent)
{
	/// @brief 事件循环,窗体阻塞

	showWindow(parent);
	return mLoop.exec();
}

void QBaseWindow::hideWindow(int _status)
{
	/// @brief 隐藏窗体

	mLoop.exit(_status);
	this->hide();
}

void QBaseWindow::closeWindow(int _status)
{
	/// @brief 关闭窗体

	mLoop.exit(_status);
	this->close();
}


void QBaseWindow::showEvent(QShowEvent*)
{
	/// @brief 窗体显示事件

	//页面加载完成后，调用子类的初始化数据函数
	if (!mIsAlreadyInitData)
	{
		mIsAlreadyInitData = true;
		QTimer::singleShot(0, this, SLOT(initData()));
	}
}

void QBaseWindow::closeEvent(QCloseEvent* event)
{
	/// @brief 窗体关闭事件

	bool isCanClose = true;
	//如果蒙板正在显示，则不能关闭
	if (mIsMaskShowing)
	{
		isCanClose = false;
	}
	else
	{
		this->handleCloseEvent(isCanClose);
		emit signals_WindowClose(isCanClose);
	}

	if (isCanClose)
	{
		event->accept(); // 接受退出信号，窗体退出
	}
	else
	{
		event->ignore(); // 忽略信号
	}
}

void QBaseWindow::handleCloseEvent(bool& _isClose)
{
	/// @brief 处理窗体关闭事件

}

void QBaseWindow::initData()
{
	/// @brief 初始化数据

}

void QBaseWindow::setWindowButtonType(int _type)
{
	/// @brief 设置标题栏按钮

	mPtr_Titlebar->setWindowButtonType(_type);
}

void QBaseWindow::setToolBarActions(QList<QAction*> _list_action)
{
	/// @brief 设置工具栏actions

	if (_list_action.isEmpty())
	{
		ui->mainToolBar->setHidden(true);
	}
	else
	{
		ui->mainToolBar->setVisible(true);
		ui->mainToolBar->addActions(_list_action);
	}
}

void QBaseWindow::changeChildWidgetParent()
{
	/// @brief 改变子类控件的父对象

	foreach(auto var, this->children())
	{
		if (!mList_BaseObject.contains(var) && var->isWidgetType())
		{
			((QWidget*)var)->setParent(centralWidget());
			((QWidget*)var)->show();//setParent后需要调用重新显示
		}
	}
}

void QBaseWindow::setWindowBorder()
{
	/// @brief 设置窗体边框

	mPtr_Titlebar->setStyleSheet(mPtr_Titlebar->styleSheet() + QString("QToolBar{border: 1px solid #346792;}"));
	QStyleHelper::setWidgetBorderStyle(ui->mainToolBar, "{border: 1px solid #346792;}");
	if (ui->statusBar->isHidden())
	{
		QStyleHelper::setWidgetBorderStyle(ui->centralWidget, "{border: 1px solid #346792;}");
	}
	else
	{
		QStyleHelper::setWidgetBorderStyle(ui->centralWidget,
			"{border-left: 1px solid #346792; border-right: 1px solid #346792;}");
		QStyleHelper::setWidgetBorderStyle(ui->statusBar,
			"{border-left: 1px solid #346792; border-right: 1px solid #346792; border-bottom: 1px solid #346792;}");
	}

}

void QBaseWindow::clearActions()
{
	/// @brief 清除actions

	ui->mainToolBar->clear();
	ui->mainToolBar->setHidden(true);
}

void QBaseWindow::setEnableToolBar(bool isEnabled)
{
	/// @brief 设置启用或禁用工具栏

	ui->mainToolBar->setEnabled(isEnabled);
}

void QBaseWindow::setTitleBarVisible(bool isVisible)
{
	/// @brief 设置显示或隐藏标题栏

	mPtr_Titlebar->setVisible(isVisible);
}


void QBaseWindow::setMenuBarVisible(bool _isVisible)
{
	/// @brief 设置菜单栏是否可见

	ui->menuBar->setVisible(_isVisible);
}

void QBaseWindow::setStatusBarVisible(bool _isVisible)
{
	/// @brief 设置状态栏是否可见

	ui->statusBar->setVisible(_isVisible);
	setWindowBorder();
}

void QBaseWindow::resizeEvent(QResizeEvent* event)
{
	/// @brief 窗体大小改变事件
	if (event->type() == QEvent::Resize)
	{
		if (mIsMaskShowing)
		{
			QBaseMask::ShowBaseMaskWindow(this);
		}
	}
}

bool QBaseWindow::showDialogWindow(QString _text, QString _title, int _buttonType)
{
	/// @brief 显示对话框窗体

	return QBaseDialog::showDialog(this, _text, _title, _buttonType);
}

void QBaseWindow::showMaskWindow(QString text)
{
	/// @brief 显示蒙板窗体

	mIsMaskShowing = true;

	QBaseMask::ShowBaseMaskWindow(this, text);
}

void QBaseWindow::closeMaskWindow()
{
	/// @brief 关闭蒙板

	mIsMaskShowing = false;

	QBaseMask::CloseBaseMaskWindow();
}

void QBaseWindow::setWidgetError(QWidget* widget, QString _errorInfo)
{
	/// @brief 设置控件错误样式

	QStyleHelper::setWidgetError(widget, _errorInfo);
}

void QBaseWindow::clearWidgetError(QWidget* widget)
{
	/// @brief 清除控件错误样式

	QStyleHelper::clearWidgetError(widget);
}

bool QBaseWindow::setWindowStyle(QString style)
{
	/// @brief 设置窗体样式

	return QStyleHelper::setWidgetStyleFile(this, style.isEmpty() ? QStyleHelper::defaultWindowStyle : style);
}