#include "systemsettingwidget.h"
#include "ui_systemsettingwidget.h"

SystemSettingWidget::SystemSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSettingWidget)
{
    ui->setupUi(this);

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
}

SystemSettingWidget::~SystemSettingWidget()
{
    delete ui;
}

bool SystemSettingWidget::jsonWrite()
{
    /* 创建通道配置文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Json");
    mkPath.cd("Json");

    QFile file(QDir::toNativeSeparators(tr("%1/%2").arg(mkPath.path()).arg("SYSTEM.json")));

    if(!file.open(QIODevice::ReadWrite)){
        emit messageSignal(tr("Failed to load the parameter, create the default parameter. error:%1").arg(file.OpenError));
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
    jsonChild.insert("Channel",QJsonValue(jsonObj));

    QJsonObject jsonObj1;
    jsonObj1.insert(tr("ColorDisplay"),int(ui->ColorDisplay->isChecked()));
    jsonObj1.insert(tr("AutomaticCorrection"),int(ui->AutomaticCorrection->isChecked()));
    jsonObj1.insert(tr("Server"),int(ui->Server->isChecked()));
    jsonObj1.insert(tr("ServerIP"),ui->ServerIP->text());
    jsonObj1.insert(tr("ServerPort"),ui->ServerPort->text().toInt());
    jsonObj1.insert(tr("Client"),int(ui->Client->isChecked()));
    jsonObj1.insert(tr("ClientIP"),ui->ClientIP->text());
    jsonObj1.insert(tr("ClientPort"),ui->ClientPort->text().toInt());
    jsonChild.insert("Recognizer",QJsonValue(jsonObj1));

    QJsonObject jsonObj2;
    jsonObj2.insert(tr("ProtocolVersion"),int(ui->ProtocolV->currentIndex()));
    jsonObj2.insert(tr("CameraVersion"),int(ui->CameraV->currentIndex()));
    jsonChild.insert("Agreement",QJsonValue(jsonObj2));

    QJsonObject jsonObj3;
    jsonObj3.insert(tr("FtpAddress"),ui->FtpAddress->text());
    jsonObj3.insert(tr("FtpPort"),ui->FtpPort->text());
    jsonObj3.insert(tr("FtpUser"), ui->FtpUser->text());
    jsonObj3.insert(tr("FtpPassword"),ui->FtpPassword->text());
    jsonObj3.insert(tr("FtpLocalImgPath"),ui->FtpLocalImgPath->text());
    jsonObj3.insert(tr("FtpRemoteImgPath"),ui->FtpRemoteImgPath->text());
    jsonChild.insert("FTP",QJsonValue(jsonObj3));

    QJsonObject jsonObj4;
    jsonObj4.insert(tr("Minimization"),int(ui->Minimization->isChecked()));
    jsonObj4.insert(tr("SaveLog"),int(ui->SaveLog->isChecked()));
    jsonObj4.insert(tr("Language"), ui->Language->currentIndex());
    jsonChild.insert("Other",QJsonValue(jsonObj4));

    jsonObjRoot.insert("MAIN",QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);
    file.write(jsonDoc.toJson());
    file.close();

    return true;
}

bool SystemSettingWidget::jsonRead()
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2/SYSTEM.json").arg(QCoreApplication::applicationDirPath()).arg("Json")));
    if(!file.open(QIODevice::ReadOnly)){
        emit messageSignal(tr("Failed to load the parameter, create the default parameter. error:%1").arg(file.OpenError));
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
                    CameraVersion= getJsonValue("Agreement","CameraVersion",value.toObject()).toInt();
                    ProtocolVersion=getJsonValue("Agreement","ProtocolVersion",value.toObject()).toInt();
                    ChannelNumber= getJsonValue("Channel","ChannelNumber",value.toObject()).toInt();
                    ImageFormatOne= getJsonValue("Channel","ImageFormatOne",value.toObject()).toInt();
                    ImageFormatTow= getJsonValue("Channel","ImageFormatTow",value.toObject()).toInt();
                    SaveImageOne= getJsonValue("Channel","SaveImageOne",value.toObject()).toInt();
                    SaveImageTow= getJsonValue("Channel","SaveImageTow",value.toObject()).toInt();
                    FtpAddress= getJsonValue("FTP","FtpAddress",value.toObject()).toString();
                    FtpLocalImgPath= getJsonValue("FTP","FtpLocalImgPath",value.toObject()).toString();
                    FtpPassword= getJsonValue("FTP","FtpPassword",value.toObject()).toString();
                    FtpPort= getJsonValue("FTP","FtpPort",value.toObject()).toString();
                    FtpRemoteImgPath= getJsonValue("FTP","FtpRemoteImgPath",value.toObject()).toString();
                    FtpUser= getJsonValue("FTP","FtpUser",value.toObject()).toString();
                    Language= getJsonValue("Other","Language",value.toObject()).toInt();
                    Minimization= getJsonValue("Other","Minimization",value.toObject()).toInt();
                    SaveLog= getJsonValue("Other","SaveLog",value.toObject()).toInt();
                    AutomaticCorrection= getJsonValue("Recognizer","AutomaticCorrection",value.toObject()).toInt();
                    Client= getJsonValue("Recognizer","Client",value.toObject()).toInt();
                    ClientIP= getJsonValue("Recognizer","ClientIP",value.toObject()).toString();
                    ClientPort= getJsonValue("Recognizer","ClientPort",value.toObject()).toInt();
                    Server= getJsonValue("Recognizer","Server",value.toObject()).toInt();
                    ServerIP= getJsonValue("Recognizer","ServerIP",value.toObject()).toString();
                    ServerPort= getJsonValue("Recognizer","ServerPort",value.toObject()).toInt();
                    ColorDisplay= getJsonValue("Recognizer","ColorDisplay",value.toObject()).toInt();

                    return true;
                    }
                }
            }
        }
    else {
        emit messageSignal(tr("load SYSTEM.json error:%1").arg(jsonError.errorString()));
    }
    return false;
}

void SystemSettingWidget::jsonWritetoUI()
{
    ui->ChannelNumber->setValue(ChannelNumber);
    ui->SaveImage_1->setChecked(SaveImageOne);
    ui->SaveImage_2->setChecked(SaveImageTow);
    ui->ImageFormat_1->setCurrentIndex(ImageFormatOne);
    ui->ImageFormat_2->setCurrentIndex(ImageFormatTow);

    ui->ColorDisplay->setChecked(ColorDisplay);
    ui->AutomaticCorrection->setChecked(AutomaticCorrection);
    ui->Server->setChecked(Server);
    ui->ServerIP->setText(ServerIP);
    ui->ServerPort->setText(QString::number(ServerPort));
    ui->Client->setChecked(Client);
    ui->ClientIP->setText(ClientIP);
    ui->ClientPort->setText(QString::number(ClientPort));

    ui->ProtocolV->setCurrentIndex(ProtocolVersion);
    ui->CameraV->setCurrentIndex(CameraVersion);

    ui->FtpAddress->setText(FtpAddress);
    ui->FtpPort->setText(FtpPort);
    ui->FtpUser->setText(FtpUser);
    ui->FtpPassword->setText(FtpPassword);
    ui->FtpLocalImgPath->setText(FtpLocalImgPath);
    ui->FtpRemoteImgPath->setText(FtpRemoteImgPath);

    ui->Minimization->setChecked(Minimization);
    ui->SaveLog->setChecked(SaveLog);
    ui->Language->setCurrentIndex(Language);
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
    emit messageSignal(tr("load SYSTEM.json value error:%1-%2").arg(child).arg(key));
    return  "NULL";
}

void SystemSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        jsonWrite();
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){

    }
}
