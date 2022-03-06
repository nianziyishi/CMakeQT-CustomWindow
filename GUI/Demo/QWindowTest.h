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

	/// @brief ��ʼ������
	void initWindow();

	/// @brief ��ʼ���ؼ�
	void initWidget();

	/// @brief ���actions��������
	void addActions();

	/// @brief ������ر��¼�
	void handleCloseEvent(bool& _isClose) override;

private slots:

	/// @brief ��ʼ�����ݣ����������ɺ��ɻ�����ã�
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
