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

void ServiceWidget::messageSlot(const QString &type, const QString &msg)
{
    ui->plainTextEdit->appendPlainText(tr("[%1] [%2]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg));
}
