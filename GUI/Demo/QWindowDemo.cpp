#include "QWindowDemo.h"
#include "QWindowTest.h"
#include "QBaseDialog.h"
#include <QMessageBox>
#include "QtClassTest.h"

QWindowDemo::QWindowDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void QWindowDemo::on_PB_Window1_clicked()
{
    QWindowTest* window = new QWindowTest();
    window->showWindow(this);
}

void QWindowDemo::on_PB_Window2_clicked()
{
    QMessageBox::information(this,"hint","this is qt dialog Demo");
    QBaseDialog::showDialog(this, "this is dialog Demo", "hint");
}

void QWindowDemo::on_PB_Debug_clicked()
{
    TestType();
}
