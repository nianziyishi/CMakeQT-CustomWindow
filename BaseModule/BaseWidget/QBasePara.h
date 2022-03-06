#ifndef QTBASEPARA_H
#define QTBASEPARA_H

namespace QBasePara
{
	//标题栏按钮类型
	enum TypeTitleBar
	{
		None_TitleBar = 0,	//无按钮
		Close = 1,			//关闭按钮
		Minimize = 2,		//最小化
		Maximize = 4		//最大化
	};

	//对话框按钮类型
	enum TypeDialog
	{
		None_Dialog = 0,	//无按钮
		OK = 1,				//确定按钮
		Cancel = 2,			//取消按钮
	};
}

#endif // QTBASEPARA_H
