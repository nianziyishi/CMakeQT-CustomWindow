#ifndef QSTYLEHELPER_H
#define QSTYLEHELPER_H

#include <QString>
class QWidget;

class QStyleHelper
{
public:
	QStyleHelper();

	/// @brief 从qss文件设置样式
	static bool setWidgetStyleFile(QWidget* widget = Q_NULLPTR, const QString _style = ":/lightstyle.qss");

	/// @brief 设置控件错误样式
	static void setWidgetError(QWidget* widget, QString _errorInfo);

	/// @brief 清除控件错误样式
	static void clearWidgetError(QWidget* widget);

	/// @brief 设置控件边框样式，不支持自定义类
	static void setWidgetBorderStyle(QWidget* widget, const QString _style);



	static QString defaultWindowStyle;
};

#endif // QSTYLEHELPER_H
