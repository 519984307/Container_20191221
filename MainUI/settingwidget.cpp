#include "settingwidget.h"
#include "ui_settingwidget.h"

#include "setting.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::writeINI()
{
    Setting setting;
    setting.pSetting->beginGroup(tr("MAIN"));
    setting.pSetting->setValue(tr("ChannelNumber"),QVariant(ui->spinBox->value()));
    setting.pSetting->endGroup();
}

void SettingWidget::readINI()
{
    Setting setting;
    ui->spinBox->setValue(setting.pSetting->value(tr("ChannelNumber")).toInt());
}
