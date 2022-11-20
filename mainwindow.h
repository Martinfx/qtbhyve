#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
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

public slots:
    void addItem();

private slots:
    void on_newVirtual_clicked();
    void on_listVirtuals_itemClicked(QListWidgetItem *item);
    void on_settingsVirtual_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Dialog> m_dialog;
    QVector< std::shared_ptr<VirtualMachine>> m_virtualMachine;
    void test();
    void read();
    void write();
};

#endif // MAINWINDOW_H
