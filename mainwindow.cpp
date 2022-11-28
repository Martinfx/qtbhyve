#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    read();

    /// avoid empty index
    ui->listVirtuals->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    /// XXX:
    /// Remove virtual with empty name
    QList<QListWidgetItem*> items  = ui->listVirtuals->findItems("", Qt::MatchFixedString);
    foreach(QListWidgetItem * item, items) {
        if(item->text().isEmpty()) {
            //delete ui->listVirtuals->takeItem(ui->listVirtuals->row(item));
            ui->listVirtuals->removeItemWidget(item);
            delete item;
        }
    }

    write();

    qDeleteAll(m_virtualMachine);
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

    //if(!m_dialog->getVirtualMachine()->getVersion().isEmpty()) {
        m_virtualMachine.push_back(m_dialog->getVirtualMachine());
    //}

    //qDebug() << "Test: " << m_dialog->getVirtualMachine()->getCpu();
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
        /*    qDebug() << "---------------";
            qDebug() << "Version: " << i->getVersion();
            qDebug() << "Type: "    << i->getType();
            qDebug() << "Name: "    << i->getName();
            qDebug() << "Memory: "  << i->getMemory();
            qDebug() << "Ncpu: "    << i->getCpu();
            qDebug() << "hostbridge: " << i->getHostbridge();
            qDebug() << "ahcicd: "    << i->getAhcicd();
            qDebug() << "ahcihd: "    << i->getAhcihd();
            qDebug() << "virtio: "  << i->getVirtio();
            qDebug() << "ip: "    << i->getIp();*/

            ui->labelName->setText(i->getName());
            ui->labelVersion->setText(i->getVersion());
            ui->labelType->setText(i->getType());
            ui->labelMemory->setText(QString::number(i->getMemory()));
            ui->labelCpu->setText(QString::number(i->getCpu()));
            ui->labelHostBridge->setText(i->getHostbridge());
            ui->labelAhcihd->setText(i->getAhcihd());
            ui->labelAhcicd->setText(i->getAhcicd());
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
        jsonObjectVirtuals.insert("hostbridge", QJsonValue(iter->getHostbridge()));
        jsonObjectVirtuals.insert("ahcicd", QJsonValue(iter->getAhcicd()));
        jsonObjectVirtuals.insert("ahcihd", QJsonValue(iter->getAhcihd()));
        jsonObjectVirtuals.insert("virtio", QJsonValue(iter->getVirtio()));
        jsonObjectVirtuals.insert("ifconfigname", QJsonValue(iter->getIfconfigName()));
        jsonObjectVirtuals.insert("ip", QJsonValue(iter->getIp()));
        jsonObjectVirtuals.insert("height", QJsonValue(iter->getHeight()));
        jsonObjectVirtuals.insert("width", QJsonValue(iter->getWidth()));
        jsonObjectVirtuals.insert("xhci", QJsonValue(iter->getXhci()));
        jsonObjectVirtuals.insert("tablet", QJsonValue(iter->getTablet()));
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
    if(!file.exists()) {
        QFile file2;
        file2.setFileName("save.json");
        file2.open(QIODevice::WriteOnly);
        file2.close();
    }

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
            VirtualMachine* virtualMachine = new VirtualMachine();
            virtualMachine->setName(iter.toObject().value("name").toString());
            virtualMachine->setMemory(iter.toObject().value("memory").toInt());
            virtualMachine->setType(iter.toObject().value("type").toString());
            virtualMachine->setVersion(iter.toObject().value("version").toString());
            virtualMachine->setCpu(iter.toObject().value("ncpu").toInt());
            virtualMachine->setHostbridge(iter.toObject().value("hostbridge").toString());
            virtualMachine->setAhcicd(iter.toObject().value("ahcicd").toString());
            virtualMachine->setAhcihd(iter.toObject().value("ahcihd").toString());
            virtualMachine->setVirtio(iter.toObject().value("virtio").toString());
            virtualMachine->setIfconfigName(iter.toObject().value("ifconfigname").toString());
            virtualMachine->setIp(iter.toObject().value("ip").toString());
            virtualMachine->setHeight(iter.toObject().value("height").toInt());
            virtualMachine->setWidth(iter.toObject().value("width").toInt());
            virtualMachine->setXhci(iter.toObject().value("xhci").toString());
            virtualMachine->setTablet(iter.toObject().value("tablet").toString());

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

void MainWindow::on_deleteVirtual_clicked()
{
    if(m_selectedItem != -1 && m_selectedItem <= m_virtualMachine.count()) {
        qDebug() << "m_selectedItem: " << m_selectedItem;
        QListWidgetItem *item = ui->listVirtuals->takeItem(m_selectedItem);
        qDebug() << "item->text(): " << item->text();
        m_virtualMachine.removeAt(m_selectedItem);
        qDebug() << "m_virtualMachine.count(): " << m_virtualMachine.count();
        delete item;
    }
}


void MainWindow::on_listVirtuals_currentRowChanged(int currentRow)
{
    qDebug() << "m_selectedItem: " << m_selectedItem;
    m_selectedItem = currentRow;
}

void MainWindow::on_listVirtuals_itemDoubleClicked(QListWidgetItem *item)
{
    /*for(auto items : m_virtualMachine) {
        if(item->text() ==  items->getName()) {
            qDebug() << items->getName();

            QProcess process;
            process.setProgram("bhyve");
            Q_PID pid = process.pid();
            process.waitForStarted();
            process.close();
        }
    }*/
}


void MainWindow::on_playVirtual_clicked()
{
    //qDebug() << ui->listVirtuals->currentItem()->text();
    for(auto items : m_virtualMachine) {
        if(ui->listVirtuals->currentItem()->text() ==  items->getName()) {
            qDebug() << "Play!" << items->getName();

            /*QString list;
            list = "-s 0, " + items->getHostbridge()
                          //<< " -s 3, " << items->getAhcicd()
                          + " -s 4, ./" + items->getAhcihd()
                          + " -s 5, " + items->getVirtio() + " " + items->getIfconfigName()
                          + " -s 29, fbuf, tcp=" + items->getIp()
                          + ",w=" + QString::number(items->getWidth())
                          + ",h=" + QString::number(items->getHeight()) + ",wait"
                          + " -s 31,lpc -l com1,stdio"
                          + " -l bootrom,/usr/local/share/uefi-firmware/BHYVE_UEFI.fd \
                uefivm";

            qDebug() << "list: " << list;*/
            QProcess process;
            process.setProgram("/usr/sbin/bhyve");
            process.setArguments( QStringList() << "-s 0, " << items->getHostbridge()
                                                 << " -s 3, " << items->getAhcicd()
                                                 << " -s 4, ." << items->getAhcihd()
                                                 << " -s 5, " << items->getVirtio() << " " << items->getIfconfigName()
                                                 << " -s 29, fbuf, tcp="<< items->getIp()
                                                 << ",w="<< QString::number(items->getWidth())
                                                 << ",h=" << QString::number(items->getHeight()) <<",wait"
                                                 << " -s 31,lpc -l com1,stdio"
                                                 << " -l bootrom,/usr/local/share/uefi-firmware/BHYVE_UEFI.fd uefivm"
                          );


            if ( process.exitCode() != 0 )
            {
                qCritical() << "Exit Code: " << process.exitCode();
                //return -1;
            }


            process.start();
            pid = process.processId();
            process.waitForFinished();
            //qDebug() << process.systemEnvironment();
            qDebug() << process.readAllStandardError();
            qDebug() << process.readAllStandardOutput();
            process.close();
        }
    }
}

