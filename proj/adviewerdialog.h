#ifndef ADVIEWERDIALOG_H
#define ADVIEWERDIALOG_H

#include <QDialog>
#include "kalanetcore.h"

namespace Ui {
class AdViewerDialog;
}

class AdViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdViewerDialog(KalaNetCore* core,
                            QWidget *parent = nullptr);
    ~AdViewerDialog();
    void displayAds();

private:
    Ui::AdViewerDialog *ui;
    KalaNetCore* core;
};

#endif // ADVIEWERDIALOG_H
