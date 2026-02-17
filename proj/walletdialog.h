#ifndef WALLETDIALOG_H
#define WALLETDIALOG_H

#include <QDialog>
#include "kalanetcore.h"

namespace Ui {
class WalletDialog;
}

class WalletDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WalletDialog(KalaNetCore *core, QWidget *parent = nullptr);
    ~WalletDialog();

private slots:
    void on_refreshCaptcha_clicked();

    void on_reciveButton_clicked();

private:
    void generateCaptcha();

    Ui::WalletDialog *ui;
    KalaNetCore* core;
    QString currentCaptcha;
};

#endif // WALLETDIALOG_H
