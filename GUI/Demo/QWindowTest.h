#pragma once

#include <QBaseWindow>
#include <QTimer>
namespace Ui { class QWindowTest; };

class QWindowTest : public QBaseWindow
{
	Q_OBJECT

public:
	QWindowTest(QWidget *parent = Q_NULLPTR);
	~QWindowTest();

private:

	/// @brief 初始化窗体
	void initWindow();

	/// @brief 初始化控件
	void initWidget();

	/// @brief 添加actions到工具栏
	void addActions();

	/// @brief 处理窗体关闭事件
	void handleCloseEvent(bool& _isClose) override;

private slots:

	/// @brief 初始化数据，界面加载完成后由基类调用，
	void initData() override;

	void actionModify_triggered();
	void on_PB_Dialog1_clicked();
	void on_PB_Dialog2_clicked();
	void on_PB_TestWindow_clicked();
	void slots_HanldeTimeout();

private:
	Ui::QWindowTest *ui;
	QTimer timer;

};
