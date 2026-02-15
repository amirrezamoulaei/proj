#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "signupdialog.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    SignUpDialog dlg(this,&userManager);
    dlg.exec();
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    LoginDialog dlg(this,&userManager);
    dlg.exec();
}

