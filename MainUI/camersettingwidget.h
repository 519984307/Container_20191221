#ifndef CAMERSETTING_H
#define CAMERSETTING_H

#include <QWidget>

namespace Ui {
class CamerSettingWidget;
}

class CamerSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CamerSettingWidget(QWidget *parent = nullptr);
    ~CamerSettingWidget();

private:
    Ui::CamerSettingWidget *ui;
};

#endif // CAMERSETTING_H
