#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QWidget>

namespace Ui {
class ServiceWidget;
}

class ServiceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceWidget(QWidget *parent = nullptr);
    ~ServiceWidget();

private:
    Ui::ServiceWidget *ui;
};

#endif // SERVICEWIDGET_H
