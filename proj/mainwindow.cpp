#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "signupdialog.h"
#include "logindialog.h"
#include "homewindow.h"

MainWindow::MainWindow(KalaNetCore* c, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , core(c)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 1234);
    connect(socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected to server ✅";
    });

    connect(socket, &QTcpSocket::readyRead, this, [this](){
        QByteArray data = socket->readAll();
        qDebug() << "Server says:" << data;
    });

    connect(socket, &QTcpSocket::disconnected, this, [](){
        qDebug() << "Disconnected ❌";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    SignUpDialog dlg(this,core);
    dlg.exec();
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    LoginDialog dlg(this,core);
    if(dlg.exec() == QDialog::Accepted){
        this->hide();

        HomeWindow *home = new HomeWindow(nullptr,core);
        home->show();
    }
    socket->write("Hello Server");
}

