#include "picturewidget.h"
#include "ui_picturewidget.h"

PictureWidget::PictureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PictureWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

PictureWidget::~PictureWidget()
{
    delete ui;
}

void PictureWidget::resizeEvent(QResizeEvent *size)
{
    emit resizeEventSignal();
}

void PictureWidget::on_pushButton_2_clicked()
{
    emit playStreamSignal(static_cast<uint>(ui->label->winId()) ,true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
}

void PictureWidget::on_pushButton_3_clicked()
{
    emit playStreamSignal(static_cast<uint>(ui->label->winId()) ,false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
}

void PictureWidget::on_pushButton_clicked()
{
    ///先关闭流
    emit on_pushButton_3_clicked();
    emit putCommandSignal();
}

void PictureWidget::on_pushButton_4_clicked()
{
    ui->label->clear();
}

void PictureWidget::pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber)
{
    if(imgNumber==0){
        if(jpgStream!=nullptr){
            QPixmap *labelPix = new QPixmap();
            labelPix->loadFromData(jpgStream);
            ui->label->setPixmap(*labelPix);
            delete labelPix;
            labelPix=nullptr;
        }
    }
}
