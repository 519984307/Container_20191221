#include "datawidget.h"
#include "ui_datawidget.h"

DataWidget::DataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    emit startSlave("com1","com2");
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::camerIDstates(const QString &camerIP, bool state)
{
}

void DataWidget::pictureStream(const QByteArray &jpgStream, const QString &camerIP)
{
    QPixmap *map = new QPixmap();
    map->loadFromData(jpgStream);
    //ui->label->setPixmap(*map);

    delete map;
}

void DataWidget::logicStatus(int *status)
{

}

void DataWidget::logicPutImage(int putCommnd)
{

}
