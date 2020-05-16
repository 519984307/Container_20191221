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

    ui->label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");

    countTcp=0;
}

ServiceWidget::~ServiceWidget()
{
    delete ui;
}

void ServiceWidget::resultsAnalysisStateSlot(const int &channel, const QString &msg)
{
    ui->plainTextEdit->appendPlainText(tr("[%1] %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg));
}

void ServiceWidget::socketConnectCountSlot(int count)
{
    countTcp+=count;
    if(countTcp>0){
        ui->label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }
    ui->Socket_lcdNumber->display(countTcp);
}
