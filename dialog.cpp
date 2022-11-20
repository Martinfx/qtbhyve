#include "dialog.h"
#include "ui_dialog.h"

QString VirtualMachine::getName() {
    return m_name;
}

QString VirtualMachine::getType() {
    return m_type; }


QString VirtualMachine::getVersion() {
    return m_version;
}

int VirtualMachine::getMemory() {
    return m_memory;
}

int VirtualMachine::getCpu() {
    return m_cpu;
}

void VirtualMachine::setName(const QString &name) {
    m_name = name;
}

void VirtualMachine::setType(const QString &type) {
    m_type = type;
}

void VirtualMachine::setVersion(const QString &version) {
    m_version = version;
}

void VirtualMachine::setMemory(int memory) {
    m_memory = memory;
}


void VirtualMachine::setCpu(int cpu) {
    m_cpu = cpu;
}

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->MemorySpinBox->setRange(4, getPhysMem());
    ui->MemoryHorizontalSlider->setRange(4, getPhysMem());
    ui->CpuHorizontalSlider->setRange(1, getNCpu());
    ui->CpuSpinBox->setRange(1, getNCpu());

    QString OS = ui->OSComboBox->currentText();
    if (OS == "Micro$oft Windows") {
        ui->OSVersionComboBox->addItem("Windows 7");
        ui->OSVersionComboBox->addItem("Windows 8");
        ui->OSVersionComboBox->addItem("Windows 10");
        ui->OSVersionComboBox->addItem("Windows 11");
        ui->MemoryHorizontalSlider->setValue(1024);
    }

    m_virtualMachine = std::make_shared<VirtualMachine>();
    ui->lineEdit->setText("VirtualMachine");
    m_virtualMachine->setName(ui->lineEdit->text());
}

Dialog::~Dialog() {
    delete ui;
}

std::shared_ptr<VirtualMachine> Dialog::getVirtualMachine() {
    return m_virtualMachine;
}

void Dialog::on_NextPushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::on_NextPushButton_2_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void Dialog::on_MemoryHorizontalSlider_valueChanged(int value) {
    ui->MemorySpinBox->setValue(value);
}

void Dialog::on_MemorySpinBox_valueChanged(int arg1) {
    ui->MemoryHorizontalSlider->setValue(arg1);
}

void Dialog::on_CpuHorizontalSlider_valueChanged(int value)
{
    ui->CpuSpinBox->setValue(value);
}

void Dialog::on_CpuSpinBox_valueChanged(int arg1)
{
    ui->CpuHorizontalSlider->setValue(arg1);
}

void Dialog::on_OSComboBox_activated(const QString &arg1) {
    if (arg1 == "Micro$oft Windows") {
        ui->OSVersionComboBox->clear();
        ui->MemoryHorizontalSlider->setValue(2048);
        ui->OSVersionComboBox->addItem("Windows 7");
        ui->OSVersionComboBox->addItem("Windows 8");
        ui->OSVersionComboBox->addItem("Windows 10");
        ui->OSVersionComboBox->addItem("Windows 11");
    }

    if (arg1 == "Linux") {
        ui->OSVersionComboBox->clear();
        ui->OSVersionComboBox->addItem("Ubuntu");
        ui->OSVersionComboBox->addItem("Lubuntu");
        ui->OSVersionComboBox->addItem("Kubuntu");
        ui->MemoryHorizontalSlider->setValue(1024);
    }

    if (arg1 == "BSD") {
        ui->OSVersionComboBox->clear();
        ui->OSVersionComboBox->addItem("FreeBSD");
        ui->OSVersionComboBox->addItem("OpenBSD");
        ui->OSVersionComboBox->addItem("NetBSD");
        ui->OSVersionComboBox->addItem("DragonflyBSD");
        ui->MemoryHorizontalSlider->setValue(1024);
    }

    m_virtualMachine->setType(arg1);
    m_virtualMachine->setVersion(ui->OSVersionComboBox->currentText());
    /* hack*/ Memory();
}

void Dialog::on_OSVersionComboBox_activated(const QString &arg1) {
    if (arg1 == "Windows 7" || arg1 == "Windows 8" || arg1 == "Windows 10") {
        ui->MemoryHorizontalSlider->setValue(2048);
    }

    if (arg1 == "Windows 11") {
        ui->MemoryHorizontalSlider->setValue(4096);
    }
}

void Dialog::on_lineEdit_textEdited(const QString &arg1) {
    m_virtualMachine->setName(arg1);
}

int Dialog::getPhysMem() {
    QProcess process;
    process.start("sysctl", QStringList() << "hw.physmem");
    process.waitForFinished();
    QString physmem = process.readAllStandardOutput();
    process.close();
    physmem.remove("hw.physmem: ");
    qDebug() << physmem;
    return (int)(physmem.toDouble() / 1024 / 1024);
}

int Dialog::getNCpu() {
    QProcess process;
    process.start("sysctl", QStringList() << "hw.ncpu");
    process.waitForFinished();
    QString ncpu = process.readAllStandardOutput();
    process.close();
    ncpu.remove("hw.ncpu: ");
    qDebug() << ncpu;
    return ncpu.toInt();
}

void Dialog::Memory() {
    m_virtualMachine->setMemory(ui->MemoryHorizontalSlider->value());
}

void Dialog::on_buttonBox_accepted() {
    m_virtualMachine->setName(ui->lineEdit->text());
    m_virtualMachine->setType(ui->OSComboBox->currentText());
    m_virtualMachine->setVersion(ui->OSVersionComboBox->currentText());
    m_virtualMachine->setMemory(ui->MemoryHorizontalSlider->value());
    m_virtualMachine->setCpu(ui->CpuHorizontalSlider->value());
    emit VirtualMachineAccept();
    Dialog::close();
}

void Dialog::on_buttonBox_rejected() {
    m_virtualMachine->setName("");
    m_virtualMachine->setType("");
    m_virtualMachine->setVersion("");
    m_virtualMachine->setMemory(0);
    m_virtualMachine->setCpu(0);
    Dialog::close();
}
