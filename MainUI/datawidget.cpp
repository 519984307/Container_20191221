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

void DataWidget::resizeEvent(QResizeEvent *size)
{       
    ui->Img_After_label->setMinimumWidth(size->size().width()/3-4);
    ui->Img_After_label->setMinimumHeight(size->size().height()/2-36);
}

//void DataWidget::InitializationParameterSlot(int channel)
//{
//    this->channel=channel;
//}

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
    if(imgNumber==0){
        return;
    }
    QMutexLocker locker(&mutex);
    QPixmap *labelPix = new QPixmap();
    QPixmap  labelPixFit;
    if(jpgStream!=nullptr){
        labelPix->loadFromData(jpgStream);
        /* 防止图片发生偏移 */
        //labelPixFit=labelPix->scaled((ui->tab->width()-4)/3-4,(ui->tab->height()-36)/2-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        labelPixFit=labelPix->scaled(ui->Img_Front_label->width()-4,ui->Img_Front_label->height()-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
    else{
        delete labelPix;
        labelPix=nullptr;
    }

    switch (imgNumber) {
    case -1:
        /* 清除图片 */
        ui->Img_Front_label->clear();
        ui->Img_LeftFront_label->clear();
        ui->Img_RightFront_label->clear();
        ui->Img_LeftAfter_label->clear();
        ui->Img_RightAfter_label->clear();
        ui->Img_After_label->clear();

        /* 清除箱号结果 */
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        break;
    case 1:
        if(labelPix!=nullptr){
            ui->Img_Front_label->setPixmap(labelPixFit);
        }
        break;
    case 2:
        if(labelPix!=nullptr){
            ui->Img_LeftFront_label->setPixmap(labelPixFit);
        }
        break;
    case 3:
        if(labelPix!=nullptr){
            ui->Img_RightFront_label->setPixmap(labelPixFit);
        }
        break;
    case 4:
        if(labelPix!=nullptr){
            ui->Img_LeftAfter_label->setPixmap(labelPixFit);
        }
        break;
    case 5:
        if(labelPix!=nullptr){
            ui->Img_RightAfter_label->setPixmap(labelPixFit);
        }
        break;
    case 6:
        if(labelPix!=nullptr){
            ui->Img_After_label->setPixmap(labelPixFit);
        }
        break;
    }

    if(labelPix!=nullptr){
        delete labelPix;
        labelPix=nullptr;
    }
}

void DataWidget::containerSlot(const int& type,const QString &result1,const int& resultCheck1,const QString &iso1,const QString &result2,const int& resultCheck2,const QString &iso2)
{
    ui->lineEdit->setText(result1);
    ui->lineEdit_2->setText(iso1);
    ui->lineEdit_3->setText(result2);
    ui->lineEdit_4->setText(iso2);

    if(resultCheck1){
        ui->lineEdit->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->lineEdit->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }
    if(type==3){
        if(resultCheck2){
            ui->lineEdit_3->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
        }
        else {
            ui->lineEdit_3->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
        }
    }
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
