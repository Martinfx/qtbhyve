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
    delete m_dialog;
}


void MainWindow::on_newVirtual_clicked()
{
    m_dialog = new Dialog();
    m_dialog->setModal(true);
    m_dialog->show();

    //m_virtalMachine.push_back(m_dialog->;
}



