#include "QBaseMask.h"

#include <QLabel>
#include <QProgressBar>
#include <QGridLayout>
#include <QPointer>
#include <QDesktopWidget>
#include <QApplication>
#include "QBaseConfig.h"


QPointer<QWidget> QBaseMask::ptr_widget = Q_NULLPTR;
QBaseMask::QBaseMask(QWidget* parent)
	: QWidget(parent)
{
}

QBaseMask::~QBaseMask()
{
}

QWidget* QBaseMask::CreateWidget(bool _isWindow)
{
	/// @brief 创建控件

	auto proBar = new QProgressBar();
	proBar->setRange(0, 0);
	proBar->setMaximumSize(300, 30);
	proBar->setTextVisible(false);
	//proBar->setStyleSheet("background-color: #19232D");

	auto label = new QLabel();
	label->setAttribute(Qt::WA_TranslucentBackground);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	auto gridLayout = new QGridLayout();
	gridLayout->setContentsMargins(0, 0, 0, 0);
	gridLayout->addWidget(proBar, 0, 0);
	gridLayout->addWidget(label, 0, 0);

	auto widget = new QWidget();
	if (_isWindow)
	{
		widget->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
		widget->setWindowModality(Qt::ApplicationModal);
	}
	widget->setAttribute(Qt::WA_TranslucentBackground);
	//widget->setStyleSheet("background-color: rgb(128, 128, 128, 120)");
	widget->setMinimumSize(300, 30);
	widget->setLayout(gridLayout);

	return widget;
}

void QBaseMask::ShowBaseMaskWindow(QWidget* parent, QString text)
{
	/// @brief 显示蒙板窗体

	if (!ptr_widget)
    {
		ptr_widget = CreateWidget(true);
	}

	if (ptr_widget->children().size() == 3)
	{
		((QLabel*)ptr_widget->children().at(2))->setText(text.isEmpty() ? QBaseConfig::m_mask_hint : text);
	}
	ptr_widget->setParent(parent, ptr_widget->windowFlags());
	ptr_widget->setGeometry(0, 0, ptr_widget->minimumSize().width(), ptr_widget->minimumSize().height());
	if (parent)
	{
		ptr_widget->move(parent->mapToGlobal(QPoint(0, 0)) + QPoint((parent->width() - ptr_widget->width()) / 2, (parent->height() - ptr_widget->height()) / 2));
	}
	else
	{
		auto pDesk = QApplication::desktop();
		ptr_widget->move((pDesk->width() - ptr_widget->width()) / 2, (pDesk->height() - ptr_widget->height()) / 2);
	}
	ptr_widget->show();

}

void QBaseMask::CloseBaseMaskWindow()
{
	/// @brief 关闭蒙板窗体

	if (ptr_widget)
	{
		ptr_widget->setParent(Q_NULLPTR, ptr_widget->windowFlags());
		ptr_widget->hide();
	}
}
