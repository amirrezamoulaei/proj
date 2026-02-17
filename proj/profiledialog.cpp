#include "profiledialog.h"
#include "ui_profiledialog.h"
#include <QMessageBox>

ProfileDialog::ProfileDialog(KalaNetCore* c, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProfileDialog)
    ,core(c)
{
    ui->setupUi(this);
    ui->nameEdit->setText(QString::fromStdString(core->getLoggedInUser()->getFullName()));
    ui->emailEdit->setText(QString::fromStdString(core->getLoggedInUser()->getEmail()));
    ui->passwordEdit->setText(QString::fromStdString(core->getLoggedInUser()->getPass()));
    ui->userNameEdit->setText(QString::fromStdString(core->getLoggedInUser()->getUsername()));
    ui->phoneEdit->setText(QString::fromStdString(core->getLoggedInUser()->getPhone()));
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}



void ProfileDialog::on_pushButton_clicked()
{
    if(ui->nameEdit->text().isEmpty()||
        ui->userNameEdit->text().isEmpty()||
        ui->passwordEdit->text().isEmpty()){
        QMessageBox::warning(this, "Error", "Fild can't be empty!");
        return;
    }

    core->getLoggedInUser()->setName(ui->nameEdit->text().toStdString());
    core->getLoggedInUser()->setUsername(ui->userNameEdit->text().toStdString());
    core->getLoggedInUser()->setPassword(ui->passwordEdit->text().toStdString());
    core->getLoggedInUser()->setEmail(ui->emailEdit->text().toStdString());
    core->getLoggedInUser()->setPhone(ui->phoneEdit->text().toStdString());

    QMessageBox::information(this, "success", "Profile updated!");

}

