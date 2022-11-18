#include "dialog.h"
#include "ui_dialog.h"

QString VirtualMachine::getName(){
    return m_name;
}

QString VirtualMachine::getType(){
    return m_type;
}

QString VirtualMachine::getVersion(){
    return m_version;
}

int VirtualMachine::getMemory() {
    return m_memory;
}

void VirtualMachine::setName(QString name){
    m_name = name;
}

void VirtualMachine::setType(QString type){
    m_type = type;
}

void VirtualMachine::setVersion(QString version){
    m_version = version;
}

void VirtualMachine::setMemory(int memory) {
    m_memory = memory;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->MemorySpinBox->setRange(4, getHwMemory());
    ui->MemoryHorizontalSlider->setRange(4, getHwMemory());

    QString OS = ui->OSComboBox->currentText();
    if(OS == "Micro$oft Windows"){
       ui->OSVersionComboBox->addItem("Windows 7");
       ui->OSVersionComboBox->addItem("Windows 8");
       ui->OSVersionComboBox->addItem("Windows 10");
       ui->OSVersionComboBox->addItem("Windows 11");
       ui->MemoryHorizontalSlider->setValue(1024);
    }

   m_virtualMachine = new VirtualMachine();
   //m_virtualMachine->setMemory(getMemory());
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
    //m_virtualMachine->setMemory(value);
}

void Dialog::on_MemorySpinBox_valueChanged(int arg1)
{
    ui->MemoryHorizontalSlider->setValue(arg1);
    //m_virtualMachine->setMemory(arg1);
}

void Dialog::on_OSComboBox_activated(const QString &arg1)
{
    if(arg1 == "Micro$oft Windows"){
       ui->OSVersionComboBox->clear();
       ui->MemoryHorizontalSlider->setValue(2048);
       ui->OSVersionComboBox->addItem("Windows 7");
       ui->OSVersionComboBox->addItem("Windows 8");
       ui->OSVersionComboBox->addItem("Windows 10");
       ui->OSVersionComboBox->addItem("Windows 11");
       /*if(ui->OSVersionComboBox->currentText() == "Windows 11") {
         ui->MemoryHorizontalSlider->setValue(4096);
       }*/
    }

    if(arg1 == "Linux"){
       ui->OSVersionComboBox->clear();
       ui->OSVersionComboBox->addItem("Ubuntu");
       ui->OSVersionComboBox->addItem("Lubuntu");
       ui->OSVersionComboBox->addItem("Kubuntu");
       ui->MemoryHorizontalSlider->setValue(1024);
    }

    if(arg1 == "BSD"){
       ui->OSVersionComboBox->clear();
       ui->OSVersionComboBox->addItem("FreeBSD");
       ui->OSVersionComboBox->addItem("OpenBSD");
       ui->OSVersionComboBox->addItem("NetBSD");
       ui->OSVersionComboBox->addItem("DragonflyBSD");
       ui->MemoryHorizontalSlider->setValue(1024);
    }

    m_virtualMachine->setType(arg1);
    m_virtualMachine->setVersion(ui->OSVersionComboBox->currentText());
    Memory();
}

void Dialog::on_OSVersionComboBox_activated(const QString &arg1)
{
    if(arg1 == "Windows 7" || "Windows 8" ||"Windows 10") {
        ui->MemoryHorizontalSlider->setValue(2048);
    }

    if(arg1 == "Windows 11") {
        ui->MemoryHorizontalSlider->setValue(4096);
    }
}

void Dialog::on_lineEdit_textEdited(const QString &arg1)
{
    m_virtualMachine->setName(arg1);
}

int Dialog::getHwMemory() {
    QProcess process;
    process.start("sysctl", QStringList() << "hw.physmem");
    process.waitForFinished();
    QString physmem = process.readAllStandardOutput();
    process.close();
    physmem.remove("hw.physmem: ");
    qDebug() << physmem;
    return (int)(physmem.toDouble()/1024/ 1024);
}

void Dialog::Memory(){
    m_virtualMachine->setMemory(ui->MemoryHorizontalSlider->value());
    //return ui->MemoryHorizontalSlider->value();
}
