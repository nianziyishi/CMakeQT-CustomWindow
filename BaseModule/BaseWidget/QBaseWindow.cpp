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
	/// @brief ��ʼ������

	//����رպ��ͷ��ڴ�
	setAttribute(Qt::WA_DeleteOnClose);
	//Ĭ��Ϊģ̬
	setWindowModality(Qt::WindowModality::NonModal);	
	//���ô���ͼ��
	setWindowIcon(QIcon(QBaseConfig::m_icon_titlebar));
	//���ô�����ʽ
	setWindowStyle();
	
	//���ز˵���
	ui->menuBar->hide();
	//����״̬��
	ui->statusBar->hide();
	//���ù�����
	ui->mainToolBar->hide();
	ui->mainToolBar->setMovable(false);
	ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

	//���ô���߿�
	setWindowBorder();

	//����������
	foreach (auto var, this->children())
	{
		mList_BaseObject.append(var);
	}
	 
}


void QBaseWindow::showWindow(QWidget* parent)
{
	/// @brief ��ʾ����

	auto pDesk = QApplication::desktop();
	this->setParent(parent, this->windowFlags());
	this->move((pDesk->width() - this->width()) / 2, (pDesk->height() - this->height()) / 2);
	this->show();
}

int QBaseWindow::execWindow(QWidget* parent)
{
	/// @brief �¼�ѭ��,��������

	showWindow(parent);
	return mLoop.exec();
}

void QBaseWindow::hideWindow(int _status)
{
	/// @brief ���ش���

	mLoop.exit(_status);
	this->hide();
}

void QBaseWindow::closeWindow(int _status)
{
	/// @brief �رմ���

	mLoop.exit(_status);
	this->close();
}


void QBaseWindow::showEvent(QShowEvent*)
{
	/// @brief ������ʾ�¼�

	//ҳ�������ɺ󣬵�������ĳ�ʼ�����ݺ���
	if (!mIsAlreadyInitData)
	{
		mIsAlreadyInitData = true;
		QTimer::singleShot(0, this, SLOT(initData()));
	}
}

void QBaseWindow::closeEvent(QCloseEvent* event)
{
	/// @brief ����ر��¼�

	bool isCanClose = true;
	//����ɰ�������ʾ�����ܹر�
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
		event->accept(); // �����˳��źţ������˳�
	}
	else
	{
		event->ignore(); // �����ź�
	}
}

void QBaseWindow::handleCloseEvent(bool& _isClose)
{
	/// @brief ������ر��¼�

}

void QBaseWindow::initData()
{
	/// @brief ��ʼ������

}

void QBaseWindow::setWindowButtonType(int _type)
{
	/// @brief ���ñ�������ť

	mPtr_Titlebar->setWindowButtonType(_type);
}

void QBaseWindow::setToolBarActions(QList<QAction*> _list_action)
{
	/// @brief ���ù�����actions

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
	/// @brief �ı�����ؼ��ĸ�����

	foreach(auto var, this->children())
	{
		if (!mList_BaseObject.contains(var) && var->isWidgetType())
		{
			((QWidget*)var)->setParent(centralWidget());
			((QWidget*)var)->show();//setParent����Ҫ����������ʾ
		}
	}
}

void QBaseWindow::setWindowBorder()
{
	/// @brief ���ô���߿�

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
	/// @brief ���actions

	ui->mainToolBar->clear();
	ui->mainToolBar->setHidden(true);
}

void QBaseWindow::setEnableToolBar(bool isEnabled)
{
	/// @brief �������û���ù�����

	ui->mainToolBar->setEnabled(isEnabled);
}

void QBaseWindow::setTitleBarVisible(bool isVisible)
{
	/// @brief ������ʾ�����ر�����

	mPtr_Titlebar->setVisible(isVisible);
}


void QBaseWindow::setMenuBarVisible(bool _isVisible)
{
	/// @brief ���ò˵����Ƿ�ɼ�

	ui->menuBar->setVisible(_isVisible);
}

void QBaseWindow::setStatusBarVisible(bool _isVisible)
{
	/// @brief ����״̬���Ƿ�ɼ�

	ui->statusBar->setVisible(_isVisible);
	setWindowBorder();
}

void QBaseWindow::resizeEvent(QResizeEvent* event)
{
	/// @brief �����С�ı��¼�
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
	/// @brief ��ʾ�Ի�����

	return QBaseDialog::showDialog(this, _text, _title, _buttonType);
}

void QBaseWindow::showMaskWindow(QString text)
{
	/// @brief ��ʾ�ɰ崰��

	mIsMaskShowing = true;

	QBaseMask::ShowBaseMaskWindow(this, text);
}

void QBaseWindow::closeMaskWindow()
{
	/// @brief �ر��ɰ�

	mIsMaskShowing = false;

	QBaseMask::CloseBaseMaskWindow();
}

void QBaseWindow::setWidgetError(QWidget* widget, QString _errorInfo)
{
	/// @brief ���ÿؼ�������ʽ

	QStyleHelper::setWidgetError(widget, _errorInfo);
}

void QBaseWindow::clearWidgetError(QWidget* widget)
{
	/// @brief ����ؼ�������ʽ

	QStyleHelper::clearWidgetError(widget);
}

bool QBaseWindow::setWindowStyle(QString style)
{
	/// @brief ���ô�����ʽ

	return QStyleHelper::setWidgetStyleFile(this, style.isEmpty() ? QStyleHelper::defaultWindowStyle : style);
}