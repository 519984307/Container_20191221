#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>

namespace Ui {
class SystemSettingWidget;
}

class SystemSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSettingWidget(QWidget *parent = nullptr);
    ~SystemSettingWidget();

private:
    Ui::SystemSettingWidget *ui;
};

#endif // SYSTEMSETTING_H
