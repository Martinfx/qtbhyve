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
    //m_dialog->setToolTipsVisible(true);
    m_dialog->show();

   if(!m_dialog->getVirtualMachine()->getType().isEmpty()) {
        m_virtualMachine.push_back(m_dialog->getVirtualMachine());
    }
}

void MainWindow::test() {
    int counter = 0;
    for(auto i : m_virtualMachine) {
        qDebug() << counter ;
        qDebug() << "Version: " << i->getVersion();
        qDebug() << "Type: "    << i->getType();
        qDebug() << "Name: "    << i->getName();
        qDebug() << "Memory: "  << i->getMemory();
        qDebug() << "Ncpu: "    << i->getCpu();
        counter++;
    }
}

void MainWindow::on_listVirtuals_itemClicked(QListWidgetItem *item)
{
    for(auto i : m_virtualMachine) {
        if(item->text() == i->getName()) {
            qDebug() << "---------------";
            qDebug() << "Version: " << i->getVersion();
            qDebug() << "Type: "    << i->getType();
            qDebug() << "Name: "    << i->getName();
            qDebug() << "Memory: "  << i->getMemory();
            qDebug() << "Ncpu: "    << i->getCpu();
        }
    }
}

void MainWindow::write() {
    QJsonArray mainJsonArray;
    QJsonObject jsonObjectVirtuals;
    int counter = 0;
    for(auto iter : m_virtualMachine) {
        jsonObjectVirtuals.insert("virtual", QJsonValue( counter++));
        jsonObjectVirtuals.insert("memory", QJsonValue(iter->getMemory()));
        jsonObjectVirtuals.insert("type", QJsonValue(iter->getType()));
        jsonObjectVirtuals.insert("name", QJsonValue(iter->getName()));
        jsonObjectVirtuals.insert("version", QJsonValue(iter->getVersion()));
        jsonObjectVirtuals.insert("ncpu", QJsonValue(iter->getCpu()));
        mainJsonArray.push_back(jsonObjectVirtuals);
    }

    QJsonDocument jsonDoc;
    jsonDoc.setArray(mainJsonArray);
    QByteArray data = jsonDoc.toJson();

    if( m_virtualMachine.count() > 0)  {
        QFile file("save.json");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
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
        qDebug() << "Read json failed: " << err.errorString();
    } else {
        QJsonArray jsonArray = jsonDoc.array();

        for(auto iter : jsonArray ) {
            qDebug() << "memory: " << iter.toObject().value("memory").toDouble();
            std::shared_ptr<VirtualMachine> virtualMachine = std::make_shared<VirtualMachine>();
            virtualMachine->setName(iter.toObject().value("name").toString());
            virtualMachine->setMemory(iter.toObject().value("memory").toInt());
            virtualMachine->setType(iter.toObject().value("type").toString());
            virtualMachine->setVersion(iter.toObject().value("version").toString());
            virtualMachine->setCpu(iter.toObject().value("ncpu").toInt());
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
