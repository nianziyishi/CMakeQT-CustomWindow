#include "QBaseTitleBar.h"

#include <QToolButton>
#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>
#include <QStyle>
#include <QPoint>
#include <QLabel>
#include <QIcon>
#include <QApplication>

#include "QBasePara.h"
#include "QBaseConfig.h"

class TitleBarPrivate {
public:
	//const QString icon_min = ":/icon_window_minimize.png";
	//const QString icon_max = ":/icon_window_maximize.png";
	//const QString icon_close = ":/icon_window_close.png";
	//const QString icon_restore = ":/icon_window_restore.png";

	bool mouse_left_pressing = false;	//鼠标左键按下状态记录
	QPoint move_start_point;			//窗口移动时起始位置记录
	QMainWindow* window;				//获取主窗口指针，默认为QMainWindow，如果是QWidget请修改
	QLabel* label_icon;					//窗口图标
	QLabel* label_spacer;				//图标和标题的间隔
	QLabel* label_title;				//窗口标题
	QWidget* widget_placeholder;		//标题中部占位
	QToolButton* toolButton_min;		//最小化
	QToolButton* toolButton_max;		//最大化
	QToolButton* toolButton_close;		//关闭
};

QBaseTitleBar::QBaseTitleBar(QWidget* parent) : QToolBar(parent)
{
	//默认包含三个按钮
	mWindowButtonType = QBasePara::TypeTitleBar::Close | QBasePara::TypeTitleBar::Minimize | QBasePara::TypeTitleBar::Maximize;

	mTitleBar = new TitleBarPrivate();
	mTitleBar->window = (QMainWindow*)window();

	//自定义标题初始化--直接操作主窗口，降低使用复杂性
	mTitleBar->window->setWindowFlags(mTitleBar->window->windowFlags() | Qt::FramelessWindowHint);//主窗口隐藏标题栏
	mTitleBar->window->addToolBar(this);	//把标题栏添加到主窗口
	mTitleBar->window->addToolBarBreak();
	mTitleBar->window->installEventFilter(this);	//事件过滤器
	setMovable(false);

	//左侧显示Icon和标题
	mTitleBar->label_icon = new QLabel(this);
	mTitleBar->label_icon->setFixedSize(QSize(30, 30));	//设置窗体icon大小
	mTitleBar->label_icon->setScaledContents(true);
	mTitleBar->label_icon->setPixmap(mTitleBar->window->windowIcon().pixmap(mTitleBar->label_icon->size()));
	mTitleBar->label_icon->setAttribute(Qt::WA_TranslucentBackground);
	mTitleBar->label_spacer = new QLabel(this);
	mTitleBar->label_spacer->setFixedSize(QSize(5, 32));
	mTitleBar->label_spacer->setAttribute(Qt::WA_TranslucentBackground);
	mTitleBar->label_title = new QLabel(this);
	mTitleBar->label_title->setFont(QFont("SimSun", 12, QFont::Bold));	//设置标题字体
	mTitleBar->label_title->setText(mTitleBar->window->windowTitle());
	mTitleBar->label_title->setAttribute(Qt::WA_TranslucentBackground);
	addWidget(mTitleBar->label_icon);
	addWidget(mTitleBar->label_spacer);
	addWidget(mTitleBar->label_title);

	//中部占位
	mTitleBar->widget_placeholder = new QWidget(this);
	mTitleBar->widget_placeholder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mTitleBar->widget_placeholder->setAttribute(Qt::WA_TranslucentBackground);
	addWidget(mTitleBar->widget_placeholder);

	//右侧显示最小化、最大化、关闭按钮
	mTitleBar->toolButton_min = new QToolButton(this);
	mTitleBar->toolButton_max = new QToolButton(this);
	mTitleBar->toolButton_close = new QToolButton(this);
	mTitleBar->toolButton_min->setIcon(QIcon(QBaseConfig::m_icon_min));
	mTitleBar->toolButton_max->setIcon(QIcon(QBaseConfig::m_icon_max));
	mTitleBar->toolButton_close->setIcon(QIcon(QBaseConfig::m_icon_close));
	addWidget(mTitleBar->toolButton_min);
	addWidget(mTitleBar->toolButton_max);
	addWidget(mTitleBar->toolButton_close);

	connect(mTitleBar->toolButton_min, &QToolButton::clicked, mTitleBar->window, &QMainWindow::showMinimized);
	connect(mTitleBar->toolButton_max, &QToolButton::clicked, this, &QBaseTitleBar::maximizeButtonClicked);
	connect(mTitleBar->toolButton_close, &QToolButton::clicked, mTitleBar->window, &QMainWindow::close);
}

QBaseTitleBar::~QBaseTitleBar()
{
	if (mTitleBar)
	{
		delete mTitleBar;
		mTitleBar = Q_NULLPTR;
	}
}

void QBaseTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		maximizeButtonClicked();
	}
	event->ignore();
	QToolBar::mouseDoubleClickEvent(event);
}

void QBaseTitleBar::mousePressEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		mTitleBar->mouse_left_pressing = true;
		mTitleBar->move_start_point = event->globalPos();
	}
	event->ignore();
	QToolBar::mousePressEvent(event);
}

void QBaseTitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	if (Qt::LeftButton == event->button())
	{
		mTitleBar->mouse_left_pressing = false;
	}
	event->ignore();
	QToolBar::mouseReleaseEvent(event);
}

void QBaseTitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (mTitleBar->mouse_left_pressing)
	{
		//移动窗体位置
		Qt::WindowStates state = mTitleBar->window->windowState();
		QPoint movePoint = event->globalPos() - mTitleBar->move_start_point;
		QPoint widgetPos = mTitleBar->window->pos();
		mTitleBar->move_start_point = event->globalPos();
		mTitleBar->window->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
		mTitleBar->window->setWindowState(state);
	}

	event->ignore();
	QToolBar::mouseMoveEvent(event);
}

bool QBaseTitleBar::eventFilter(QObject* obj, QEvent* event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange: //标题修改
	{
		mTitleBar->label_title->setText(mTitleBar->window->windowTitle());
		return QToolBar::eventFilter(obj, event);
	}
	case QEvent::WindowIconChange: //图标修改
	{
		mTitleBar->label_icon->setPixmap(mTitleBar->window->windowIcon().pixmap(mTitleBar->label_icon->size()));
		return QToolBar::eventFilter(obj, event);
	}
	case QEvent::WindowStateChange:	//窗体状态变化
	{
		Qt::WindowStates state = mTitleBar->window->windowState();
		if (Qt::WindowMaximized == state || Qt::WindowFullScreen == state || (Qt::WindowMaximized | Qt::WindowFullScreen) == state)
		{
			mTitleBar->toolButton_max->setIcon(QIcon(QBaseConfig::m_icon_restore));
		}
		else
		{
			mTitleBar->toolButton_max->setIcon(QIcon(QBaseConfig::m_icon_max));
		}
		return QToolBar::eventFilter(obj, event);
	}
	default:
		return QToolBar::eventFilter(obj, event);
	}
}

void QBaseTitleBar::maximizeButtonClicked()
{
	if (mWindowButtonType & QBasePara::TypeTitleBar::Maximize)
	{
		Qt::WindowStates state = mTitleBar->window->windowState();
		if (Qt::WindowMaximized == state || Qt::WindowFullScreen == state || (Qt::WindowMaximized | Qt::WindowFullScreen) == state)
		{
			mTitleBar->window->setWindowState(Qt::WindowNoState);//将窗体正常显示
		}
		else
		{
			mTitleBar->window->setWindowState(Qt::WindowMaximized);//将窗体最大化
		}
	}
}


void QBaseTitleBar::setWindowButtonType(int _type)
{
	//没有按钮
	if (_type == QBasePara::TypeTitleBar::None_TitleBar)
	{
		mWindowButtonType = _type;
		mTitleBar->toolButton_min->setFixedWidth(0);
		mTitleBar->toolButton_max->setFixedWidth(0);
		mTitleBar->toolButton_close->setFixedWidth(0);
	}
	//只有关闭按钮
	else if (_type == QBasePara::TypeTitleBar::Close)
	{
		mWindowButtonType = _type;
		mTitleBar->toolButton_min->setFixedWidth(0);
		mTitleBar->toolButton_max->setFixedWidth(0);
	}
	//只有关闭、最小化按钮
	else if (_type == (QBasePara::TypeTitleBar::Close | QBasePara::TypeTitleBar::Minimize))
	{
		mWindowButtonType = _type;
		mTitleBar->toolButton_max->setFixedWidth(0);
	}
	//只有关闭、最大化按钮
	else if (_type == (QBasePara::TypeTitleBar::Close | QBasePara::TypeTitleBar::Maximize))
	{
		mWindowButtonType = _type;
		mTitleBar->toolButton_min->setFixedWidth(0);
	}
	//只有关闭、最小化按钮、最大化按钮
	else if (_type == (QBasePara::TypeTitleBar::Close | QBasePara::TypeTitleBar::Minimize | QBasePara::TypeTitleBar::Maximize))
	{
		mWindowButtonType = _type;
	}
}

int QBaseTitleBar::getWindowButtonType()
{
	return mWindowButtonType;
}
