#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //setWindowFlag(Qt::Popup);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_NextPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Dialog::on_NextPushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

