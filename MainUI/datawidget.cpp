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
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::logicStatusSlot(int *status)
{
    /* A1.A2.D1.B1.B2.D2 */
    ui->checkBox_2->setChecked(status[0]);
    ui->checkBox_3->setChecked(status[1]);
    ui->checkBox_4->setChecked(status[3]);
    ui->checkBox_5->setChecked(status[4]);
    ui->checkBox_6->setChecked(status[2]);
}

void DataWidget::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber)
{
    QPixmap *labelPix = new QPixmap();
    if(jpgStream!=nullptr){
        labelPix->loadFromData(jpgStream);
    }

    switch (imgNumber) {
    case -1:
        ui->label_13->clear();
        ui->label_6->clear();
        ui->label_2->clear();
        ui->label_5->clear();
        ui->label->clear();
        ui->label_4->clear();
        break;
    case 1:
            ui->label_13->setPixmap(*labelPix);
        break;
    case 2:
            ui->label_6->setPixmap(*labelPix);
        break;
    case 3:
            ui->label_2->setPixmap(*labelPix);
        break;
    case 4:
        ui->label_5->setPixmap(*labelPix);
        break;
    case 5:
            ui->label->setPixmap(*labelPix);
        break;
    case 6:
            ui->label_4->setPixmap(*labelPix);
        break;
    }
    delete labelPix;
}

//void DataWidget::logicPutImageSlot(const int &putCommnd)
//{

//}
