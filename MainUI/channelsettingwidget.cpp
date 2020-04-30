#include "channelsettingwidget.h"
#include "ui_channelsettingwidget.h"

ChannelSettingWidget::ChannelSettingWidget(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelSettingWidget)
{
    ui->setupUi(this);

    this->setParent(parent);
    this->setHidden(true);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    this->channelNumber=number;

    if(!jsonRead()){  /* 加载配置 */
        if(jsonWrite()){
            jsonRead();
        }
    }
    else {
        jsonWritetoUI();/* 回写配置到UI */
    }
}

ChannelSettingWidget::~ChannelSettingWidget()
{
    delete ui;
}

bool ChannelSettingWidget::jsonWrite()
{
    /* 创建通道配置文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Json");
    mkPath.cd("Json");

    QFile file(QDir::toNativeSeparators(tr("%1/CHANNEL%2.json").arg(mkPath.path()).arg(channelNumber)));
    if(!file.open(QIODevice::WriteOnly)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("open CHANNEL%1.json error<errorCode=%2>").arg(channelNumber).arg(file.OpenError));
        return false;
    }

    QJsonDocument jsonDoc;
    QJsonObject  jsonChild, jsonObjRoot;

    QJsonObject jsonObj;
    jsonObj.insert(tr("FrontCamer"),ui->FrontCamer->text());
    jsonObj.insert(tr("AfterCamer"),ui->AfterCamer->text());
    jsonObj.insert(tr("LeftCamer"),ui->LeftCamer->text());
    jsonObj.insert(tr("RgihtCamer"),ui->RgihtCamer->text());
    jsonObj.insert(tr("PlateCamer"),ui->PlateCamer->text());
    jsonChild.insert("Camer",QJsonValue(jsonObj));

    QJsonObject jsonObj1;
    jsonObj1.insert(tr("LicensePlate"),ui->LicensePlate->currentIndex());
    jsonChild.insert("Plate",QJsonValue(jsonObj1));

    QJsonObject jsonObj2;
    jsonObj2.insert(tr("SerialPortMode"),ui->SerialPortMode->currentIndex());
    jsonObj2.insert(tr("SerialPortOne"),ui->SerialPortOne->value());
    jsonObj2.insert(tr("SerialPortTow"),ui->SerialPortTow->value());
    jsonObj2.insert(tr("SerialAddrOne"),ui->SerialAddrOne->text());
    jsonObj2.insert(tr("SerialAddrTow"),ui->SerialAddrTow->text());
    jsonObj2.insert(tr("PortOne"),ui->PortOne->value());
    jsonObj2.insert(tr("PortTow"),ui->PortTow->value());
    if(ui->SerialPortOpenState->isChecked()){
        jsonObj2.insert(tr("infraredStatus"),0);
    }
    if(ui->SerialPortCloseState->isChecked()){
        jsonObj2.insert(tr("infraredStatus"),1);
    }
    jsonChild.insert("SerialPort",QJsonValue(jsonObj2));

    QJsonObject jsonObj3;
    jsonObj3.insert(tr("Alias"),ui->Alias->text());
    jsonChild.insert("Other",QJsonValue(jsonObj3));

    jsonObjRoot.insert(tr("Channel%1").arg(channelNumber),QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);

    QByteArray arr=jsonDoc.toJson();
    file.write(arr);
    file.waitForBytesWritten(1000);
    file.close();

    return true;
}

bool ChannelSettingWidget::jsonRead()
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2/CHANNEL%3.json").arg(QCoreApplication::applicationDirPath()).arg("Json").arg(channelNumber)));
    if(!file.open(QIODevice::ReadOnly)){
        emit messageSignal(ZBY_LOG("ERROR"),tr("Failed to load the CHANNEL%1 parameter, create the default parameter error<errorCOde=%2>").arg(channelNumber).arg(file.OpenError));
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
            if(obj.contains(tr("Channel%1").arg(channelNumber))){
                QJsonValue value=obj.value(tr("Channel%1").arg(channelNumber));

                /* 读取子目录 */
                if(value.isObject()){
                    Alias= getJsonValue("Other","Alias",value.toObject()).toString().toLocal8Bit();
                    LicensePlate=getJsonValue("Plate","LicensePlate",value.toObject()).toInt();
                    AfterCamer= getJsonValue("Camer","AfterCamer",value.toObject()).toString();
                    FrontCamer= getJsonValue("Camer","FrontCamer",value.toObject()).toString();
                    LeftCamer= getJsonValue("Camer","LeftCamer",value.toObject()).toString();
                    RgihtCamer= getJsonValue("Camer","RgihtCamer",value.toObject()).toString();
                    PlateCamer= getJsonValue("Camer","PlateCamer",value.toObject()).toString();
                    PortOne= getJsonValue("SerialPort","PortOne",value.toObject()).toInt();
                    PortTow= getJsonValue("SerialPort","PortTow",value.toObject()).toInt();
                    SerialAddrOne= getJsonValue("SerialPort","SerialAddrOne",value.toObject()).toString();
                    SerialAddrTow= getJsonValue("SerialPort","SerialAddrTow",value.toObject()).toString();
                    infraredStatus=getJsonValue("SerialPort","infraredStatus",value.toObject()).toInt();
                    SerialPortMode= getJsonValue("SerialPort","SerialPortMode",value.toObject()).toInt();
                    SerialPortTow= getJsonValue("SerialPort","SerialPortTow",value.toObject()).toInt();
                    SerialPortOne= getJsonValue("SerialPort","SerialPortOne",value.toObject()).toInt();

                    return  true;
                    }
                }
            }
        }
    else {
        file.remove();
        emit messageSignal(ZBY_LOG("ERROR"),tr("load CHANNEL.json error<errorCode=%1>").arg(jsonError.errorString()));
    }
    file.close();

    return false;
}

void ChannelSettingWidget::jsonWritetoUI()
{
    ui->FrontCamer->setText(FrontCamer);
    ui->AfterCamer->setText(AfterCamer);
    ui->LeftCamer->setText(LeftCamer);
    ui->RgihtCamer->setText(RgihtCamer);
    ui->PlateCamer->setText(PlateCamer);

    ui->LicensePlate->setCurrentIndex(LicensePlate);

    ui->SerialPortMode->setCurrentIndex(SerialPortMode);
    ui->SerialPortOne->setValue(SerialPortOne);
    ui->SerialPortTow->setValue(SerialPortTow);
    ui->SerialAddrOne->setText(SerialAddrOne);
    ui->SerialAddrTow->setText(SerialAddrTow);
    ui->PortOne->setValue(PortOne);
    ui->PortTow->setValue(PortTow);
    if(!infraredStatus){/* 常开 */
        ui->SerialPortOpenState->setChecked(true);
    }
    else {/* 常闭 */
        ui->SerialPortCloseState->setChecked(true);
    }
    ui->Alias->setText(Alias);
}

QVariant ChannelSettingWidget::getJsonValue(const QString &child, const QString &key, QJsonObject obj)
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
    emit messageSignal(ZBY_LOG("ERROR"),tr("load CHANNEL.json value error:%1-%2").arg(child).arg(key));
    return  QString("");
}

void ChannelSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{   
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        if(jsonWrite()){
            emit messageSignal(ZBY_LOG("INFO"),tr("Save Channel Json sucess"));
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Save Channel Json error"));
        }
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){
        emit messageSignal(ZBY_LOG("INFO"),tr("Not Save Channel Json"));
    }
}
