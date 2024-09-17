#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    mSocket = new QUdpSocket(this);

    //绑定接收消息信号
    connect(mSocket, &QUdpSocket::readyRead, this, [this](){
        char str[1024] = {0};
        mSocket->readDatagram(str, sizeof str); //读取消息

        ui->textEdit->append(str);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString ip = ui->ip->text();
    int port = ui->port->text().toInt();

    QString str = ui->sendEdit->text();

    // 单播 1对1 指定IP
    mSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);
}


//绑定端口
void MainWindow::on_pushButton_2_clicked()
{
    int port = ui->port->text().toInt();
    bool flag = mSocket->bind(port);
    if(true){
        QMessageBox::information(this, "tips", "绑定端口成功");
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
    }else{
        QMessageBox::information(this, "tips", "绑定端口失败");
    }
}

