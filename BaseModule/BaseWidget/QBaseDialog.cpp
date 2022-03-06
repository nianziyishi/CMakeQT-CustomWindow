#include "QBaseDialog.h"
#include "ui_QBaseDialog.h"
#include "QBaseConfig.h"

//定义一个静态对话框对象是为了重复使用，
//对话框默认为模态，一次只能显示一个对话框，
//所以在点击关闭按钮时，执行的是隐藏窗体
//静态显示的方式QBaseDialog::showDialog(this,"this is dialog","hint");
//对象显示的方式QBaseDialog dialog;dialog.execDialog(this,"this is dialog","hint");

static QPointer<QBaseDialog> ptr_baseDialog = Q_NULLPTR;

QBaseDialog::QBaseDialog(QWidget*parent)
	: QBaseWindow(parent)
{
	ui = new Ui::QBaseDialog();
	ui->setupUi(this);

	initWindow();
}

QBaseDialog::~QBaseDialog()
{
	delete ui;
	ui = Q_NULLPTR;
}

void QBaseDialog::initWindow()
{
	/// @brief 初始化窗体

	//设置窗体大小
	resize(400, 270);
	//设置窗体阻塞所有窗体
	setWindowModality(Qt::WindowModality::ApplicationModal);
	//设置窗体为对话框类型
	//setWindowFlags(windowFlags() | Qt::Dialog);
	//设置窗体标题栏为没有按钮
	setWindowButtonType(QBasePara::TypeDialog::None_Dialog);
	//设置窗体关闭后是否释放内存
	setAttribute(Qt::WA_DeleteOnClose, false);
}

void QBaseDialog::setDialogInfo(QString _text, QString _title, int _buttonType)
{
	/// @brief 设置对话框信息

	this->setWindowTitle(_title);
	ui->TE_Text->setText(_text);
	ui->LE_Icon->setPixmap(QIcon(QBaseConfig::m_icon_hint).pixmap(ui->LE_Icon->size()));

	if ((QBasePara::TypeDialog::OK | QBasePara::TypeDialog::Cancel) == _buttonType)
	{
		ui->PB_OK->setVisible(true);
		ui->PB_Cancel->setVisible(true);
	}
	else
	{
		ui->PB_OK->setVisible(true);
		ui->PB_Cancel->setVisible(false);
	}

}

void QBaseDialog::closeDialog(int status)
{
	/// @brief 关闭对话框窗体
	
	mLoop.exit(status);

	if (mIsStatic)
	{
		//窗体关闭时只隐藏窗体
		this->hideWindow(status);
	}
	else
	{
		this->closeWindow(status);
	}
}

bool QBaseDialog::execDialog(QWidget* parent, QString _text, QString _title, int _buttonType)
{
	/// @brief 事件循环,窗体阻塞

	setDialogInfo(_text, _title.isEmpty() ? QBaseConfig::m_dialog_hint : _title, _buttonType);
	showWindow(parent);
	return mLoop.exec();
}

bool QBaseDialog::showDialog(QWidget* parent, QString _text, QString _title, int _buttonType)
{
	/// @brief 使用全局静态对象显示对话框，title为空时默认显示“提示”

	if (!ptr_baseDialog)
	{
		ptr_baseDialog = new QBaseDialog();
		ptr_baseDialog->setIsStaticShow();
	}

	return ptr_baseDialog->execDialog(parent, _text, _title, _buttonType);
}

void QBaseDialog::setIsStaticShow()
{
	/// @brief 设置是以静态方式显示对话框

	mIsStatic = true;
}

void QBaseDialog::on_PB_OK_clicked()
{
	/// @brief 确定按钮

	closeDialog(1);
}

void QBaseDialog::on_PB_Cancel_clicked()
{
	/// @brief 取消按钮

	closeDialog(0);
}
