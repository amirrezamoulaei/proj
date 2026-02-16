#include "homewindow.h"
#include "ui_homewindow.h"
#include "addaddialog.h"

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

