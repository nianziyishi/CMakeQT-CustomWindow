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

void TestType()
{

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

	return;
}
