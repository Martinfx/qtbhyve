#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
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

QString VirtualMachine::getHostbridge() {
    return m_hostbridge;
}

QString VirtualMachine::getAhcicd() {
    return m_ahcicd;
}

QString VirtualMachine::getAhcihd() {
    return m_ahcihd;
}

QString VirtualMachine::getVirtio() {
    return m_virtio;
}

QString VirtualMachine::getIfconfigName() {
    return m_ifconfigname;
}

QString VirtualMachine::getIp() {
    return m_ip;
}

int VirtualMachine::getHeight (){
    return m_height;
}

int VirtualMachine::getWidth(){
    return m_width;
}

QString VirtualMachine::getXhci(){
    return m_xhci;
}

QString VirtualMachine::getTablet(){
    return m_tablet;
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

void VirtualMachine::setHostbridge(const QString &hostbridge){
    m_hostbridge = hostbridge;
}

void VirtualMachine::setAhcicd(const QString &ahcicd){
    m_ahcicd = ahcicd;
}

void VirtualMachine::setAhcihd(const QString &ahcihd){
    m_ahcihd = ahcihd;
}

void VirtualMachine::setVirtio(const QString &virtio){
    m_virtio = virtio;
}

void VirtualMachine::setIfconfigName(const QString &ifconfigname){
    m_ifconfigname = ifconfigname;
}

void VirtualMachine::setIp(const QString &ip) {
    m_ip = ip;
}

void VirtualMachine::setHeight(int height){
    m_height = height;
}

void VirtualMachine::setWidth(int width)  {
    m_width = width;
}

void VirtualMachine::setXhci(const QString &xhci) {
    m_xhci = xhci;
}

void VirtualMachine::setTablet(const QString &tablet) {
    m_tablet = tablet;
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

    m_virtualMachine = new VirtualMachine();
    ui->lineEdit->setText("VirtualMachine");
    m_virtualMachine->setName(ui->lineEdit->text());
}

Dialog::~Dialog() {
    delete ui;
}

VirtualMachine* Dialog::getVirtualMachine() {
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
    m_virtualMachine->setHostbridge(ui->lineEditHostbridge->text());
    m_virtualMachine->setAhcicd(ui->lineEditPathIso->text());
    m_virtualMachine->setAhcihd(ui->lineEditPathImg->text());
    m_virtualMachine->setVirtio(ui->comboBoxVirtio->currentText());
    m_virtualMachine->setIfconfigName(ui->lineEditIfconfigName->text());
    m_virtualMachine->setHostbridge(ui->lineEditHostbridge->text());
    m_virtualMachine->setIp(ui->lineEditIp->text());
    m_virtualMachine->setHeight(ui->lineEditWidth->text().toInt());
    m_virtualMachine->setWidth(ui->lineEditHeight->text().toInt());
    m_virtualMachine->setXhci(ui->lineEditXhci->text());
    m_virtualMachine->setTablet(ui->lineEditTablet->text());
    emit VirtualMachineAccept();
    Dialog::close();
}

void Dialog::on_buttonBox_rejected() {
    m_virtualMachine->setName("");
    m_virtualMachine->setType("");
    m_virtualMachine->setVersion("");
    m_virtualMachine->setMemory(0);
    m_virtualMachine->setCpu(0);
    m_virtualMachine->setHostbridge("");
    m_virtualMachine->setAhcicd("");
    m_virtualMachine->setAhcihd("");
    m_virtualMachine->setVirtio("");
    m_virtualMachine->setIfconfigName("");
    m_virtualMachine->setIp("");
    m_virtualMachine->setHeight(0);
    m_virtualMachine->setWidth(0);
    m_virtualMachine->setXhci("");
    m_virtualMachine->setTablet("");
    Dialog::close();
}

void Dialog::on_pushButtonChooseIso_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Iso (*.iso)"));
    qDebug() << filePath;
    ui->lineEditPathIso->setText(filePath);
}


void Dialog::on_pushButtonChooseImg_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Img (*.img)"));
    qDebug() << filePath;
    ui->lineEditPathImg->setText(filePath);
}

void Dialog::on_lineEditHostbridge_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setHostbridge(arg1);
}

void Dialog::on_lineEditPathIso_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setAhcicd(arg1);
}

void Dialog::on_lineEditPathImg_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setAhcihd(arg1);
}

void Dialog::on_lineEditVirtio_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setVirtio(arg1);
}

void Dialog::on_lineEditIp_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setIp(arg1);
}

void Dialog::on_lineEditWidth_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setHeight(arg1.toInt());
}

void Dialog::on_lineEditHeight_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setWidth(arg1.toInt());
}

void Dialog::on_lineEditXhci_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setXhci(arg1);
}

void Dialog::on_lineEditTablet_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setTablet(arg1);
}

void Dialog::on_comboBox_activated(const QString &arg1)
{
    this->m_virtualMachine->setVirtio(arg1);
}

void Dialog::on_lineEditIfconfigName_textChanged(const QString &arg1)
{
    this->m_virtualMachine->setIfconfigName(arg1);
}

