#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>

namespace Ui {
class DataBaseWidget;
}

class DataBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataBaseWidget(QWidget *parent = nullptr);
    ~DataBaseWidget();

private:
    Ui::DataBaseWidget *ui;
};

#endif // DATABASEWIDGET_H
