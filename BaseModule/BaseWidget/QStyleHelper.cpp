#include "QStyleHelper.h"

#include <QFile>
#include <QWidget>
#include <QApplication>

QString QStyleHelper::defaultWindowStyle = ":/lightstyle.qss";
//QString QStyleHelper::defaultWindowStyle = ":/darkstyle.qss";

QStyleHelper::QStyleHelper()
{
}

bool QStyleHelper::setWidgetStyleFile(QWidget* widget, const QString _style)
{
	/// @brief 从qss文件设置样式

	QFile qss(_style);
	if (qss.open(QFile::ReadOnly))
	{
		if (widget)
			widget->setStyleSheet(qss.readAll());
		else
			qApp->setStyleSheet(qss.readAll());
		qss.close();
		return true;
	}
	return false;
}

void QStyleHelper::setWidgetError(QWidget* widget, QString _errorInfo)
{
	/// @brief 设置控件错误样式

	if (widget != Q_NULLPTR)
	{
		setWidgetBorderStyle(widget,"{ border-style: outset;border-width: 1px;border-color: red;}");
		widget->setToolTip(_errorInfo);
	}
}

void QStyleHelper::clearWidgetError(QWidget* widget)
{
	/// @brief 清除控件错误样式

	if (widget != Q_NULLPTR)
	{
		widget->setStyleSheet("");
		widget->setToolTip("");
	}
}

void QStyleHelper::setWidgetBorderStyle(QWidget* widget, const QString _style)
{
	/// @brief 设置控件边框样式

	if (widget != Q_NULLPTR)
	{
		widget->setStyleSheet(widget->styleSheet() + QString("%1#%2 ").arg(widget->metaObject()->className()).arg(widget->objectName()) + _style);
	}
}

