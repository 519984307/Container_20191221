#ifndef CHECKDATABASEWIDGET_H
#define CHECKDATABASEWIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class CheckDataBaseWidget;
}

class CheckDataBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CheckDataBaseWidget(QWidget *parent = nullptr);
    ~CheckDataBaseWidget();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CheckDataBaseWidget *ui;
};

#endif // CHECKDATABASEWIDGET_H
