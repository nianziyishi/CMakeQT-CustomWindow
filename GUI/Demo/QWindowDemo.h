#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QWindowDemo.h"

class  QWindowDemo : public QMainWindow
{
    Q_OBJECT

public:
    QWindowDemo(QWidget *parent = Q_NULLPTR);

private slots:
	void on_PB_Window1_clicked();
    void on_PB_Window2_clicked();
    void on_PB_Debug_clicked();
    
private:
    Ui::QWindowDemoClass ui;
};
