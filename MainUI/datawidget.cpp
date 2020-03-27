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
    QMutexLocker locker(&mutex);

    QPixmap *labelPix = new QPixmap();
    if(jpgStream!=nullptr){
        labelPix->loadFromData(jpgStream);        
    }
    else{/* 清除图片 */
        ui->label_13->clear();
        ui->label_6->clear();
        ui->label_2->clear();
        ui->label_5->clear();
        ui->label->clear();
        ui->label_4->clear();

        delete labelPix;
        labelPix=nullptr;
        return;
    }

    /* 防止图片发生偏移 */
    QPixmap  labelPixFit=labelPix->scaled(ui->label->size().width()-4,ui->label->size().height()-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    switch (imgNumber) {
    case 1:
            ui->label_13->setPixmap(labelPixFit);
        break;
    case 2:
            ui->label_6->setPixmap(labelPixFit);
        break;
    case 3:
            ui->label_2->setPixmap(labelPixFit);
        break;
    case 4:
        ui->label_5->setPixmap(labelPixFit);
        break;
    case 5:
            ui->label->setPixmap(labelPixFit);
        break;
    case 6:
            ui->label_4->setPixmap(labelPixFit);
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
