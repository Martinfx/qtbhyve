#include "vnc.h"
#include "ui_vnc.h"

VNC::VNC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vnc)
{
    ui->setupUi(this);
    ui->vncView->connectToVncServer("127.0.0.1","");
    ui->vncView->startFrameBufferUpdate();
    qDebug() << ui->vncView->isConnectedToServer();
}

VNC::~VNC()
{
    ui->vncView->disconnectFromVncServer();
    delete ui;
}
