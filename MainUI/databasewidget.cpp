#include "databasewidget.h"
#include "ui_databasewidget.h"

DataBaseWidget::DataBaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBaseWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);        

    ui->DateTime_Statrt_dateTimeEdit->setDate(QDate::currentDate());
    ui->DateTime_Statrt_dateTimeEdit->setTime(QTime(0,0,0));

    ui->DataTime_End_dateTimeEdit->setDate(QDate::currentDate());
    ui->DataTime_End_dateTimeEdit->setTime(QTime(23,59,59));

    pModel=nullptr;

    this->imgPath="";

    date=true;    channel=false;    Isotype=false;    plate=false;    number=false;    check=false;    type=false;


    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->resizeRowsToContents();
    // ui->tableView->resizeColumnToContents(1);
    //ui->tableView->resizeRowToContents(1);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

DataBaseWidget::~DataBaseWidget()
{
    delete pModel;
    pModel=nullptr;

    delete ui;
}

void DataBaseWidget::hideEvent(QHideEvent *event)
{
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->ImageOrData_PushButton->setText(tr("Image"));

    showImg=false;
    ui->Img_Front_label->clear();
    ui->Img_LeftFront_label->clear();
    ui->Img_RightFront_label->clear();
    ui->Img_LeftAfter_label->clear();
    ui->Img_RightAfter_label->clear();
    ui->Img_After_label->clear();
    ui->Img_plate_label->clear();
}

void DataBaseWidget::resizeEvent(QResizeEvent *size)
{
    //    qDebug()<<size->size().width()-ui->Img_After_label->width()-ui->Img_RightAfter_label->width()-ui->Img_RightFront_label->width();
    //    qDebug()<<size->size().height()-ui->Img_After_label->height()-ui->Img_LeftAfter_label->height();

    if(size->oldSize().height()!=-1){
        int W=(size->size().width()-4) /3;
        int H=(size->size().height()-172)/2;
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
            ui->Img_plate_label->setFixedSize(W,H);
            ui->Img_plate_label->size().scale(W,H,Qt::IgnoreAspectRatio);
        }
    }
}

void DataBaseWidget::seFindtImgPathSlot(const QString &path, const int &format)
{
    this->imgPath=path;
    this->imgFormat=format;
}

QString DataBaseWidget::checkFilter()
{
    QStringList filterList;    

    if(channel){
        filterList.append(tr("Channel='%1'").arg(ui->Channel_spinBox->value()));
    }
    if(date){
        filterList.append(tr("(Timer>='%1' AND Timer<='%2')").arg(ui->DateTime_Statrt_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")).arg(ui->DataTime_End_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")));
    }
    if(number){
        if(ui->Numbers_Front_lineEdit->text()!=""){
            filterList.append(tr("ContainerFront='%1'").arg(ui->Numbers_Front_lineEdit->text()));
        }
        if(ui->Numbers_End_lineEdit->text()!=""){
            filterList.append(tr("ContainerAfter='%1'").arg(ui->Numbers_End_lineEdit->text()));
        }
    }
    if(plate){
        filterList.append(tr("Plate='%1'").arg(ui->Plate_lineEdit->text()));
    }
    if(type){
        filterList.append(tr("Type='%1'").arg(ui->Type_comboBox->currentIndex()-1));
    }
    if(check){
        if(ui->Yes_radioButton->isChecked()){
            filterList.append(tr("(CheckFront='%1' AND CheckAfter='%1'))").arg(1));
        }
        if(ui->No_radioButton->isChecked()){
            filterList.append(tr("(CheckFront='%1' OR CheckAfter='%1')").arg(0));
        }
    }
    if(Isotype){
        filterList.append(tr("(ISOFront='%1' OR ISOAfter='%1')").arg(ui->Iso_Type_comboBox->currentText()));
    }
    qDebug()<<filterList.join(" AND ");
    return  filterList.join(" AND ");
}

void DataBaseWidget::statisticalDataSlot(int rows, double correct, double error, double statistical)
{
    ui->total_label->setText(QString::number(rows));
    ui->correct_label->setText(QString::number(correct));
    ui->error_label->setText(QString::number(error));
    ui->rate_label->setText(tr("%1%").arg(QString::number(statistical,'f',2)));
}

void DataBaseWidget::returnModelSlot( QSqlTableModel *model)
{
    pModel=model;

    ui->tableView->setModel(pModel);

    ui->tableView->setColumnHidden(ID,true);
    ui->tableView->setColumnHidden(ImgFront,true);
    ui->tableView->setColumnHidden(ImgFrontCheck,true);
    ui->tableView->setColumnHidden(ImgFrontNumber,true);
    ui->tableView->setColumnHidden(ImgLeftFront,true);
    ui->tableView->setColumnHidden(ImgLeftFrontCheck,true);
    ui->tableView->setColumnHidden(ImgLeftFrontNumber,true);
    ui->tableView->setColumnHidden(ImgRightFront,true);
    ui->tableView->setColumnHidden(ImgRightFrontCheck,true);
    ui->tableView->setColumnHidden(ImgRightFrontNumber,true);
    ui->tableView->setColumnHidden(ImgLeftAfter,true);
    ui->tableView->setColumnHidden(ImgLeftAfterCheck,true);
    ui->tableView->setColumnHidden(ImgLeftAfterNumber,true);
    ui->tableView->setColumnHidden(ImgRightAfter,true);
    ui->tableView->setColumnHidden(ImgRightAfterCheck,true);
    ui->tableView->setColumnHidden(ImgRightAfterNumber,true);
    ui->tableView->setColumnHidden(ImgAfter,true);
    ui->tableView->setColumnHidden(ImgAfterCheck,true);
    ui->tableView->setColumnHidden(ImgAfterNumber,true);
    ui->tableView->setColumnHidden(PlateImg,true);   
}

void DataBaseWidget::on_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->stackedWidget1->setCurrentIndex(1);
    }
    else {
        ui->stackedWidget1->setCurrentIndex(0);
    }
}

void DataBaseWidget::on_Find_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void DataBaseWidget::on_ImageOrData_PushButton_toggled(bool checked)
{
    if(checked){
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->ImageOrData_PushButton->setText(tr("Data"));

        showImg=true;/* 设置加载图片 */
        on_tableView_clicked(ui->tableView->currentIndex());/* 重新处罚一次当前选择项 */
    }
    else {
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->ImageOrData_PushButton->setText(tr("Image"));

        showImg=false;
        ui->Img_Front_label->clear();
        ui->Img_LeftFront_label->clear();
        ui->Img_RightFront_label->clear();
        ui->Img_LeftAfter_label->clear();
        ui->Img_RightAfter_label->clear();
        ui->Img_After_label->clear();
        ui->Img_plate_label->clear();
    }
}

void DataBaseWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(pModel!=nullptr){
        qDebug()<<"nullptr";
        pModel->clear();
        delete pModel;
        pModel=nullptr;

        ui->tableView->clearSpans();
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok)){
        setDataBaseFilterSignal(checkFilter());
    }
    else if (button==ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        statisticalDataSlot(0,0,0,0);
    }
    ui->stackedWidget->setCurrentIndex(0);/* 切换到显示页 */
}

/* 选择状态切换 */
void DataBaseWidget::on_Datatime_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->DataTime_End_dateTimeEdit->setEnabled(true);
        ui->DateTime_Statrt_dateTimeEdit->setEnabled(true);

        date=true;
    }
    else if(arg1==Qt::Unchecked){
        ui->DataTime_End_dateTimeEdit->setEnabled(false);
        ui->DateTime_Statrt_dateTimeEdit->setEnabled(false);

        date=false;
    }
}

void DataBaseWidget::on_Channel_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Channel_spinBox->setEnabled(true);

        channel=true;
    }else if(arg1==Qt::Unchecked){
        ui->Channel_spinBox->setEnabled(false);

        channel=false;
    }
}

void DataBaseWidget::on_Numbers_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Numbers_Front_lineEdit->setEnabled(true);
        ui->Numbers_End_lineEdit->setEnabled(true);

        number=true;
    }
    else     if(arg1==Qt::Unchecked){
        ui->Numbers_Front_lineEdit->setEnabled(false);
        ui->Numbers_End_lineEdit->setEnabled(false);

        number=false;
    }
}

void DataBaseWidget::on_IsoType_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Iso_Type_comboBox->setEnabled(true);

        Isotype=true;
    }
    else     if(arg1==Qt::Unchecked){
        ui->Iso_Type_comboBox->setEnabled(false);

        Isotype=false;
    }
}

void DataBaseWidget::on_Plate_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Plate_lineEdit->setEnabled(true);

        plate=true;
    }
    else     if(arg1==Qt::Unchecked){
        ui->Plate_lineEdit->setEnabled(false);

        plate=false;
    }
}

void DataBaseWidget::on_Check_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Yes_radioButton->setEnabled(true);
        ui->No_radioButton->setEnabled(true);

        check=true;
    }
    else     if(arg1==Qt::Unchecked){
        ui->Yes_radioButton->setEnabled(false);
        ui->No_radioButton->setEnabled(false);

        check=false;
    }
}

void DataBaseWidget::on_Type_checkBox_stateChanged(int arg1)
{
    if(arg1==Qt::Checked){
        ui->Type_comboBox->setEnabled(true);

        type=true;
    }
    else     if(arg1==Qt::Unchecked){
        ui->Type_comboBox->setEnabled(false);

        type=false;
    }
}

/* 选中数据 */

void DataBaseWidget::showImages(const QModelIndex &index)
{
    this->resize(this->size() - QSize(1,1));
    this->resize(this->size() + QSize(1,1));

    ui->Img_Front_label->clear();
    ui->Img_LeftFront_label->clear();
    ui->Img_RightFront_label->clear();
    ui->Img_LeftAfter_label->clear();
    ui->Img_RightAfter_label->clear();
    ui->Img_After_label->clear();
    ui->Img_plate_label->clear();

    ui->label_15->clear();
    ui->label_34->clear();
    ui->label_30->clear();
    ui->label_33->clear();
    ui->label_29->clear();
    ui->label_32->clear();

    if(imgPath!=""){
        QDir dir(imgPath);
        QString suffixPath="";
        bool isRoot=false;/* 如果是保存在根目录就不用CD */
        QStringList date=index.sibling(index.row(),Timer).data().toString().split(" ");
        int land=index.sibling(index.row(),Channel).data().toInt();

        if(date.count()==2){
            QStringList tmpList=date[0].split("-");           
            switch (imgFormat) {
            case 0:
                suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(QString::number(land)).arg(tmpList.join("/")));
                break;
            case 1:
                suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(QString::number(land)).arg(tmpList[0].append("/").append(tmpList[1])));
                break;
            case 2:
                suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(QString::number(land)).arg(tmpList[0]));
                break;
            case 3:
                suffixPath=QDir::toNativeSeparators(tr("%1").arg(land));
                break;
            case 4:
                suffixPath=QDir::toNativeSeparators(tr("%1").arg(tmpList.join("/")));
                break;
            case 5:
                suffixPath=QDir::toNativeSeparators(tr("%1").arg(tmpList[0].append("/").append(tmpList[1])));
                break;
            case 6:
                suffixPath=QDir::toNativeSeparators(tr("%1").arg(tmpList[0]));
                break;
            case 7:
                isRoot=true;
                break;
            }
        }
        if(!isRoot){
            dir.cd(suffixPath);
        }

        QPixmap *labelPix = new QPixmap();
        /* 防止图片发生偏移 */
        QPixmap  labelPixFit;

        QString imgTmp=index.sibling(index.row(),ImgFront).data().toString();       
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_Front_label->width(),ui->Img_Front_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_Front_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),ImgLeftFront).data().toString();
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_LeftFront_label->width(),ui->Img_LeftFront_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_LeftFront_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),ImgRightFront).data().toString();
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_RightFront_label->width(),ui->Img_RightFront_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_RightFront_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),ImgLeftAfter).data().toString();
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_LeftAfter_label->width(),ui->Img_LeftAfter_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_LeftAfter_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),ImgRightAfter).data().toString();
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_RightAfter_label->width(),ui->Img_RightAfter_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_RightAfter_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),ImgAfter).data().toString();
                qDebug()<<imgTmp;
        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_After_label->width(),ui->Img_After_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_After_label->setPixmap(labelPixFit);
            }
        }
        imgTmp=index.sibling(index.row(),PlateImg).data().toString();

        if(imgTmp!=""){
            if(labelPix->load(QDir::toNativeSeparators(tr("%1/%2").arg(dir.path()).arg(imgTmp)))){
                labelPixFit=labelPix->scaled(ui->Img_plate_label->width(),ui->Img_plate_label->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->Img_plate_label->setPixmap(labelPixFit);
            }
        }

        date.clear();
        delete labelPix;
        labelPix=nullptr;
    }
}

void DataBaseWidget::on_tableView_clicked(const QModelIndex &index)
{
    if(showImg){
        showImages(index);
    }
    ui->numberFront_label->setText(index.sibling(index.row(),ContainerFront).data().toString());/* 前箱 */
    ui->numberAfter_label->setText(index.sibling(index.row(),ContainerAfter).data().toString());/* 后箱 */
    ui->checkFront_label->setText(index.sibling(index.row(),ISOFront).data().toString());/* 前箱型 */
    ui->checkAfter_label->setText(index.sibling(index.row(),ISOAfter).data().toString());/* 后箱型 */
    ui->Plate_label->setText(index.sibling(index.row(),Plate).data().toString());/* 车牌 */

    ui->label_15->setText(index.sibling(index.row(),ImgFrontNumber).data().toString());
    if(index.sibling(index.row(),ImgFrontCheck).data().toBool()){
        ui->label_15->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_15->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->label_30->setText(index.sibling(index.row(),ImgLeftFrontNumber).data().toString());
    if(index.sibling(index.row(),ImgLeftFrontCheck).data().toBool()){
        ui->label_30->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_30->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->label_34->setText(index.sibling(index.row(),ImgRightFrontNumber).data().toString());
    if(index.sibling(index.row(),ImgRightFrontCheck).data().toBool()){
        ui->label_34->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_34->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->label_29->setText(index.sibling(index.row(),ImgLeftAfterNumber).data().toString());
    if(index.sibling(index.row(),ImgLeftAfterCheck).data().toBool()){
        ui->label_29->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_29->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->label_33->setText(index.sibling(index.row(),ImgRightAfterNumber).data().toString());
    if(index.sibling(index.row(),ImgRightAfterCheck).data().toBool()){
        ui->label_33->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_33->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->label_32->setText(index.sibling(index.row(),ImgAfterNumber).data().toString());
    if(index.sibling(index.row(),ImgAfterCheck).data().toBool()){
        ui->label_32->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->label_32->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    /* Tupe,集装箱类别:
     * -1 – 未知
     * 0 – 一个 20 集装箱
     * 1 – 一个 40 吋/45 吋集装箱
     * 2 – 两个 20 吋集装箱
     */
    int TYPE=index.sibling(index.row(),Type).data().toInt();
    if(TYPE>=0){
        if(TYPE==2){
            if(index.sibling(index.row(),CheckFront).data().toBool()){
                ui->numberFront_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
            }
            else {
                ui->numberFront_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
            }
            if(index.sibling(index.row(),CheckAfter).data().toBool()){
                ui->numberAfter_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
            }
            else {
                ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
            }
        }
        else if (TYPE<2) {
            if(index.sibling(index.row(),CheckFront).data().toBool()){
                ui->numberFront_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
            }
            else {
                ui->numberFront_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
            }
            ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
        }
    }
    else {
        ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
        ui->numberFront_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
    }

    /* 使用Model */
//    QSqlRecord record=pModel->record(index.row());
//    ui->numberFront_label->setText(record.value("ContainerFront").toString());
//    ui->numberAfter_label->setText(record.value("ContainerAfter").toString());
//    ui->checkFront_label->setText(record.value("ISOFront").toString());
//    ui->checkAfter_label->setText(record.value("ISOAfter").toString());
//    ui->Plate_label->setText(record.value("Plate").toString());
//    if(record.value("Type").toInt()>0){
//        if(record.value("Type").toInt()==3){
//            if(record.value("CheckAfter").toBool()){
//                ui->numberAfter_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
//            }
//            else {
//                ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
//            }
//        }
//        if(record.value("Type").toInt()<3){
//            if(record.value("CheckFront").toBool()){
//                ui->numberFront_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
//            }
//            else {
//                ui->numberFront_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
//            }
//            ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
//        }
//    }
//    else {
//        ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
//        ui->numberFront_label->setStyleSheet("background-color: rgb(255, 255, 255);color: rgb(0, 0, 0);");
//    }
//    record.clear();
}

void DataBaseWidget::on_Home_pushButton_clicked()
{
//    if(pModel){
//        emit on_tableView_clicked(pModel->index(0,0));
//        ui->tableView->selectRow(0);
//    }
    ui->tableView->selectRow(0);
    on_tableView_clicked(ui->tableView->currentIndex());
}

void DataBaseWidget::on_End_pushButton_clicked()
{
//    if(pModel){
//        ui->tableView->selectRow(pModel->rowCount()-1);
//        emit on_tableView_clicked(pModel->index(pModel->rowCount()-1,0));
//    }
    if(ui->tableView->model()!=nullptr){
        ui->tableView->selectRow(ui->tableView->model()->rowCount()-1);
        on_tableView_clicked(ui->tableView->currentIndex());
    }
}

void DataBaseWidget::on_Front_pushButton_clicked()
{
//    int row=ui->tableView->currentIndex().row();
//    if(pModel&&row>0){
//        ui->tableView->selectRow(row-1);
//        //emit on_tableView_clicked(pModel->index(row-1,0));
//        on_tableView_clicked(ui->tableView->currentIndex());
//    }
    ui->tableView->selectRow(ui->tableView->currentIndex().row()-1);
    on_tableView_clicked(ui->tableView->currentIndex());
}

void DataBaseWidget::on_After_pushButton_clicked()
{
//    int row=ui->tableView->currentIndex().row();
//    if(pModel&&row<pModel->rowCount()-1){
//        ui->tableView->selectRow(row+1);
//        on_tableView_clicked(ui->tableView->currentIndex());
//    }
    ui->tableView->selectRow(ui->tableView->currentIndex().row()+1);
    on_tableView_clicked(ui->tableView->currentIndex());
}
