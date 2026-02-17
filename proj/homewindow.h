#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "kalanetcore.h"

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr,KalaNetCore *userManager = nullptr);
    ~HomeWindow();

private slots:
    void on_postButton_2_clicked();

    void on_viewButton_clicked();

    void on_exitButton_6_clicked();

    void on_walletButton_4_clicked();

    void on_profileButton_5_clicked();

private:
    Ui::HomeWindow *ui;
    KalaNetCore *userManager;
};

#endif // HOMEWINDOW_H
