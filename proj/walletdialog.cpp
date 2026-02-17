#include "walletdialog.h"
#include "ui_walletdialog.h"
#include <QRandomGenerator>
#include <QMessageBox>

WalletDialog::WalletDialog(KalaNetCore *c,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WalletDialog)
    ,core(c)
{
    ui->setupUi(this);

    ui->balanceLable->setText(
        "Balance: "+ QString::number(core->getLoggedInUser()->getBalance()));
    generateCaptcha();
}

WalletDialog::~WalletDialog()
{
    delete ui;
}

void WalletDialog::generateCaptcha(){
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    currentCaptcha.clear();
    for(int i=0; i<6 ; i++){
        int index = QRandomGenerator::global()->bounded(chars.length());
        currentCaptcha += chars[index];
    }
    ui->captchaLable->setText(currentCaptcha);
}
void WalletDialog::on_refreshCaptcha_clicked()
{
    generateCaptcha();
}


void WalletDialog::on_reciveButton_clicked()
{
    QString enteredCaptcha = ui->captchaEdit->text();

    if(enteredCaptcha != currentCaptcha){
        QMessageBox::warning(this, "Error", "CAPTCHA is incorrect!");
        generateCaptcha();
        return;
    }

    bool ok;
    int amount = ui->amountEdit->text().toInt(&ok);
    if(!ok || amount <= 0){
        QMessageBox::warning(this, "Error", "Invalid amount!");
        return;
    }

    core->getLoggedInUser()->deposit(amount);

    ui->balanceLable->setText(
        "Balance: "+ QString::number(core->getLoggedInUser()->getBalance()));

    QMessageBox::information(this, "Success", "Balance updated!");

    ui->amountEdit->clear();
    ui->captchaEdit->clear();
    generateCaptcha();
}

