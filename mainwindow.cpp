#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_newVirtualMachine;
}


void MainWindow::on_newVirtual_clicked()
{
    m_newVirtualMachine = new Dialog();
    m_newVirtualMachine->setModal(true);

    m_newVirtualMachine->show();
    qDebug() <<  m_newVirtualMachine->getMemory();
}



