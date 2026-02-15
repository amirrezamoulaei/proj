#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "kalanetcore.h"
#include "QMessageBox"


namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr,KalaNetCore *userManager = nullptr);
    ~SignUpDialog();

private slots:
    void on_Confirm_clicked();

private:
    Ui::SignUpDialog *ui;
    KalaNetCore *userManager;
};

#endif // SIGNUPDIALOG_H
