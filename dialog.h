#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <memory>

class VirtualMachine
{
public:
    VirtualMachine() {}
    ~VirtualMachine(){}

    QString getName();
    QString getType();
    QString getVersion();
    int getMemory();

    void setName(QString name);
    void setType(QString type);
    void setVersion(QString version);
    void setMemory(int memory);

private:
    QString m_name;
    QString m_type;
    QString m_version;
    int m_memory;
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
    int getHwMemory();
    void Memory();

private slots:
    void on_NextPushButton_clicked();
    void on_NextPushButton_2_clicked();
    void on_MemoryHorizontalSlider_valueChanged(int value);
    void on_MemorySpinBox_valueChanged(int arg1);
    void on_OSComboBox_activated(const QString &arg1);
    void on_lineEdit_textEdited(const QString &arg1);
    void on_OSVersionComboBox_activated(const QString &arg1);

private:
    Ui::Dialog *ui;
    VirtualMachine *m_virtualMachine;
};
#endif // DIALOG_H
