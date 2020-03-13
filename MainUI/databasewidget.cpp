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

    init();
}

DataBaseWidget::~DataBaseWidget()
{
    database.close();
    delete pModel;
    delete ui;
}

void DataBaseWidget::init()
{
    date=true;    channel=false;    type=false;    plate=false;    number=false;

    if(QSqlDatabase::contains("qt_sql_default_connection")){
        database=QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database=QSqlDatabase::addDatabase("QSQLITE");
    }

    database.setDatabaseName("History.db");
    pModel=new QSqlTableModel (this,database);
    pModel->setTable("Containers");
    pModel->setSort(ID,Qt::AscendingOrder);;

    ui->tableView->setModel(pModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->resizeRowsToContents();
    // ui->tableView->resizeColumnToContents(1);
    //ui->tableView->resizeRowToContents(1);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->setColumnHidden(ID,true);
    ui->tableView->setColumnHidden(ImgFront,true);
    ui->tableView->setColumnHidden(ImgLeftFront,true);
    ui->tableView->setColumnHidden(ImgRightFront,true);
    ui->tableView->setColumnHidden(ImgLeftAfter,true);
    ui->tableView->setColumnHidden(ImgRightAfter,true);
    ui->tableView->setColumnHidden(ImgAfter,true);
    ui->tableView->setColumnHidden(PlateImg,true);
}

void DataBaseWidget::loadDataBaseToView()
{
    QStringList filterList;

    if(database.open()){
        if(channel){
            filterList.append(tr("Channel='%1'").arg(ui->Channel_spinBox->value()));
            //pModel->setFilter(tr("Channel='%1'").arg(ui->Channel_spinBox->value()));
        }
        if(date){
            filterList.append(tr("Timer>='%1' AND Timer<='%2'").arg(ui->DateTime_Statrt_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")).arg(ui->DataTime_End_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")));
            //pModel->setFilter(tr("Timer>='%1' AND Timer<='%2'").arg(ui->DateTime_Statrt_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")).arg(ui->DataTime_End_dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss")));
        }
        if(number){
            if(ui->Numbers_Front_lineEdit->text()!=""){
                filterList.append(tr("ContainerFront='%1'").arg(ui->Numbers_Front_lineEdit->text()));
                //pModel->setFilter(tr("ContainerFront='%1'").arg(ui->Numbers_Front_lineEdit->text()));
            }
            if(ui->Numbers_End_lineEdit->text()!=""){
                //pModel->setFilter(tr("ContainerAfter='%1'").arg(ui->Numbers_End_lineEdit->text()));
                filterList.append(tr("ContainerAfter='%1'").arg(ui->Numbers_End_lineEdit->text()));
            }
        }
        if(plate){
            //pModel->setFilter(tr("Plate='%1'").arg(ui->Plate_lineEdit->text()));
            filterList.append(tr("Plate='%1'").arg(ui->Plate_lineEdit->text()));
        }
        if(type){
            //pModel->setFilter(tr("ISOFront='%1' OR ISOAfter='%1'").arg(ui->Type_comboBox->currentText()));
            filterList.append(tr("(ISOFront='%1' OR ISOAfter='%1')").arg(ui->Type_comboBox->currentText()));
        }

        QString filter="";
        int num= filterList.count();

        for (int i=0;i<num;i++) {
            filter.append(filterList[i]);
            if(i<num-1){
                filter.append(" AND ");
            }
        }

        pModel->setFilter(filter);
        pModel->select();
        database.close();

        filterList.clear();
    }

    rateDataBase();
}

void DataBaseWidget::rateDataBase()
{
    emit on_tableView_clicked(pModel->index(0,0));

    double correct=0;    double error=0;

    QSqlRecord record;

    for(int i=0;i<pModel->rowCount();i++){
        record=pModel->record(i);
        if(record.value("CheckFront").toBool()||record.value("CheckAfter").toBool()){
            correct++;
        }
        else {
            error++;
        }
    }
    ui->total_label->setText(QString::number(pModel->rowCount()));
    ui->correct_label->setText(QString::number(correct));
    ui->error_label->setText(QString::number(error));
    ui->rate_label->setText(tr("%1%").arg(QString::number(correct/pModel->rowCount()*100,'f',2)));
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
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok)){
        loadDataBaseToView();
    }
    else if (button==ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        ;
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

void DataBaseWidget::on_tableView_clicked(const QModelIndex &index)
{
    QSqlRecord record=pModel->record(index.row());

    ui->numberFront_label->setText(record.value("ContainerFront").toString());
    ui->numberAfter_label->setText(record.value("ContainerAfter").toString());
    ui->checkFront_label->setText(record.value("ISOFront").toString());
    ui->checkAfter_label->setText(record.value("ISOAfter").toString());
    ui->Plate_label->setText(record.value("Plate").toString());

    if(record.value("CheckFront").toBool()){
        ui->numberFront_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->numberFront_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    if(record.value("CheckAfter").toBool()){
        ui->numberAfter_label->setStyleSheet("background-color: rgb(0, 170, 0);color: rgb(255, 255, 255);");
    }
    else {
        ui->numberAfter_label->setStyleSheet("background-color: rgb(255, 0, 0);color: rgb(255, 255, 255);");
    }

    ui->tableView->setCurrentIndex(index);
    ui->tableView->setFocus();
}

void DataBaseWidget::on_Home_pushButton_clicked()
{
    if(pModel){
        emit on_tableView_clicked(pModel->index(0,0));
        ui->tableView->selectRow(0);
    }
}

void DataBaseWidget::on_End_pushButton_clicked()
{
    if(pModel){
        emit on_tableView_clicked(pModel->index(pModel->rowCount()-1,0));
        ui->tableView->selectRow(pModel->rowCount()-1);
    }
}

void DataBaseWidget::on_Before_pushButton_clicked()
{
    if(pModel&&ui->tableView->currentIndex().row()>0){
        emit on_tableView_clicked(pModel->index(ui->tableView->currentIndex().row()-1,0));
    }
}

void DataBaseWidget::on_After_pushButton_clicked()
{
    if(pModel&&ui->tableView->currentIndex().row()<pModel->rowCount()-1){
        emit on_tableView_clicked(pModel->index(ui->tableView->currentIndex().row()+1,0));
    }
}
