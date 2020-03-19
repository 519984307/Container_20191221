#include "databaselogic.h"

DataBaseLogic::DataBaseLogic()
{
}

DataBaseLogic::~DataBaseLogic()
{
    for (auto db:QSqlDatabase::database().connectionNames()) {
        QSqlDatabase::removeDatabase(db);
    }
}

void DataBaseLogic::initDataBaseSlot(const QString &user,const QString &pass,const QString &ip)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","HISTORY");
    db.setDatabaseName("History.db");
    db.setUserName(user);
    db.setPassword(pass);
    db.setHostName(ip);

    if(db.open()){
        QSqlQuery query(db);
        query.prepare(tr("CREATE TABLE `Containers` (\
                      `ID`	INTEGER PRIMARY KEY AUTOINCREMENT,\
                      `Timer`	TEXT NOT NULL,\
                      `Channel`	INTEGER NOT NULL,\
                       'Type' INTEGER,\
                      `ContainerFront`	TEXT,\
                      `CheckFront`	INTEGER,\
                      `ISOFront`	TEXT,\
                      `ContainerAfter`	TEXT,\
                      `CheckAfter`	INTEGER,\
                      `ISOAfter`	TEXT,\
                      `ImgFront`	TEXT,\
                      `ImgFrontNumber`	TEXT,\
                      `ImgLeftFront`	TEXT,\
                      `ImgLeftFrontNumber`	TEXT,\
                      `ImgRightFront`	TEXT,\
                      `ImgRightFrontNumber`	TEXT,\
                      `ImgLeftAfter`	TEXT,\
                      `ImgLeftAfterNumber`	TEXT,\
                      `ImgRightAfter`	TEXT,\
                      `ImgRightAfterNumber`	TEXT,\
                      `ImgAfter`	TEXT,\
                      `ImgAfterNumber`	TEXT,\
                      `Plate`	 TEXT,\
                      `PlateTimer` 	TEXT,\
                      `PlateImg`	TEXT\
                  )"));
        if(!query.exec()){
                          emit messageSignal(ZBY_LOG("ERROR"),tr("Create table containers error<errorCode=%1>").arg(query.lastError().text()));
                      }
                      else {
                          emit messageSignal(ZBY_LOG("INFO"),tr("ZBY_LOG_INFO(Create table Containers sucess"));
                      }
                      query.clear();
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Open databse  error<errorCode=%1>").arg(db.lastError().text()));
    }
    db.close();
}

void DataBaseLogic::insertDataBaseSlot(QMap<QString, QString> data)
{
    QSqlDatabase db=QSqlDatabase::database("HISTORY");

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
        model.clear();
        record.clear();
        data.clear();
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Open databse  error<errorCode=%1>").arg(db.lastError().text()));
    }
    db.close();
}

QSqlDatabase DataBaseLogic::readDataBaseSlot()
{
    return(QSqlDatabase::database("HISTORY"));
}

void DataBaseLogic::updateDataBaseSlot(QMap<QString, QString> data)
{
    QSqlDatabase db=QSqlDatabase::database("HISTORY");

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
        }
    }
}
