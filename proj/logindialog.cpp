#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
#include "QRandomGenerator"

LoginDialog::LoginDialog(QWidget *parent,KalaNetCore *um)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    ,userManager(um)
{
    ui->setupUi(this);
    generateCaptcha();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    std::string username = ui->usernameLineEdit->text().toStdString();
    std::string password = ui->passwordLineEdit->text().toStdString();

    if(ui->captchaLineEdit->text()!=currentCaptcha){
        QMessageBox::warning(this,"Error","Captcha incorrect");
        generateCaptcha();
        return;
    }
    try{
        userManager->login(username, password);
        QMessageBox::information(this,"Success","Login successful");
        accept();
    }
    catch(const std::exception &e){
        QMessageBox::critical(this,"Error",e.what());
        generateCaptcha();
    }

}
void LoginDialog::generateCaptcha(){
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    currentCaptcha.clear();
    for(int i=0; i<6 ; i++){
        int index = QRandomGenerator::global()->bounded(chars.length());
        currentCaptcha += chars[index];
    }
    ui->captchaLabel->setText(currentCaptcha);
}

void LoginDialog::on_refreshCaptcha_clicked()
{
    generateCaptcha();
}

