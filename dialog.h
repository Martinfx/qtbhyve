#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <memory>

class VirtualMachine
{
public:
    VirtualMachine() : m_memory(0), m_cpu(0) {}
    ~VirtualMachine() {}

    QString getName();
    QString getType();
    QString getVersion();
    int getMemory();
    int getCpu();
    QString getHostbridge();
    QString getAhcicd();
    QString getAhcihd();
    QString getVirtio();
    QString getIp();
    int getHeigh();
    int getWidth();

    void setName(const QString &name);
    void setType(const QString &type);
    void setVersion(const QString &version);
    void setMemory(int memory);
    void setCpu(int cpu);
    void setHostbridge(const  QString &hostbridge);
    void setAhcicd(const QString &ahcicd);
    void setAhcihd(const QString &ahcihd);
    void setVirtio(const QString &virtio);
    void setIp(const QString &ip);
    void setHeight(int height);
    void setWidth(int width);

private:
    QString m_name;
    QString m_type;
    QString m_version;
    QString m_hostbridge;
    QString m_ahcicd;
    QString m_ahcihd;
    QString m_virtio;
    int m_memory;
    int m_cpu;
    QString m_ip;
    int m_width;
    int m_height;
};

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int getPhysMem();
    int getNCpu();
    std::shared_ptr<VirtualMachine> getVirtualMachine();

signals:
    void VirtualMachineAccept();

private slots:
    void on_NextPushButton_clicked();
    void on_NextPushButton_2_clicked();
    void on_MemoryHorizontalSlider_valueChanged(int value);
    void on_MemorySpinBox_valueChanged(int arg1);
    void on_OSComboBox_activated(const QString &arg1);
    void on_lineEdit_textEdited(const QString &arg1);
    void on_OSVersionComboBox_activated(const QString &arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_CpuHorizontalSlider_valueChanged(int value);
    void on_CpuSpinBox_valueChanged(int arg1);
    void on_pushButtonChooseIso_clicked();
    void on_pushButtonChooseImg_clicked();

private:
    void Memory();

    Ui::Dialog *ui;
    std::shared_ptr<VirtualMachine>  m_virtualMachine;
};
#endif // DIALOG_H
