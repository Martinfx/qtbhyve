#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->MemorySpinBox->setRange(4, getMemory());
    ui->MemoryHorizontalSlider->setRange(4, getMemory());
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

int Dialog::getMemory() {

    QProcess process;
    process.start("sysctl", QStringList() << "hw.physmem");
    process.waitForFinished();
    QString physmem = process.readAllStandardOutput();
    process.close();
    physmem.remove("hw.physmem: ");
    //physmem.remove("\n");
    qDebug() << physmem;

    return (int)(physmem.toDouble()/1000/ 1000);
}

void Dialog::on_MemoryHorizontalSlider_valueChanged(int value)
{
     ui->MemorySpinBox->setValue(value);
}

void Dialog::on_MemorySpinBox_valueChanged(int arg1)
{
    ui->MemoryHorizontalSlider->setValue(arg1);
}

