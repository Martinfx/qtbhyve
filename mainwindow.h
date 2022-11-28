#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
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
    void on_deleteVirtual_clicked();
    void on_listVirtuals_currentRowChanged(int currentRow);
    void on_listVirtuals_itemDoubleClicked(QListWidgetItem *item);
    void on_playVirtual_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Dialog> m_dialog;
    QVector<VirtualMachine*> m_virtualMachine;
    void test();
    /// read data from json file
    void read();
    /// write data to json file
    void write();
    /// Selected item from widgetlist
    int m_selectedItem;
    /// Actual pid process
    Q_PID pid;
};

#endif // MAINWINDOW_H
