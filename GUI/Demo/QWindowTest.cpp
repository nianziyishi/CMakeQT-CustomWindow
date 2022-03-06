#include "QWindowTest.h"
#include "ui_QWindowTest.h"
#include <QDesktopWidget>
#include <QStyle>
#include <QAction>
#include <QDebug>
#include "QBaseDialog.h"

QWindowTest::QWindowTest(QWidget *parent)
	: QBaseWindow(parent)
{
	ui = new Ui::QWindowTest();
	ui->setupUi(this);

	initWindow();
	initWidget();
	qDebug() << "QWindowTest QWindowTest";
}

QWindowTest::~QWindowTest()
{
	qDebug() << "QWindowTest delete";
	delete ui;
}

/// @brief 初始化窗体
void QWindowTest::initWindow()
{
	//设置窗体标题
	setWindowTitle(QStringLiteral("自定义窗体"));
	//设置窗体Icon
	//setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_DesktopIcon));
	//设置窗体大小
	resize(450, 390);
	//设置窗体状态
	//setWindowState(Qt::WindowState::WindowMaximized);
	//设置窗体模态
	//setWindowModality(Qt::WindowModality::NonModal);
	//设置窗体按钮
	//setWindowButtonType(QBasePara::Close | QBasePara::Minimize);
}

void QWindowTest::initWidget()
{
	/// @brief 初始化控件

	addActions();

	setWidgetError(ui->lineEdit, "Text cannot be empty");
	
	setStatusBarVisible(true);

	connect(&timer, &QTimer::timeout, this, &QWindowTest::slots_HanldeTimeout);
	timer.setInterval(3000);

}

/// @brief 初始化数据
void QWindowTest::initData()
{
	qDebug() << "QWindowTest InitData";

	ui->label->setText(QString("QMainWindow:%1\nQWidget:%2").arg(sizeof(QMainWindow)).arg(sizeof(QWidget)));
}

void QWindowTest::handleCloseEvent(bool& _isClose)
{
	/// @brief 处理窗体关闭事件

	qDebug() << "QWindowTest HandleCloseEvent";
	//允许关闭
	_isClose = true;	

	//或者隐藏窗体
	//_isClose = false;	
	//hideWindow(1);
}

void QWindowTest::addActions()
{
	/// @brief 添加action到工具栏

	auto pStyle = QApplication::style();
	QList<QAction*> list_action;

	QAction* action_modify = new QAction(QIcon(pStyle->standardIcon(QStyle::SP_DesktopIcon)), QStringLiteral("显示对话框"), this);
	action_modify->setObjectName("action_modify");
	connect(action_modify, &QAction::triggered, this, &QWindowTest::actionModify_triggered);
	list_action.append(action_modify);
	this->setToolBarActions(list_action);
}

void QWindowTest::actionModify_triggered()
{
	showDialogWindow("this is dialog action");
	//QBaseDialog::showDialog(this, "this is dialog action", "hint");
}

void QWindowTest::on_PB_Dialog1_clicked()
{
	showMaskWindow();
	timer.start();
	//showDialogWindow("this is dialog action", "hint");
	//QBaseDialog::showDialog(this, "this is dialog1", "hint");
}

void QWindowTest::on_PB_Dialog2_clicked()
{
	//showDialogWindow("this is dialog action", "hint");
	QBaseDialog::showDialog(this, "this is dialog2", "hint");
}

void QWindowTest::on_PB_TestWindow_clicked()
{
	QWindowTest* window = new QWindowTest();
	window->showWindow(this);

	qDebug() << "QWindowTest on_PB_TestWindow_clicked";
}

void QWindowTest::slots_HanldeTimeout()
{
	closeMaskWindow();
}
