#ifndef ADDADDIALOG_H
#define ADDADDIALOG_H

#include <QDialog>
#include "kalanetcore.h"

namespace Ui {
class AddAdDialog;
}

class AddAdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAdDialog(QWidget *parent = nullptr, KalaNetCore *userManager = nullptr);
    ~AddAdDialog();

private slots:
    void on_addAdpushButton_clicked();

    void on_SelectImagePushButton_clicked();

private:
    Ui::AddAdDialog *ui;
    KalaNetCore *userManager;
    QString qimagePath;
};

#endif // ADDADDIALOG_H
