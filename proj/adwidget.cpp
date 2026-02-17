#include "adwidget.h"
#include "ui_adwidget.h"
#include <QPixmap>

AdWidget::AdWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdWidget)
{
    ui->setupUi(this);
}

AdWidget::~AdWidget()
{
    delete ui;
}

void AdWidget::setAd(Ad* ad){

    ui->titleLable->setText(
        QString::fromStdString(ad->getTitle()));
    ui->descLable->setText(
        QString::fromStdString(ad->getDescription()));
    ui->priceLable->setText(
        QString::number(ad->getPrice()));
    ui->categoryLabel->setText(
        QString::number((int)ad->getCategory()));


    QPixmap pix(
        QString::fromStdString(ad->getImagePath()));

    ui->imageLable->setPixmap(pix);
}
