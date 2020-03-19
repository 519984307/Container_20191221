#include "databasecorrelation.h"

DataBaseCorrelation::DataBaseCorrelation(QObject *parent)
{
    this->setParent(parent);

    initDataBase();
}

DataBaseCorrelation::~DataBaseCorrelation()
{
    for (auto obj:QSqlDatabase::database().connectionNames()) {
        QSqlDatabase::removeDatabase(obj);
    }
}

void DataBaseCorrelation::initDataBase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","HISTORY");
    db.setDatabaseName("History.db");

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
                          emit messageSignal(tr("CREATE TABLE `Containers` ERROR:%1").arg(query.lastError().text()));
                      }
                      query.clear();
    }
    else {
        emit messageSignal(tr("CREATE TABLE `Containers` ERROR:%1").arg(db.lastError().text()));
    }
    db.close();
}
#include<iostream>
void DataBaseCorrelation::insertDataBaseSlot(QHash<QString, QString> dataHash)
{
    QMutexLocker &locker();
    QSqlDatabase db=QSqlDatabase::database("HISTORY");

    if(db.open()){
        QSqlTableModel model(this,db);
        model.setTable(tr("Containers"));
        model.select();
        QSqlRecord record=model.record();
        record.setValue("Timer",dataHash.value("Timer","NUL"));
        record.setValue("Channel",dataHash.value("Channel","NUL"));
        record.setValue("Type",dataHash.value("Type",QString::number(0)));
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
        model.clear();
        dataHash.clear();
    }
    else {
        emit messageSignal(tr("INSERT TABLE `Containers` ERROR:%1").arg(db.lastError().text()));
    }
    db.close();

    QHash<QString,QString>::iterator it;
    for (it=dataHash.begin();it!=dataHash.end();++it) {
        std::cout<<"|||"<<it.value().toStdString()<<std::endl;
    }
}
