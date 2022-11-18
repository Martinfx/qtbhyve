#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>

#include "dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newVirtual_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *m_dialog;
    QVector<VirtualMachine*> m_virtalMachine;
};

class VirtualMachine2
{
public:
    VirtualMachine2() {}
    ~VirtualMachine2(){}

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
    int memory;
};

#endif // MAINWINDOW_H
