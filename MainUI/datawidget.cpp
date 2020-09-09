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
//    qDebug()<<size->size().width()-ui->Img_After_label->width()-ui->Img_RightAfter_label->width()-ui->Img_RightFront_label->width();
//    qDebug()<<size->size().height()-ui->Img_After_label->height()-ui->Img_LeftAfter_label->height();

    if(size->oldSize().height()!=-1){
        int W=(size->size().width()-10) /3;/* 10 */
        int H=(size->size().height()-69)/2;/* 69 */
        if(W>0&&H>0){
            ui->Img_After_label->setFixedSize(W,H);
            ui->Img_After_label->size().scale(W,H,Qt::IgnoreAspectRatio);
            ui->Img_LeftAfter_label->setFixedSize(W,H);
            ui->Img_LeftAfter_label->size().scale(W,H,Qt::IgnoreAspectRatio);
            ui->Img_Front_label->setFixedSize(W,H);
            ui->Img_Front_label->size().scale(W,H,Qt::IgnoreAspectRatio);
            ui->Img_RightAfter_label->setFixedSize(W,H);
            ui->Img_RightAfter_label->size().scale(W,H,Qt::IgnoreAspectRatio);
            ui->Img_LeftFront_label->setFixedSize(W,H);
            ui->Img_LeftFront_label->size().scale(W,H,Qt::IgnoreAspectRatio);
            ui->Img_RightFront_label->setFixedSize(W,H);
            ui->Img_RightFront_label->size().scale(W,H,Qt::IgnoreAspectRatio);
        }
    }
}

void DataWidget::hideEvent(QHideEvent *event)
{
    //ui->tabWidget->setTabText(1,tr("Result"));
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

        ui->lineEdit_5->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_8->clear();

        ui->Infrared_logic_lineEdit->clear();


        ui->lineEdit->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_2->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_3->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_4->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");

        ui->lineEdit_5->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_7->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_9->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");
        ui->lineEdit_8->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 170, 0);");

        //ui->tabWidget->setTabText(1,tr("Result"));
        //ui->tab->setStyleSheet("color: #2c2c2c;");

        break;

    case 1:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_Front_label->width(),ui->Img_Front_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->Img_Front_label->setPixmap(labelPixFit);
        }
        break;
    case 2:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_RightFront_label->width(),ui->Img_RightFront_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->Img_RightFront_label->setPixmap(labelPixFit);
        }
        break;
    case 3:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_LeftFront_label->width(),ui->Img_LeftFront_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->Img_LeftFront_label->setPixmap(labelPixFit);
        }
        break;
    case 4:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_RightAfter_label->width(),ui->Img_RightAfter_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->Img_RightAfter_label->setPixmap(labelPixFit);
        }
        break;
    case 5:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_LeftAfter_label->width(),ui->Img_LeftAfter_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->Img_LeftAfter_label->setPixmap(labelPixFit);
        }
        break;
    case 6:
        if(labelPix!=nullptr){
            labelPixFit=labelPix->scaled(ui->Img_After_label->width(),ui->Img_After_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
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
    /* Tupe,集装箱类别:
     * -1 – 未知
     * 0 – 一个 20 集装箱
     * 1 – 一个 40 吋/45 吋集装箱
     * 2 – 两个 20 吋集装箱
     */

    ui->lineEdit->setText(result1);
    ui->lineEdit_2->setText(iso1);
    ui->lineEdit_3->setText(result2);
    ui->lineEdit_4->setText(iso2);

    ui->lineEdit_5->setText(result1);
    ui->lineEdit_7->setText(iso1);
    ui->lineEdit_9->setText(result2);
    ui->lineEdit_8->setText(iso2);

    if(resultCheck1){
        ui->lineEdit->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
        ui->lineEdit_5->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->lineEdit->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
        ui->lineEdit_5->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }
    if(type==2){
        if(resultCheck2){
            ui->lineEdit_3->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
            ui->lineEdit_9->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
        }
        else {
            ui->lineEdit_3->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
            ui->lineEdit_9->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
        }
    }

    QString logic="";
    ui->Infrared_logic_lineEdit->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");

    switch (type) {
    case -1:
        logic=tr("No container");
        break;
    case 0:
        logic=tr("A small container");
        break;
    case 1:
        logic=tr("A large container");
        break;
    case 2:
        logic=tr("Two small containersr");
        break;
    }
    ui->Infrared_logic_lineEdit->setText(logic);

    //ui->tabWidget->setTabText(1,tr("Front:%1 | Check1:%2 | IS01:%3 | Before:%4 | Check:%5 | ISO2:%6  | Type:%7  | Plate:%8").arg(result1).arg(resultCheck1).arg(iso1).arg(result2).arg(resultCheck2).arg(iso2).arg(logic).arg(""));
}

void DataWidget::camerIDstatesSlot(const QString &camerIP, bool state, const QString &alisa)
{
    if(alisa=="Front"){
        if(state){
            ui->Front_Camera_checkBox->setChecked(true);
        }
        else {
            ui->Front_Camera_checkBox->setChecked(false);
        }
    }
    else if(alisa=="After"){
        if(state){
            ui->After_Camera_checkBox->setChecked(true);
        }
        else {
            ui->After_Camera_checkBox->setChecked(false);
        }
    }
    else if(alisa=="Left"){
        if(state){
            ui->Left_Camera_checkBox->setChecked(true);
        }
        else {
            ui->Left_Camera_checkBox->setChecked(false);
        }
    }
    else if(alisa=="Right"){
        if(state){
            ui->Right_Camera_checkBox->setChecked(true);
        }
        else {
            ui->Right_Camera_checkBox->setChecked(false);
        }
    }
}

void DataWidget::imageFlowSlot(QByteArray img)
{
    QPixmap pix;
    pix.loadFromData(img);
    ui->label_3->setPixmap(pix);
}

void DataWidget::theVideoStreamSlot(QByteArray arrImg)
{    
    QPixmap pix;
    if(pix.loadFromData(arrImg)){
        ui->label_3->setPixmap(pix);
    }
    arrImg.clear();
}

void DataWidget::resultsTheLicensePlateSlot(const QString &plate, const QString &color, const QString &time, QByteArray arrImg)
{    
    ui->lineEdit_6->setText(plate);
    ui->lineEdit_11->setText(plate);
    ui->lineEdit_10->setText(plate);
    ui->lineEdit_12->setText(color);
    ui->lineEdit_13->setText(time);
    QPixmap pix;
    if(arrImg!=nullptr){
        pix.loadFromData(arrImg);
        ui->label_4->setPixmap(pix);
    }
}

void DataWidget::equipmentStateSlot(bool state)
{

}


void DataWidget::on_while_cycle_capture_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Capture_pushButton->setEnabled(false);
    }
    else {
        ui->Capture_pushButton->setEnabled(true);
    }
    emit simulateTriggerSignal(5);
}

void DataWidget::on_Capture_pushButton_clicked()
{
    switch (ui->Simulatiion_comboBox->currentIndex()) {
    case 0:
        emit simulateTriggerSignal(1);
        break;
    case 1:
        emit simulateTriggerSignal(2);
        break;
    case 2:
        emit simulateTriggerSignal(3);
        break;
    case 3:
        emit simulateTriggerSignal(4);
        break;
    case 4:
        emit simulateTriggerSignal(0);
        break;
    }
}

void DataWidget::on_pushButton_clicked()
{
    emit simulationCaptureSignal();
}

void DataWidget::on_pushButton_2_clicked(bool checked)
{
    emit openTheVideoSignal(checked);
}
