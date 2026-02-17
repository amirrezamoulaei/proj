#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include "models.h"
#include "kalanetcore.h"

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(KalaNetCore* core, QWidget *parent = nullptr);
    ~ProfileDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProfileDialog *ui;
    KalaNetCore* core;
};

#endif // PROFILEDIALOG_H
