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
    write();
    delete ui;
}

void MainWindow::addItem() {
    ui->listVirtuals->addItem(m_dialog->getVirtualMachine()->getName());
}

void MainWindow::on_newVirtual_clicked()
{
    m_dialog = std::make_shared<Dialog>();
    m_dialog->setModal(true);
    QObject::connect(m_dialog.get(), SIGNAL(VirtualMachineAccept()), this,
                     SLOT(addItem()));
    m_dialog->show();
    m_virtalMachine.push_back(m_dialog->getVirtualMachine());

    //qDebug() << m_virtalMachine.count();
    //qDebug() << m_dialog->getVirtualMachine()->getName();
}

void MainWindow::test() {
    int counter = 0;
    for(auto i : m_virtalMachine) {
        qDebug() << counter ;
        qDebug() << "Version: " << i->getVersion();
        qDebug() << "Type: "    << i->getType();
        qDebug() << "Name: "    << i->getName();
        qDebug() << "Memory: "  << i->getMemory();
        counter++;
    }
    //counter = 0;
}

void MainWindow::on_listVirtuals_itemClicked(QListWidgetItem *item)
{
    for(auto i : m_virtalMachine) {
        if(item->text() == i->getName()) {
            qDebug() << "---------------";
            qDebug() << i->getName();
            qDebug() << i->getMemory();
            //qDebug() << "---------------";
        }
    }
    //qDebug() << ;
}

void MainWindow::write() {
    QJsonArray mainJsonObject;
    QJsonObject jsonObjectVirtuals;
    int counter = 0;
    for(auto i : m_virtalMachine) {
        //qDebug() << counter ;
        jsonObjectVirtuals.insert("virtual", QJsonValue( counter++));
        jsonObjectVirtuals.insert("memory", QJsonValue(i->getMemory()));
        jsonObjectVirtuals.insert("type", QJsonValue(i->getType()));
        jsonObjectVirtuals.insert("Name", QJsonValue(i->getName()));
        jsonObjectVirtuals.insert("Version", QJsonValue(i->getVersion()));
        mainJsonObject.push_back(jsonObjectVirtuals);
    }
    // mainJsonObject.insert("virtual", jsonObjectVirtuals);

    QJsonDocument jsonDoc;
    jsonDoc.setArray(mainJsonObject);
    QByteArray data = jsonDoc.toJson();

    QFile file("save.json");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

void MainWindow::on_settingsVirtual_clicked()
{
    test();
}

