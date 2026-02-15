#include "signupdialog.h"
#include "ui_signupdialog.h"
SignUpDialog::SignUpDialog(QWidget *parent,KalaNetCore *um)
    : QDialog(parent)
    , ui(new Ui::SignUpDialog)
    ,userManager(um)
{
    ui->setupUi(this);
}



SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_Confirm_clicked()
{

    std::string username = ui->lineEditUserName->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();
    std::string name = ui->lineEditName->text().toStdString();
    std::string phone = ui->lineEditPhone->text().toStdString();
    std::string email = ui->lineEditEmail->text().toStdString();

    try{
        userManager->signup(username,password,name,phone,email);
        QMessageBox::information(this,"You have successfully registered","Successful registration!");
        accept();
    }
    catch(const std::exception &e){
        QMessageBox::critical(this,"Error",e.what());
    }
}

