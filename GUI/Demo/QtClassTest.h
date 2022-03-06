#pragma once

#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix>
#include <QBitArray>
#include <QDateTime>
#include <QVector>
#include <QList>
#include <QMap>
#include <QSet>
#include <QHash>
#include <QWindow>
#include <QUrl>
#include <QDebug>

class Human
{
public:
	Human() {};
	QString mName;
	int mAge;
	int mCards[3];
};

void TimestampToDatetime(QDateTime dt)
{
	QDateTime qdatetime(QDateTime::currentDateTime());
	long timestamp = dt.toMSecsSinceEpoch();
	//long timestamp = 1001997058518;	//1638337352
	//"2021 年 12 月 1 日1时55分53秒518毫秒"
	// 2021 年 12 月 1 日13:42:32 //49352秒
	//double now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	long days = 24 * 60 * 60;	//86400
	long months = 2630016;	//2592000	//	2629743
	long years = 31556736;	//31104000	//	31556926
	long n, yy, mm, dd, HH, MM, SS, MS;

	n = timestamp / 1000;
	yy = n / years + 1970;
	mm = n % years / months + 1;
	dd = n % years % months / days + 1;
	long d1 = n % years;
	long d2 = d1 % months;
	long d3 = n % years % months;

	long year = 365 * days;
	long month = 30 * days;
	long dayTotalSec = n % year % month % days;
	HH = n % year % month % days / 3600 + 8;
	MM = n % year % month % days % 3600 / 60;
	SS = n % year % month % days % 3600 % 60;
	MS = timestamp % 1000;

	qDebug() << QString("%1年%2月%3日%4时%5分%6秒%7毫秒")
		.arg(yy).arg(mm).arg(dd).arg(HH).arg(MM).arg(SS).arg(MS);

	//int jd = QDate::currentDate().toJulianDay();
	int jd = 2459550;


	int a = jd + 32044;
	int b = (4 * a + 3) / 146097;
	int c = a - ((146097 * b) / 4);
	int d = (4 * c + 3) / 1461;
	int e = c - ((1461 * d) / 4);
	int m = (5 * e + 2) / 153;
	int day1 = e - ((153 * m + 2) / 5) + 1;
	int month1 = m + 3 - 12 * (m / 10);
	int year1 = 100 * b + d - 4800 + (m / 10);

	int day2 = (((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) - ((1461 * ((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) / 4)) - ((153 * ((5 * (((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) - ((1461 * ((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) / 4)) + 2) / 153) + 2) / 5) + 1;
	int month2 = ((5 * (((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) - ((1461 * ((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) / 4)) + 2) / 153) + 3 - 12 * (((5 * (((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) - ((1461 * ((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) / 4)) + 2) / 153) / 10);
	int year2 = 100 * (((4 * (jd + 32044) + 3) / 146097)) + (((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) - 4800 + (((5 * (((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) - ((1461 * ((4 * ((jd + 32044) - ((146097 * ((4 * (jd + 32044) + 3) / 146097)) / 4)) + 3) / 1461)) / 4)) + 2) / 153) / 10);


	qDebug() << QString("%1年%2月%3日").arg(year1).arg(month1).arg(day1);
	qDebug() << QString("%1年%2月%3日").arg(year2).arg(month2).arg(day2);

	return;
}

void ConvertTime()
{
	long timestamp = 1644989272;	//2022-02-16 13:27:52
	int ss = timestamp % 60;
	int mm = timestamp / 60 % 60;
	int hh = timestamp / 60 / 60 % 24+8;
	int DD = timestamp / 60 / 60 / 24;
	long a = DD + 2472632;
	long b = (4 * a + 3) / 146097;
	long c = ((-b * 146097) / 4) + a;
	long d = (4 * c + 3) / 1461;
	long e = ((-1461 * d) / 4) + c;
	long m = ((5 * e + 2) / 153);
	DD = -int((153 * m + 2) / 5) + e + 1;
	int MM = int(-m / 10) * 12 + m + 3;
	int YY = b * 100 + d - 4800 + int(m / 10);

	QString str = QString("%1年%2月%3日").arg(YY).arg(MM).arg(DD).arg(hh).arg(mm).arg(ss);
	qDebug() << str;

}

void TestType()
{
	QWidgetList widgetList = QApplication::allWidgets();

	qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
	//TimestampToDatetime(QDateTime::currentDateTime());
	//ConvertTime();


	int size_int = sizeof(int);		//4
	int size_QString = sizeof(QString);	//8
	int size_QStringList = sizeof(QStringList);	//8
	int size_void = sizeof(void*);	//8
	int size_QUrlPrivate = sizeof(QAtomicInt) + sizeof(int) + (sizeof(QString) * 0);	//4+4+8*i


	std::string str = "asd1234中";
	QPoint qpoint(20, 30);
	QLine qline(20, 30, 20, 60);
	QRect qrect(20, 30, 20, 20);
	QVector2D qvector2d(20, 30);
	QVector3D qvector3d(20, 30, 20);
	QMatrix qmatrix(20, 20, 30, 30, 40, 40);
	QChar qchar = 'h';
	QString qstring = "as12中";
	QUrl qurl = QUrl("http://192.168.103.102:7011/TestPath/");
	//qurl.setUserName("username");
	qurl.setPassword("password");
	qurl.setQuery("");
	qurl.setFragment("fragment");
	QStringList qstringlist = QString("as12,asd3,cxv4中").split(',');
	QByteArray qbytearray = "fdg123中";
	QBitArray qbitarray(3, true);
	QTime qtime(QTime::currentTime());
	QDate qdate(QDate::currentDate());
	QDateTime qdatetime(QDateTime::currentDateTime());	
	QVector<QString> qvector1;
	qvector1.append("123");
	qvector1.append("asd中");
	QVector<int> qvector;
	qvector.append(2);
	qvector.append(5);
	QList<int> qlist1;
	qlist1.append(3);
	qlist1.append(4);
	QList<QString> qlist;
	qlist.append("123");
	qlist.append("asd");
	QMap<int, QString> qmap;	//no support
	qmap.insert(2, "asd");
	qmap.insert(3, "asd123中");
	QHash<int, QString> qhash;	//no support
	qhash.insert(2, "asd");
	qhash.insert(3, "asd123中");
	QSet<QString> qset;			//no support
	qset.insert("asd");
	qset.insert("qwe中");
	QVariant qvariant(QString("asd中"));
	QWindow qwindow;
	QWidget qwidget;

	Human* xiaoming = new Human();
	xiaoming->mName = "XiaoMing";
	xiaoming->mAge = 20;
	xiaoming->mCards[0] = 12344;
	xiaoming->mCards[1] = 12345;
	Human* xiaohua = new Human();
	xiaohua->mName = "XiaoHua";
	xiaohua->mAge = 22;
	xiaohua->mCards[0] = 22344;
	xiaohua->mCards[1] = 32345;
	QList<Human*> list_homes;
	list_homes.append(xiaoming);
	list_homes.append(xiaohua);

	int ii = 0;
}
