#include "addaddialog.h"
#include "ui_addaddialog.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "QMessageBox"

AddAdDialog::AddAdDialog(QWidget *parent,KalaNetCore *um)
    : QDialog(parent)
    , ui(new Ui::AddAdDialog)
    ,userManager(um)
{
    ui->setupUi(this);
}

AddAdDialog::~AddAdDialog()
{
    delete ui;
}

void AddAdDialog::on_addAdpushButton_clicked()
{
    try{
        std::string title = ui->titleLineEdit->text().toStdString();
        std::string desc = ui->descTextEdit->toPlainText().toStdString();
        double price = ui->priceLineEdit_3->text().toDouble();
        Category cat = static_cast<Category>(ui->categoryComboBox->currentIndex());
        std::string imagePath = qimagePath.toStdString();

        userManager->postAd(title, desc, price, cat, imagePath);
        QMessageBox::information(this, "Success", "Ad posted.");
        accept();
    }
    catch(const std::exception &e){
        QMessageBox::critical(this, "Error", e.what());
    }
}


void AddAdDialog::on_SelectImagePushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Select Image",
        "",
        "Image(*.png *.jpg *.jpeg)"
        );
    if(!path.isEmpty()){
        QDir dir(QDir::currentPath());
        if(!dir.exists()){
            dir.mkdir("images");
        }

        QString fileName = QFileInfo(path).fileName();
        QString dest = QDir::currentPath() + "/images/" + fileName;

        QFile::remove(dest);
        QFile::copy(path,dest);

        qimagePath = dest;
        ui->pathLabel_7->setText(fileName);
    }
}

