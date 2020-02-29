#ifndef CHECKDATABASEWIDGET_H
#define CHECKDATABASEWIDGET_H

#include <QWidget>

namespace Ui {
class CheckDataBaseWidget;
}

class CheckDataBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckDataBaseWidget(QWidget *parent = nullptr);
    ~CheckDataBaseWidget();

private:
    Ui::CheckDataBaseWidget *ui;
};

#endif // CHECKDATABASEWIDGET_H
