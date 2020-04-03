#include "datawidget.h"
#include "ui_datawidget.h"

DataWidget::DataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataWidget)
{
    ui->setupUi(this);

    init=true;

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);    
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::resizeEvent(QResizeEvent *size)
{   
    if(!init){
        ui->Img_After_label->setMinimumWidth(ui->Img_Front_label->size().width());
    }
    init=false;
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
    QMutexLocker locker(&mutex);
    QPixmap *labelPix = new QPixmap();
    if(jpgStream!=nullptr){
        labelPix->loadFromData(jpgStream);
    }
    else{/* 清除图片 */
        ui->Img_Front_label->clear();
        ui->Img_LeftFront_label->clear();
        ui->Img_RightFront_label->clear();
        ui->Img_LeftAfter_label->clear();
        ui->Img_RightAfter_label->clear();
        ui->Img_After_label->clear();

        delete labelPix;
        labelPix=nullptr;
        return;
    }

    /* 防止图片发生偏移 */
    QSize size=ui->Img_Front_label->size();
    QPixmap  labelPixFit=labelPix->scaled(size.width()-4,size.height()-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    switch (imgNumber) {
    case 1:
            ui->Img_Front_label->setPixmap(labelPixFit);
        break;
    case 2:
            ui->Img_LeftFront_label->setPixmap(labelPixFit);
        break;
    case 3:
            ui->Img_RightFront_label->setPixmap(labelPixFit);
        break;
    case 4:
        ui->Img_LeftAfter_label->setPixmap(labelPixFit);
        break;
    case 5:
            ui->Img_RightAfter_label->setPixmap(labelPixFit);
        break;
    case 6:
            ui->Img_After_label->setPixmap(labelPixFit);
        break;
    }

    delete labelPix;
    labelPix=nullptr;
}

void DataWidget::on_test_22_pushButton_clicked()
{
    emit simulateTriggerSignal(1);
}

void DataWidget::on_test_45_pushButton_clicked()
{
    emit simulateTriggerSignal(2);
}

void DataWidget::on_test_double_22_front_pushButton_clicked()
{
    emit simulateTriggerSignal(3);
}

void DataWidget::on_test_double_22_before_pushButton_clicked()
{
    emit simulateTriggerSignal(4);
}

void DataWidget::on_clearn_image_pushButton_clicked()
{
    emit simulateTriggerSignal(0);
}

void DataWidget::on_while_cycle_capture_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->test_22_pushButton->setEnabled(false);
        ui->test_45_pushButton->setEnabled(false);
        ui->test_double_22_front_pushButton->setEnabled(false);
        ui->test_double_22_before_pushButton->setEnabled(false);
    }
    else {
        ui->test_22_pushButton->setEnabled(true);
        ui->test_45_pushButton->setEnabled(true);
        ui->test_double_22_front_pushButton->setEnabled(true);
        ui->test_double_22_before_pushButton->setEnabled(true);
    }
    emit simulateTriggerSignal(5);
}
