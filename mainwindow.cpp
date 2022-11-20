#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    read();
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

    if(!m_dialog->getVirtualMachine()->getName().isEmpty() ||
        !m_dialog->getVirtualMachine()->getType().isEmpty()){
        m_virtualMachine.push_back(m_dialog->getVirtualMachine());
    }

    //qDebug() << m_virtalMachine.count();
    //qDebug() << m_dialog->getVirtualMachine()->getName();
}

void MainWindow::test() {
    int counter = 0;
    for(auto i : m_virtualMachine) {
        qDebug() << counter ;
        qDebug() << "Version: " << i->getVersion();
        qDebug() << "Type: "    << i->getType();
        qDebug() << "Name: "    << i->getName();
        qDebug() << "Memory: "  << i->getMemory();
        counter++;
    }
}

void MainWindow::on_listVirtuals_itemClicked(QListWidgetItem *item)
{
    for(auto i : m_virtualMachine) {
        if(item->text() == i->getName()) {
            qDebug() << "---------------";
            qDebug() << i->getName();
            qDebug() << i->getMemory();
            //qDebug() << "---------------";
        }
    }
}

void MainWindow::write() {
    QJsonArray mainJsonObject;
    QJsonObject jsonObjectVirtuals;
    int counter = 0;
    for(auto i : m_virtualMachine) {
        jsonObjectVirtuals.insert("virtual", QJsonValue( counter++));
        jsonObjectVirtuals.insert("memory", QJsonValue(i->getMemory()));
        jsonObjectVirtuals.insert("type", QJsonValue(i->getType()));
        jsonObjectVirtuals.insert("name", QJsonValue(i->getName()));
        jsonObjectVirtuals.insert("Version", QJsonValue(i->getVersion()));
        mainJsonObject.push_back(jsonObjectVirtuals);
    }

    QJsonDocument jsonDoc;
    jsonDoc.setArray(mainJsonObject);
    QByteArray data = jsonDoc.toJson();

    if( m_virtualMachine.count() > 0)  {
        QFile file("save.json");
        file.open(QIODevice::WriteOnly);
        file.write(data);
        file.close();
    }
}

void MainWindow::read() {
    QFile file("save.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString json = file.readAll();
    file.close();

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << err.errorString();
    } else {
        QJsonArray arr = jsonDoc.array();

        for(auto i : arr ) {
            qDebug() << "memory: " << i.toObject().value("memory").toDouble();
            std::shared_ptr<VirtualMachine> virtualMachine = std::make_shared<VirtualMachine>();
            virtualMachine->setName(i.toObject().value("name").toString());
            virtualMachine->setMemory(i.toObject().value("memory").toInt());
            virtualMachine->setType(i.toObject().value("type").toString());
            virtualMachine->setVersion(i.toObject().value("Version").toString());
            m_virtualMachine.push_back(virtualMachine);
            ui->listVirtuals->addItem(virtualMachine->getName());
        }

        qDebug() << m_virtualMachine.count();
    }
}

void MainWindow::on_settingsVirtual_clicked()
{
    test();
}
