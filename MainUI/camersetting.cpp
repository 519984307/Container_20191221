#include "camersetting.h"
#include "ui_camersetting.h"

CamerSetting::CamerSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamerSetting)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

CamerSetting::~CamerSetting()
{
    delete ui;
}
