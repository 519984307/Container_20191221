#include "databaseread.h"

DataBaseRead::DataBaseRead(QObject *parent)
{
    this->setParent(parent);
    model=nullptr;
}

DataBaseRead::~DataBaseRead()
{
//    if(model!=nullptr){
//         delete model;
//    }

//    QSqlDatabase::removeDatabase(connectName);
}

void DataBaseRead::initDataBaseSlot(const QString &connectName,const QString &user,const QString &pass,const QString &ip)
{
    /*  创建插件目录  */
    QDir pluginsDir(QCoreApplication::applicationDirPath());
    const QString pluginPath="Data";
    if(!pluginsDir.cd(pluginPath)){
        pluginsDir.mkdir(pluginPath);
        pluginsDir.cd(pluginPath);
    }

    this->connectName=connectName;

    db=QSqlDatabase::addDatabase("QSQLITE",connectName);
    db.setDatabaseName(QDir::toNativeSeparators(tr("%1/%2").arg(pluginsDir.path()).arg("History.db")));
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

void DataBaseRead::setDataBaseFilterSlot(const QString &filter)
{
    //QMutexLocker locker(&mutex);
    if(db.open()){

        if(model!=nullptr){
            model->clear();
            model=nullptr;
        }

        model=new QSqlTableModel (this,db);
        model->setTable(tr("Containers"));
        model->setFilter(filter);
        model->select();
        while (model->canFetchMore()) {
            model->fetchMore();
        }

        emit returnModelSingal(model);
    }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("Open databse  error<errorCode=%1>").arg(db.lastError().text()));
    }
    db.close();
}
