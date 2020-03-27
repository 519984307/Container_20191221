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

QString DataBaseWidget::checkFilter()
{
    QStringList filterList;    

    if(channel){
        filterList.append(tr("Channel='%1'").arg(ui->Channel_spinBox->value()));
    }
    if(date){
        filterList.append(tr("Timer>='%1' AND Timer<='%2'").arg(ui->DateTime_Statrt_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")).arg(ui->DataTime_End_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")));
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
        filterList.append(tr("Type='%1'").arg(ui->Type_comboBox->currentIndex()));
    }
    if(check){
        if(ui->Yes_radioButton->isChecked()){
            filterList.append(tr("(CheckFront='%1' AND (CheckAfter='%1' OR CheckAfter!='%2'))").arg(1).arg(0));
        }
        if(ui->No_radioButton->isChecked()){
            filterList.append(tr("CheckFront='%1' OR CheckAfter='%1'").arg(0));
        }
    }
    if(Isotype){
        filterList.append(tr("(ISOFront='%1' OR ISOAfter='%1')").arg(ui->Iso_Type_comboBox->currentText()));
    }

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
    ui->tableView->setModel(model);

    ui->tableView->setColumnHidden(ID,true);
    ui->tableView->setColumnHidden(ImgFront,true);
    ui->tableView->setColumnHidden(ImgFrontNumber,true);
    ui->tableView->setColumnHidden(ImgLeftFront,true);
    ui->tableView->setColumnHidden(ImgLeftFrontNumber,true);
    ui->tableView->setColumnHidden(ImgRightFront,true);
    ui->tableView->setColumnHidden(ImgRightFrontNumber,true);
    ui->tableView->setColumnHidden(ImgLeftAfter,true);
    ui->tableView->setColumnHidden(ImgLeftAfterNumber,true);
    ui->tableView->setColumnHidden(ImgRightAfter,true);
    ui->tableView->setColumnHidden(ImgRightAfterNumber,true);
    ui->tableView->setColumnHidden(ImgAfter,true);
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
    }
    else {
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->ImageOrData_PushButton->setText(tr("Image"));
    }
}

void DataBaseWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(pModel!=nullptr){
        pModel->clear();
        delete pModel;
        pModel=nullptr;
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok)){
        setDataBaseFilterSignal(checkFilter());
    }
    else if (button==ui->buttonBox->button(QDialogButtonBox::Cancel)) {        
        statisticalDataSlot(0,0,0,0);
    }
    ui->stackedWidget->setCurrentIndex(0);
}

//------------------------------------------------------------------------------------------------------------- 选择状态切换
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

///--------------------------------------------------------------------------------------------------------------------------------------------------------- 选取数据
void DataBaseWidget::on_tableView_clicked(const QModelIndex &index)
{
    ui->numberFront_label->setText(index.sibling(index.row(),4).data().toString());/* 前箱 */
    ui->numberAfter_label->setText(index.sibling(index.row(),7).data().toString());/* 后箱 */
    ui->checkFront_label->setText(index.sibling(index.row(),6).data().toString());/* 前箱型 */
    ui->checkAfter_label->setText(index.sibling(index.row(),9).data().toString());/* 后箱型 */
    ui->Plate_label->setText(index.sibling(index.row(),22).data().toString());/* 车牌 */

    /* Type 为箱型 [0没有箱,1一个小箱,2一个大箱,3两个小箱] */
    int TYPE=index.sibling(index.row(),3).data().toInt();
    if(TYPE>0){
        if(TYPE==3){
            if(index.sibling(index.row(),5).data().toBool()){
                ui->numberAfter_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
            }
            else {
                ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
            }
        }
        else if (TYPE<3) {
            if(index.sibling(index.row(),8).data().toBool()){
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
    ui->tableView->selectRow(ui->tableView->model()->rowCount()-1);
    on_tableView_clicked(ui->tableView->currentIndex());
}

void DataBaseWidget::on_Before_pushButton_clicked()
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
