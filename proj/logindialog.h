#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "QString"
#include <QDialog>
#include "kalanetcore.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr,KalaNetCore *userManager = nullptr);
    void generateCaptcha();
    ~LoginDialog();

private slots:
    void on_pushButton_clicked();

    void on_refreshCaptcha_clicked();

private:
    Ui::LoginDialog *ui;
    KalaNetCore *userManager;
    QString currentCaptcha;
};

#endif // LOGINDIALOG_H
