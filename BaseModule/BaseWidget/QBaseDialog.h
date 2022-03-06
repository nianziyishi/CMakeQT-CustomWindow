#ifndef QBASEDIALOG_H
#define QBASEDIALOG_H

#include <QBaseWindow>
#include <QEventLoop>
#include <QPointer>

#include "../basemodule_global.h"
#include "QBasePara.h"

namespace Ui { class QBaseDialog; };

class QBaseWindow;

class BASEMODULE_EXPORT QBaseDialog : public QBaseWindow
{
	Q_OBJECT

public:
	explicit QBaseDialog(QWidget* parent = Q_NULLPTR);
	~QBaseDialog();

	/// @brief 使用全局静态对象显示对话框，title为空时默认显示“提示”
	static bool showDialog(QWidget* parent, QString _text, QString _title = "", int _buttonType = QBasePara::TypeDialog::OK);

	/// @brief 定义对象显示对话框，事件循环,窗体阻塞
	bool execDialog(QWidget* parent, QString _text, QString _title = "", int _buttonType = QBasePara::TypeDialog::OK);

	/// @brief 设置是以静态方式显示对话框
	void setIsStaticShow();

private:

	/// @brief 初始化窗体
	void initWindow();

	/// @brief 设置对话框信息
	void setDialogInfo(QString _text, QString _title, int _buttonType);

	/// @brief 关闭对话框窗体
	void closeDialog(int _status = 0);

private slots:

	/// @brief 确定按钮
	void on_PB_OK_clicked();

	/// @brief 取消按钮
	void on_PB_Cancel_clicked();

private:
	Ui::QBaseDialog* ui;
	QEventLoop mLoop;	//循环事件
	bool mIsStatic = false;	//是否是使用静态对象显示对话框
};
#endif // QBASEDIALOG_H
