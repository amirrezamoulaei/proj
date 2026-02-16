#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "signupdialog.h"
#include "logindialog.h"
#include "homewindow.h"

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
    if(dlg.exec() == QDialog::Accepted){
        this->hide();

        HomeWindow *home = new HomeWindow(nullptr,&userManager);
        home->show();
    }
}

