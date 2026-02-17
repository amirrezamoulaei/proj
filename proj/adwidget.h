#ifndef ADWIDGET_H
#define ADWIDGET_H

#include <QWidget>
#include "models.h"

namespace Ui {
class AdWidget;
}

class AdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdWidget(QWidget *parent = nullptr);
    void setAd(Ad* ad);
    ~AdWidget();

private:
    Ui::AdWidget *ui;
};

#endif // ADWIDGET_H
