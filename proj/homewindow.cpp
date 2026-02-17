#include "homewindow.h"
#include "ui_homewindow.h"
#include "addaddialog.h"
#include "adViewerdialog.h"
#include "walletdialog.h"
#include "profiledialog.h"

HomeWindow::HomeWindow(QWidget *parent,KalaNetCore *um) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow),
    userManager(um)
{
    ui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_postButton_2_clicked()
{
    AddAdDialog dlg(this, userManager);
    dlg.exec();
}


void HomeWindow::on_viewButton_clicked()
{
    AdViewerDialog dlg(userManager, this);
    dlg.exec();
}


void HomeWindow::on_exitButton_6_clicked()
{
    this->close();
}


void HomeWindow::on_walletButton_4_clicked()
{
    WalletDialog dlg(userManager, this);
    dlg.exec();
}


void HomeWindow::on_profileButton_5_clicked()
{

    ProfileDialog dlg(userManager,this);
    dlg.exec();
}

