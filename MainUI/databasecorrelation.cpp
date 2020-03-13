#include "databasecorrelation.h"

DataBaseCorrelation::DataBaseCorrelation(QObject *parent)
{
    this->setParent(parent);

    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("History.db");
    initDataBase();
}

void DataBaseCorrelation::initDataBase()
{
    if(database.open()){
        QSqlQuery query(database);
        query.prepare(tr("CREATE TABLE `Containers` (\
                      `ID`	INTEGER PRIMARY KEY AUTOINCREMENT,\
                      `Timer`	TEXT NOT NULL,\
                      `Channel`	INTEGER NOT NULL,\
                      `ContainerFront`	TEXT,\
                      `CheckFront`	INTEGER,\
                      `ISOFront`	TEXT,\
                      `ContainerAfter`	TEXT,\
                      `CheckAfter`	INTEGER,\
                      `ISOAfter`	TEXT,\
                      `ImgFront`	TEXT,\
                      `ImgLeftFront`	TEXT,\
                      `ImgRightFront`	TEXT,\
                      `ImgLeftAfter`	TEXT,\
                      `ImgRightAfter`	TEXT,\
                      `ImgAfter`	TEXT,\
                      `Plate`	 TEXT,\
                      `PlateTimer` 	TEXT,\
                      `PlateImg`	TEXT\
                  )"));
        if(!query.exec()){
            emit messageSignal(tr("CREATE TABLE `Containers` ERROR:%1").arg(query.lastError().text()));
        }
        database.close();
    }
}

void DataBaseCorrelation::insertDataBase(const QHash<QString, QString> dataHash)
{
    if(database.open()){
        QSqlTableModel model;
        model.setTable(tr("Containers"));
        model.select();
        QSqlRecord record=model.record();
        record.setValue("Timer",dataHash.value("Timer","NULL"));
        record.setValue("Channel",dataHash.value("Channel","NULL"));
        record.setValue("ContainerFront",dataHash.value("ContainerFront"));
        record.setValue("CheckFront",dataHash.value("CheckFront"));
        record.setValue("ISOFront",dataHash.value("ISOFront"));
        record.setValue("ContainerAfter",dataHash.value("ContainerAfter"));
        record.setValue("CheckAfter",dataHash.value("CheckAfter"));
        record.setValue("ISOAfter",dataHash.value("ISOAfter"));
        record.setValue("ImgFront",dataHash.value("ImgFront"));
        record.setValue("ImgLeftFront",dataHash.value("ImgLeftFront"));
        record.setValue("ImgRightFront",dataHash.value("ImgRightFront"));
        record.setValue("ImgLeftAfter",dataHash.value("ImgLeftAfter"));
        record.setValue("ImgRightAfter",dataHash.value("ImgRightAfter"));
        record.setValue("ImgAfter",dataHash.value("ImgAfter"));
        record.setValue("Plate",dataHash.value("Plate"));
        record.setValue("PlateTimer",dataHash.value("PlateTimer"));
        record.setValue("PlateImg",dataHash.value("PlateImg"));

        model.insertRecord(0,record);
        model.submitAll();
        database.close();
    }
    else {
        emit messageSignal(tr("CREATE TABLE `Containers` ERROR:%1").arg(database.lastError().text()));
    }
}
