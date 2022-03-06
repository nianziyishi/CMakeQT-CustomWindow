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

	/// @brief ��ʾ����
	void showWindow(QWidget* parent = Q_NULLPTR);

	/// @brief �¼�ѭ��,��������
	int execWindow(QWidget* parent = Q_NULLPTR);

	/// @brief ���ش���
	void hideWindow(int _status = 0);

	/// @brief �رմ���
	void closeWindow(int _status = 0);

	/// @brief �������û���ù�����
	void setEnableToolBar(bool _isEnable);

	/// @brief ������ʾ�����ر�����
	void setTitleBarVisible(bool _isVisible);

protected:

	/// @brief ������ر��¼���true�ر�, false���ر�
	virtual void handleCloseEvent(bool& _isClose);

	/// @brief ���ñ�������ť
	/// @param type ��ť����
	void setWindowButtonType(int _type);

	/// @brief ���ù�����actions
	void setToolBarActions(QList<QAction*> _list_action);

	/// @brief ���actions
	void clearActions();

	/// @brief ��ʾ�Ի�����
	bool showDialogWindow(QString _text, QString _title = "", int _buttonType = QBasePara::TypeDialog::OK);

	/// @brief ��ʾ�ɰ崰��
	void showMaskWindow(QString text = "");

	/// @brief �ر��ɰ�
	void closeMaskWindow();
	
	/// @brief ���ÿؼ�������ʽ
	void setWidgetError(QWidget* widget, QString _errorInfo);

	/// @brief ����ؼ�������ʽ
	void clearWidgetError(QWidget* widget);

	/// @brief ���ô�����ʽ
	bool setWindowStyle(QString style = "");

	/// @brief ���ò˵����Ƿ�ɼ�
	void setMenuBarVisible(bool _isVisible);

	/// @brief ����״̬���Ƿ�ɼ�
	void setStatusBarVisible(bool _isVisible);


private:

	/// @brief ��ʼ������
	void initWindow();

	/// @brief ������ʾ�¼�
	void showEvent(QShowEvent*) override;

	/// @brief ����ر��¼�
	void closeEvent(QCloseEvent* event) override;

	/// @brief �����С�ı��¼�
	void resizeEvent(QResizeEvent* event) override;

	/// @brief �ı�����ؼ��ĸ�����
	void changeChildWidgetParent();

	/// @brief ���ô���߿�
	void setWindowBorder();

signals:
	/// @brief ����ر��ź�
	void signals_WindowClose(bool& _isCanClose);

private slots:
	/// @brief ��ʼ������
	virtual void initData();

private:
	Ui::QBaseWindow *ui;
	QPointer<QBaseTitleBar> mPtr_Titlebar;	//������
	QEventLoop mLoop;	//ѭ���¼�
	QObjectList mList_BaseObject;	//����������
	bool mIsMaskShowing = false;
	bool mIsAlreadyInitData = false;

};
#endif // QBASEWINDOW_H
