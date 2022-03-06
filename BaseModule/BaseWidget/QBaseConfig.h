#ifndef QBASECONFIG_H
#define QBASECONFIG_H

#include <QString>

namespace QBaseConfig
{
	static const QString m_icon_titlebar = ":/icon_window_titlebar.ico";
	static const QString m_icon_min = ":/icon_window_minimize.png";
	static const QString m_icon_max = ":/icon_window_maximize.png";
	static const QString m_icon_close = ":/icon_window_close.png";
	static const QString m_icon_restore = ":/icon_window_restore.png";
	static const QString m_icon_hint = ":/icon_dialog_hint.ico";

	static const QString m_dialog_hint = QStringLiteral("提示");
	static const QString m_mask_hint = QStringLiteral("正在处理中，请稍候...");

};

#endif // QBASECONFIG_H
