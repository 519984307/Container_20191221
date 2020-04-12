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
//    if(ui->plainTextEdit->blockCount()>300){
//        ui->plainTextEdit->clear();
//    }
    ui->plainTextEdit->appendPlainText(msg);
}
