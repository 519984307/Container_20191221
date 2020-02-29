#include "camersettingwidget.h"
#include "ui_camersettingwidget.h"

CamerSettingWidget::CamerSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CamerSettingWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

CamerSettingWidget::~CamerSettingWidget()
{
    delete ui;
}
