#ifndef CAMERSETTING_H
#define CAMERSETTING_H

#include <QWidget>

namespace Ui {
class ChannelSettingWidget;
}

class ChannelSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelSettingWidget(QWidget *parent = nullptr);
    ~ChannelSettingWidget();

private:
    Ui::ChannelSettingWidget *ui;
};

#endif // CAMERSETTING_H
