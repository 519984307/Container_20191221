#include "systemsettingwidget.h"
#include "ui_systemsettingwidget.h"

SystemSettingWidget::SystemSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingWidget)
{
    ui->setupUi(this);

    connect(ui->Contains_pushButton,SIGNAL(clicked()),this,SLOT(conditionsOfButton_clicked()));
    connect(ui->Eliminate_pushButton,SIGNAL(clicked()),this,SLOT(conditionsOfButton_clicked()));
    connect(ui->CheckPathPushButton_1,SIGNAL(clicked()),this,SLOT(checkPathPushButton_clicked()));
    connect(ui->CheckPathPushButton_2,SIGNAL(clicked()),this,SLOT(checkPathPushButton_clicked()));

    pSettingValues=new SettingValues () ;

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    /* 加载配置 */
    if(!jsonRead()){
        if(jsonWrite()){
            jsonRead();
        }
    }
    else {/* 外部更改配置,回写配置到UI */
        jsonWritetoUI();
    }

    if(pSettingValues->SaveImageOne){
        createImgPath(pSettingValues->ImgPathOne,pSettingValues->ImageFormatOne);
    }
    if(pSettingValues->SaveImageTow){
        createImgPath(pSettingValues->ImgPathTow,pSettingValues->ImageFormatTow);
    }
}

SystemSettingWidget::~SystemSettingWidget()
{
    delete  pSettingValues;
    delete ui;
}

void SystemSettingWidget::createImgPath(const QString &path,int currentindex)
{
    if(path!=""){
        QDir  dir(QDir::toNativeSeparators(path));
        for(int i=1;i<=pSettingValues->ChannelNumber;i++){
            switch (currentindex) {
            case 0:
                dir.mkpath(QDir::toNativeSeparators(tr("%1/%2").arg(i).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd"))));
                break;
            case 1:
                dir.mkpath(QDir::toNativeSeparators(tr("%1/%2").arg(i).arg(QDateTime::currentDateTime().toString("yyyy/MM"))));
                break;
            case 2:
                dir.mkpath(QDir::toNativeSeparators(tr("%1/%2").arg(i).arg(QDateTime::currentDateTime().toString("yyyy"))));
                break;
            case 3:
                dir.mkpath(QDir::toNativeSeparators(tr("%1").arg(i)));
                break;
            case 4:
                dir.mkpath(QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd"))));
                break;
            case 5:
                dir.mkpath(QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM"))));
                break;
            case 6:
                dir.mkpath(QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy"))));
                break;
            case 7:
                dir.mkpath(QDir::toNativeSeparators(path));
                break;
            }
        }
    }
}

bool SystemSettingWidget::jsonWrite()
{
    /* 创建系统配置文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Json");
    mkPath.cd("Json");

    QFile file(QDir::toNativeSeparators(tr("%1/%2").arg(mkPath.path()).arg("SYSTEM.json")));

    if(!file.open(QIODevice::WriteOnly)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("Failed to load the parameter, create the default parameter error<errorCode=%1>").arg(file.OpenError));
        return false;
    }

    QJsonDocument jsonDoc;
    QJsonObject jsonChild,jsonObjRoot;

    QJsonObject jsonObj;
    jsonObj.insert(tr("ChannelNumber"),ui->ChannelNumber->value());
    jsonObj.insert(tr("SaveImageOne"),int(ui->SaveImage_1->isChecked()));
    jsonObj.insert(tr("SaveImageTow"), int(ui->SaveImage_2->isChecked()));
    jsonObj.insert(tr("ImageFormatOne"),ui->ImageFormat_1->currentIndex());
    jsonObj.insert(tr("ImageFormatTow"),ui->ImageFormat_2->currentIndex());
    jsonObj.insert(tr("ImgPathOne"),ui->ImgPathlineEdit_1->text().toLocal8Bit().data());
    jsonObj.insert(tr("ImgPathTow"),ui->ImgPathlineEdit_2->text().toLocal8Bit().data());
    jsonChild.insert("Channel",QJsonValue(jsonObj));

    QJsonObject jsonObj1;
    if(ui->ColorDisplay->isChecked()){
        jsonObj1.insert(tr("CheckResult"),0);
    }
    if(ui->AutomaticCorrection->isChecked()){
        jsonObj1.insert(tr("CheckResult"),1);
    }
    jsonChild.insert("Recognizer",QJsonValue(jsonObj1));

    QJsonObject jsonObj2;
    jsonObj2.insert(tr("ProtocolVersion"),ui->ProtocolV->currentIndex());
    jsonObj2.insert(tr("CameraVersion"),ui->CameraV->currentIndex());
    jsonObj2.insert(tr("HcSDKPath"),ui->HcSDK_Path_lineEdit->text());
    jsonChild.insert("Agreement",QJsonValue(jsonObj2));

    QJsonObject jsonObj3;
    jsonObj3.insert(tr("FTP"),int(ui->FTP->isChecked()));
    jsonObj3.insert(tr("FtpAddress"),ui->FtpAddress->text());
    jsonObj3.insert(tr("FtpPort"),ui->FtpPort->text());
    jsonObj3.insert(tr("FtpUser"), ui->FtpUser->text());
    jsonObj3.insert(tr("FtpPassword"),ui->FtpPassword->text());
    jsonObj3.insert(tr("FtpLocalImgPath"),ui->FtpLocalImgPath->text());
    jsonObj3.insert(tr("FtpRemoteImgPath"),ui->FtpRemoteImgPath->text());
    jsonChild.insert("FTP",QJsonValue(jsonObj3));

    QJsonObject jsonObj4;
    jsonObj4.insert(tr("Minimization"),int(ui->Minimization->isChecked()));
    jsonObj4.insert(tr("Language"), ui->Language->currentIndex());
    jsonObj4.insert(tr("Automatic"),int(ui->Automatic->isChecked()));
    jsonChild.insert("Other",QJsonValue(jsonObj4));

    QJsonObject jsonObj5;
    jsonObj5.insert(tr("DataBaseVersion"), ui->DataBaseTypeV->currentIndex());
    jsonObj5.insert(tr("DataBaseUser"),ui->DataBaseUser->text());
    jsonObj5.insert(tr("DataBasePwd"),ui->DataBasePassword->text());
    jsonObj5.insert(tr("DataBaseAddr"),ui->DataBaseAddress->text());
    jsonObj5.insert(tr("DataBasePort"),ui->DataBasePort->text().toInt());
    jsonObj5.insert(tr("TextFormat"),int(ui->TextFormat->isChecked()));
    jsonObj5.insert(tr("TextFormatVersion"),ui->TextForamtV->currentIndex());
    jsonChild.insert("DataBase",QJsonValue(jsonObj5));

    QJsonObject jsonObj6;
    jsonObj6.insert(tr("SaveLog"),int(ui->SaveLog->isChecked()));
    jsonObj6.insert(tr("SaveLogVersion"), ui->SaveLogV->currentIndex());
    jsonObj6.insert(tr("InfoLog"),int(ui->InfoLog->isChecked()));
    jsonObj6.insert(tr("DebugLog"),int(ui->DebugLog->isChecked()));
    jsonChild.insert("Log",QJsonValue(jsonObj6));

    QJsonObject jsonObj7;
    if(ui->ClientModel->isChecked()){
        jsonObj7.insert(tr("ServiceModel"),0);
    }
    if(ui->ServerModel->isChecked()){
        jsonObj7.insert(tr("ServiceModel"),1);
    }
    jsonObj7.insert("Service_Type",ui->Service_Type_comboBox->currentIndex());
    jsonObj7.insert("SingletonAddress",ui->Address_Singleton_lineEdit->text());
    jsonObj7.insert("ManyCasesAddress",ui->Address_Many_textEdit->toPlainText());
    jsonObj7.insert("Heartbeat",int(ui->Hearbeat_checkBox->isChecked()));
    jsonObj7.insert("Resultting",int(ui->Resulting_checkBox->isChecked()));
    jsonChild.insert("Service",QJsonValue(jsonObj7));

    jsonObjRoot.insert("MAIN",QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);

    QByteArray arr=jsonDoc.toJson();/* 写入日志 */
    file.write(arr);
    file.waitForBytesWritten(1000);
    file.close();

    return true;
}

bool SystemSettingWidget::jsonRead()
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2/SYSTEM.json").arg(QCoreApplication::applicationDirPath()).arg("Json")));
    if(!file.open(QIODevice::ReadOnly)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("Failed to load the parameter, create the default parameter error<errorCode=%1>").arg(file.OpenError));
        return false;
    }

    QByteArray arr=file.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc=QJsonDocument::fromJson(arr,&jsonError);

    /* 加载文件 */
    if(!jsonDoc.isNull()&&jsonError.error==QJsonParseError::NoError){
        /* 读取根目录 */
        if(jsonDoc.isObject()){
            QJsonObject obj=jsonDoc.object();
            if(obj.contains(tr("MAIN"))){
                QJsonValue value=obj.value(tr("MAIN"));

                /* 读取子目录 */
                if(value.isObject()){
                    pSettingValues->CameraVersion= getJsonValue("Agreement","CameraVersion",value.toObject()).toInt();
                    pSettingValues->ProtocolVersion=getJsonValue("Agreement","ProtocolVersion",value.toObject()).toInt();
                    pSettingValues->HcSDKPath=getJsonValue("Agreement","HcSDKPath",value.toObject()).toString();

                    pSettingValues->ChannelNumber= getJsonValue("Channel","ChannelNumber",value.toObject()).toInt();
                    pSettingValues->ImageFormatOne= getJsonValue("Channel","ImageFormatOne",value.toObject()).toInt();
                    pSettingValues->ImageFormatTow= getJsonValue("Channel","ImageFormatTow",value.toObject()).toInt();
                    pSettingValues->SaveImageOne= getJsonValue("Channel","SaveImageOne",value.toObject()).toInt();
                    pSettingValues->SaveImageTow= getJsonValue("Channel","SaveImageTow",value.toObject()).toInt();
                    pSettingValues->ImgPathOne= getJsonValue("Channel","ImgPathOne",value.toObject()).toString();
                    pSettingValues->ImgPathTow= getJsonValue("Channel","ImgPathTow",value.toObject()).toString();

                    pSettingValues->FTP=getJsonValue("FTP","FTP",value.toObject()).toInt();
                    pSettingValues->FtpAddress= getJsonValue("FTP","FtpAddress",value.toObject()).toString();
                    pSettingValues->FtpLocalImgPath= getJsonValue("FTP","FtpLocalImgPath",value.toObject()).toString();
                    pSettingValues->FtpPassword= getJsonValue("FTP","FtpPassword",value.toObject()).toString();
                    pSettingValues->FtpPort= getJsonValue("FTP","FtpPort",value.toObject()).toString();
                    pSettingValues->FtpRemoteImgPath= getJsonValue("FTP","FtpRemoteImgPath",value.toObject()).toString();
                    pSettingValues->FtpUser= getJsonValue("FTP","FtpUser",value.toObject()).toString();

                    pSettingValues->Language= getJsonValue("Other","Language",value.toObject()).toInt();
                    pSettingValues->Minimization= getJsonValue("Other","Minimization",value.toObject()).toInt();
                    pSettingValues->Automatic=getJsonValue("Other","Automatic",value.toObject()).toInt();

                    pSettingValues->SaveLog= getJsonValue("Log","SaveLog",value.toObject()).toInt();
                    pSettingValues->SaveLogVersion= getJsonValue("Log","SaveLogVersion",value.toObject()).toInt();
                    pSettingValues->InfoLog= getJsonValue("Log","InfoLog",value.toObject()).toInt();
                    pSettingValues->DebugLog= getJsonValue("Log","DebugLog",value.toObject()).toInt();

                    pSettingValues->CheckResult=getJsonValue("Recognizer","CheckResult",value.toObject()).toInt();

                    pSettingValues->ServiceModel=getJsonValue("Service","ServiceModel",value.toObject()).toInt();
                    pSettingValues->Service_Type=getJsonValue("Service","Service_Type",value.toObject()).toInt();
                    pSettingValues->SingletonAddress=getJsonValue("Service","SingletonAddress",value.toObject()).toString();
                    pSettingValues->ManyCasesAddress=getJsonValue("Service","ManyCasesAddress",value.toObject()).toString();
                    pSettingValues->Heartbeat=getJsonValue("Service","Heartbeat",value.toObject()).toInt();
                    pSettingValues->Resultting=getJsonValue("Service","Resultting",value.toObject()).toInt();

                    pSettingValues->DataBaseVersion=getJsonValue("DataBase","DataBaseVersion",value.toObject()).toInt();
                    pSettingValues->DataBaseUser=getJsonValue("DataBase","DataBaseUser",value.toObject()).toString();
                    pSettingValues->DataBasePwd=getJsonValue("DataBase","DataBasePwd",value.toObject()).toString();
                    pSettingValues->DataBaseAddr=getJsonValue("DataBase","DataBaseAddr",value.toObject()).toString();
                    pSettingValues->DataBasePort=getJsonValue("DataBase","DataBasePort",value.toObject()).toInt();
                    pSettingValues->TextFormat=getJsonValue("DataBase","TextFormat",value.toObject()).toInt();
                    pSettingValues->TextFormatVersion=getJsonValue("DataBase","TextFormatVersion",value.toObject()).toInt();

                    return true;
                    }
                }
            }
        }
    else {
        emit messageSignal(ZBY_LOG("ERROR"),tr("load SYSTEM.json error<errorCode=%1>").arg(jsonError.errorString()));
    }
    return false;
}

void SystemSettingWidget::jsonWritetoUI()
{
    ui->ChannelNumber->setValue(pSettingValues->ChannelNumber);
    ui->SaveImage_1->setChecked(pSettingValues->SaveImageOne);
    ui->SaveImage_2->setChecked(pSettingValues->SaveImageTow);
    ui->ImageFormat_1->setCurrentIndex(pSettingValues->ImageFormatOne);
    ui->ImageFormat_2->setCurrentIndex(pSettingValues->ImageFormatTow);
    ui->ImgPathlineEdit_1->setText(pSettingValues->ImgPathOne);
    ui->ImgPathlineEdit_2->setText(pSettingValues->ImgPathTow);

    if(!pSettingValues->CheckResult){/* 颜色显示 */
        ui->ColorDisplay->setChecked(1);
    }
    else {/* 自动校验 */
        ui->AutomaticCorrection->setChecked(1);
    }

    if(!pSettingValues->ServiceModel){/* 客户端模式 */
        ui->ClientModel->setChecked(1);
    }
    else {/* 服务器模式 */
        ui->ServerModel->setChecked(1);
    }

    ui->Service_Type_comboBox->setCurrentIndex(pSettingValues->Service_Type);
    ui->Address_Singleton_lineEdit->setText(pSettingValues->SingletonAddress);
    ui->Address_Many_textEdit->setText(pSettingValues->ManyCasesAddress);
    ui->Hearbeat_checkBox->setChecked(pSettingValues->Heartbeat);
    ui->Resulting_checkBox->setChecked(pSettingValues->Resultting);

    ui->ProtocolV->setCurrentIndex(pSettingValues->ProtocolVersion);
    ui->CameraV->setCurrentIndex(pSettingValues->CameraVersion);
    ui->HcSDK_Path_lineEdit->setText(pSettingValues->HcSDKPath);

    ui->FTP->setChecked(pSettingValues->FTP);
    ui->FtpAddress->setText(pSettingValues->FtpAddress);
    ui->FtpPort->setText(pSettingValues->FtpPort);
    ui->FtpUser->setText(pSettingValues->FtpUser);
    ui->FtpPassword->setText(pSettingValues->FtpPassword);
    ui->FtpLocalImgPath->setText(pSettingValues->FtpLocalImgPath);
    ui->FtpRemoteImgPath->setText(pSettingValues->FtpRemoteImgPath);

    ui->Minimization->setChecked(pSettingValues->Minimization);
    ui->Language->setCurrentIndex(pSettingValues->Language);
    ui->Automatic->setChecked(pSettingValues->Automatic);

    ui->SaveLog->setChecked(pSettingValues->SaveLog);
    ui->SaveLogV->setCurrentIndex(pSettingValues->SaveLogVersion);
    ui->InfoLog->setChecked(pSettingValues->InfoLog);
    ui->DebugLog->setChecked(pSettingValues->DebugLog);

    ui->DataBaseTypeV->setCurrentIndex(pSettingValues->DataBaseVersion);
    ui->DataBaseUser->setText(pSettingValues->DataBaseUser);
    ui->DataBasePassword->setText(pSettingValues->DataBasePwd);
    ui->DataBaseAddress->setText(pSettingValues->DataBaseAddr);
    ui->DataBasePort->setText(QString::number(pSettingValues->DataBasePort));
    ui->TextFormat->setChecked(pSettingValues->TextFormat);
    ui->TextForamtV->setCurrentIndex(pSettingValues->TextFormatVersion);
}

QVariant SystemSettingWidget::getJsonValue(const QString &child, const QString &key, QJsonObject obj)
{
    if(obj.contains(child)){
        QJsonValue jsonValue=obj.value(child);       
        /* 读取配置子项 */
        if(jsonValue.isObject()){
            obj=jsonValue.toObject();
            /* 读取配置值 */
            if(obj.contains(key)){
                jsonValue=obj.value(key);
                if(jsonValue.isString()){
                    return jsonValue.toString();
                }
                else {
                    return jsonValue.toInt();
                }
            }
        }
    }
    emit messageSignal(ZBY_LOG("ERROR"),tr("load SYSTEM.json value error:%1-%2").arg(child).arg(key));
    return  "";
}

void SystemSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        if(jsonWrite()){
            emit messageSignal(ZBY_LOG("INFO"),tr("Save System Json sucess"));
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Save System Json error"));
        }
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){
        emit messageSignal(ZBY_LOG("INFO"),tr("Not Save System Json"));
    }
}

void SystemSettingWidget::checkPathPushButton_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this);

    QPushButton* pPb=qobject_cast<QPushButton*>(sender());
    if(pPb==ui->CheckPathPushButton_1){
        if(path==""){
            ui->ImgPathlineEdit_1->setText("");
        }
         ui->ImgPathlineEdit_1->setText(tr("%1").arg(path).toLocal8Bit());
    }
    else if (pPb==ui->CheckPathPushButton_2) {
        if(path==""){
            ui->ImgPathlineEdit_2->setText("");
        }
        ui->ImgPathlineEdit_2->setText(tr("%1").arg(path).toLocal8Bit());
    }
}

void SystemSettingWidget::conditionsOfButton_clicked()
{
    QString fileName="";
    QString check="";
    QPushButton* pPb=qobject_cast<QPushButton*>(sender());
    if(pPb==ui->Contains_pushButton){
        fileName="XXXX.dat";
        check=ui->Contains_lineEdit->text().trimmed().toUpper();
    }
    else if (pPb==ui->Eliminate_pushButton) {
        fileName="ZZZZ.dat";
        check=ui->Eliminate_lineEdit->text().trimmed().toUpper();
    }

    int index=-1;
    QFile file(QDir::toNativeSeparators(tr("%1/%2/%3").arg(QCoreApplication::applicationDirPath()).arg("QRecognition").arg(fileName)));

    if(check!=""){
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            QStringList strList=stream.readAll().split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
            for (int var = 0; var < strList.count(); ++var) {
                if(strList[var]==check){
                    index=var;
                    break;
                }
            }
            file.close();

            if(index!=-1){/* 添加项 */
                QMessageBox::StandardButton bt= QMessageBox::warning(this,check,tr("Whether to delete the record=%1").arg(check),QMessageBox::Yes|QMessageBox::No);
                if(bt==QMessageBox::Yes){
                    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                        strList.removeAt(index);
                        stream<<strList.join("\n");
                        file.close();
                    }
                }
            }
            else {/* 删除项 */
                QMessageBox::StandardButton bt= QMessageBox::warning(this,check,tr("Whether to add the record=%1").arg(check),QMessageBox::Yes|QMessageBox::No);
                if(bt==QMessageBox::Yes){
                    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                        strList.append(tr("%1").arg(check));
                        stream<<strList.join("\n");
                        file.close();
                    }
                }
            }
        }
    }
}
