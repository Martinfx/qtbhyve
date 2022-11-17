#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->MemorySpinBox->setRange(4, getMemory());
    ui->MemoryHorizontalSlider->setRange(4, getMemory());

    QString OS = ui->OSComboBox->currentText();
    if(OS == "Micro$oft Windows"){
       ui->OSVersionComboBox->addItem("Windows 7");
       ui->OSVersionComboBox->addItem("Windows 8");
       ui->OSVersionComboBox->addItem("Windows 10");
       ui->OSVersionComboBox->addItem("Windows 11");
    }
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


void Dialog::on_MemoryHorizontalSlider_valueChanged(int value)
{
     ui->MemorySpinBox->setValue(value);
}

void Dialog::on_MemorySpinBox_valueChanged(int arg1)
{
    ui->MemoryHorizontalSlider->setValue(arg1);
}

void Dialog::on_OSComboBox_activated(const QString &arg1)
{
    if(arg1 == "Micro$oft Windows"){
       ui->OSVersionComboBox->clear();
       ui->OSVersionComboBox->addItem("Windows 7");
       ui->OSVersionComboBox->addItem("Windows 8");
       ui->OSVersionComboBox->addItem("Windows 10");
       ui->OSVersionComboBox->addItem("Windows 11");
    }

    if(arg1 == "Linux"){
       ui->OSVersionComboBox->clear();
       ui->OSVersionComboBox->addItem("Ubuntu");
       ui->OSVersionComboBox->addItem("Lubuntu");
       ui->OSVersionComboBox->addItem("Kubuntu");
    }

    if(arg1 == "BSD"){
       ui->OSVersionComboBox->clear();
       ui->OSVersionComboBox->addItem("FreeBSD");
       ui->OSVersionComboBox->addItem("OpenBSD");
       ui->OSVersionComboBox->addItem("NetBSD");
       ui->OSVersionComboBox->addItem("DragonflyBSD");
    }
}

int Dialog::getMemory() {
    QProcess process;
    process.start("sysctl", QStringList() << "hw.physmem");
    process.waitForFinished();
    QString physmem = process.readAllStandardOutput();
    process.close();
    physmem.remove("hw.physmem: ");
    qDebug() << physmem;
    return (int)(physmem.toDouble()/1024/ 1024);
}
