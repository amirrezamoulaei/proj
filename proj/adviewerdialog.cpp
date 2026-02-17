#include "adviewerdialog.h"
#include "ui_adviewerdialog.h"
#include "adWidget.h"

AdViewerDialog::AdViewerDialog(KalaNetCore* c,
                               QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdViewerDialog)
    , core(c)
{
    ui->setupUi(this);
    displayAds();
}

AdViewerDialog::~AdViewerDialog()
{
    delete ui;
}

void AdViewerDialog::displayAds(){
    ui->adsListWidget->clear();

    auto ads = core->getAvailableAds();

    for(Ad* ad : ads){

        QListWidgetItem* item =
            new QListWidgetItem(ui->adsListWidget);

        AdWidget* widget = new AdWidget;
        widget->setAd(ad);

        item->setSizeHint(widget->sizeHint());

        ui->adsListWidget->addItem(item);
        ui->adsListWidget->setItemWidget(item, widget);
    }

}
