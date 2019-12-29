#include "servicewidget.h"
#include "ui_servicewidget.h"

ServiceWidget::ServiceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

ServiceWidget::~ServiceWidget()
{
    delete ui;
}
