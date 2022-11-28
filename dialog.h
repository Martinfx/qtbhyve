#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <memory>

class VirtualMachine
{
public:
    VirtualMachine() : m_memory(0), m_cpu(0),
        m_height(0), m_width(0){}
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
    QString getIfconfigName();
    QString getIp();
    int getHeight();
    int getWidth();
    QString getXhci();
    QString getTablet();

    void setName(const QString &name);
    void setType(const QString &type);
    void setVersion(const QString &version);
    void setMemory(int memory);
    void setCpu(int cpu);
    void setHostbridge(const QString &hostbridge);
    void setAhcicd(const QString &ahcicd);
    void setAhcihd(const QString &ahcihd);
    void setVirtio(const QString &virtio);
    void setIfconfigName(const QString &ifconfigname);
    void setIp(const QString &ip);
    void setHeight(int height);
    void setWidth(int width);
    void setXhci(const QString &xhci);
    void setTablet(const QString &tablet);

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
    QString m_xhci;
    QString m_tablet;
    QString m_ifconfigname;
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
    VirtualMachine *getVirtualMachine();

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
    void on_lineEditHostbridge_textChanged(const QString &arg1);
    void on_lineEditPathIso_textChanged(const QString &arg1);
    void on_lineEditPathImg_textChanged(const QString &arg1);
    void on_lineEditVirtio_textChanged(const QString &arg1);
    void on_lineEditIp_textChanged(const QString &arg1);
    void on_lineEditWidth_textChanged(const QString &arg1);
    void on_lineEditHeight_textChanged(const QString &arg1);
    void on_lineEditXhci_textChanged(const QString &arg1);
    void on_lineEditTablet_textChanged(const QString &arg1);
    void on_comboBox_activated(const QString &arg1);
    void on_lineEditIfconfigName_textChanged(const QString &arg1);

private:
    void Memory();

    Ui::Dialog *ui;
    VirtualMachine *m_virtualMachine;
};
#endif // DIALOG_H
