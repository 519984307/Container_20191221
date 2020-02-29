#include "systemsettingwidget.h"
#include "ui_systemsettingwidget.h"

SystemSettingWidget::SystemSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

SystemSettingWidget::~SystemSettingWidget()
{
    delete ui;
}

//Setting setting;
//setting.pSetting->beginGroup(tr("MAIN"));
//setting.pSetting->setValue(tr("ChannelNumber"),QVariant(ui->spinBox->value()));
//setting.pSetting->endGroup();
//ui->spinBox->setValue(setting.pSetting->value(tr("ChannelNumber")).toInt());
