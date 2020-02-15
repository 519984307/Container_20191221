#include "systemsetting.h"
#include "ui_systemsetting.h"

SystemSetting::SystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSetting)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

SystemSetting::~SystemSetting()
{
    delete ui;
}

//Setting setting;
//setting.pSetting->beginGroup(tr("MAIN"));
//setting.pSetting->setValue(tr("ChannelNumber"),QVariant(ui->spinBox->value()));
//setting.pSetting->endGroup();
//ui->spinBox->setValue(setting.pSetting->value(tr("ChannelNumber")).toInt());
