#include "databaseinsert.h"


DataBaseInsert::DataBaseInsert(QObject *parent)
{
    this->setParent(parent);
}

DataBaseInsert::~DataBaseInsert()
{
    //QSqlDatabase::removeDatabase(connectName);
}

void DataBaseInsert::initDataBaseSlot(const QString &connectName,const QString &user, const QString &pass, const QString &ip)
{
    this->connectName=QString("DataBaseInsert").append(connectName);

    db=QSqlDatabase::addDatabase("QSQLITE",connectName);
    db.setDatabaseName(QDir::toNativeSeparators(tr("%1/%2/%3").arg(QCoreApplication::applicationDirPath()).arg("Data").arg("History.db")));
    db.setUserName(user);
    db.setPassword(pass);
    db.setHostName(ip);

    if(!db.open()){
        emit messageSignal(ZBY_LOG("ERROR"),tr("Open databse  error<errorCode=%1>").arg(db.lastError().text()));
    }
    db.close();
}

void DataBaseInsert::insertDataBaseSlot(QMap<QString, QString> data)
{
    //QMutexLocker locker(&mutex);
    if(db.open()){
        QSqlTableModel model(this,db);
        model.setTable(tr("Containers"));
        model.select();
        QSqlRecord record=model.record();
        record.setValue("Timer",data.value("Timer","NUL"));
        record.setValue("Channel",data.value("Channel","NUL"));
        record.setValue("Type",data.value("Type",QString::number(0)));
        record.setValue("ContainerFront",data.value("ContainerFront"));
        record.setValue("CheckFront",data.value("CheckFront"));
        record.setValue("ISOFront",data.value("ISOFront"));
        record.setValue("ContainerAfter",data.value("ContainerAfter"));
        record.setValue("CheckAfter",data.value("CheckAfter"));
        record.setValue("ISOAfter",data.value("ISOAfter"));
        record.setValue("ImgFront",data.value("ImgFront"));
        record.setValue("ImgLeftFront",data.value("ImgLeftFront"));
        record.setValue("ImgRightFront",data.value("ImgRightFront"));
        record.setValue("ImgLeftAfter",data.value("ImgLeftAfter"));
        record.setValue("ImgRightAfter",data.value("ImgRightAfter"));
        record.setValue("ImgAfter",data.value("ImgAfter"));
        record.setValue("Plate",data.value("Plate"));
        record.setValue("PlateTimer",data.value("PlateTimer"));
        record.setValue("PlateImg",data.value("PlateImg"));

        if(!model.insertRecord(0,record)){
            emit messageSignal(ZBY_LOG("ERROR"),tr("Insert data to databse  error<errorCOde=%1>").arg(model.lastError().text()));
        }
        model.submitAll();

        /*
         * 清除数据
         */
        data.clear();
        record.clear();
        model.clear();
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Open databse  error<errorCode=%1>").arg(db.lastError().text()));
    }
    db.close();
}

void DataBaseInsert::updateDataBaseSlot(QMap<QString, QString> data)
{
    //QMutexLocker locker(&mutex);
    if(db.open()){
        QSqlTableModel model(this,db);
        model.setTable(tr("Containers"));
        model.setFilter(tr("Timer=%1 AND Channel=%2").arg(data.value("Timer")).arg(data.value("Channel")));
        model.select();
        if(model.rowCount()==1){
            QSqlRecord record=model.record(0);
            record.setValue("ContainerFront",data.value("ContainerFront"));
            record.setValue("CheckFront",data.value("CheckFront"));
            record.setValue("ISOFront",data.value("ISOFront"));
            record.setValue("ContainerAfter",data.value("ContainerAfter"));
            record.setValue("CheckAfter",data.value("CheckAfter"));
            record.setValue("ISOAfter",data.value("ISOAfter"));
            record.setValue("ImgFrontNumber",data.value("ImgFrontNumber"));
            record.setValue("ImgLeftFrontNumber",data.value("ImgLeftFrontNumber"));
            record.setValue("ImgRightFrontNumber",data.value("ImgRightFrontNumber"));
            record.setValue("ImgLeftAfterNumber",data.value("ImgLeftAfterNumber"));
            record.setValue("ImgRightAfterNumber",data.value("ImgRightAfterNumber"));
            record.setValue("ImgAfterNumber",data.value("ImgAfterNumber"));
            model.setRecord(0,record);
            model.submitAll();

            record.clear();
        }
        model.clear();
    }
    db.close();
}
