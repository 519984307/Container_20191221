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
}

ChannelSettingWidget::~ChannelSettingWidget()
{
    delete ui;
}

void ChannelSettingWidget::jsonWrite()
{
    /* 创建通道配置文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Json");
    mkPath.cd("Json");

    QFile file(QDir::toNativeSeparators(tr("%1/CHANNEL%2.json").arg(mkPath.path()).arg(channelNumber)));
    if(!file.open(QIODevice::ReadWrite)){
        emit messageSignal(tr("open SYSTEM.json error:%1").arg(file.OpenError));
    }

    QJsonDocument jsonDoc;
    QJsonObject  jsonChild, jsonObjRoot;

    QJsonObject jsonObj;
    jsonObj.insert(tr("BeforeCamer"),ui->BeforeCamer->text());
    jsonObj.insert(tr("AfterCamer"),ui->AfterCamer->text());
    jsonObj.insert(tr("LeftCamer"),ui->LeftCamer->text());
    jsonObj.insert(tr("RgihtCamer"),ui->RgihtCamer->text());
    jsonObj.insert(tr("PlateCamer"),ui->PlateCamer->text());
    jsonChild.insert(tr("Camer"),QJsonValue(jsonObj));

    QJsonObject jsonObj1;
    jsonObj1.insert(tr("LicensePlate"),ui->LicensePlate->currentIndex());
    jsonChild.insert(tr("Plate"),QJsonValue(jsonObj1));

    QJsonObject jsonObj2;
    jsonObj2.insert(tr("SerialPortMode"),ui->SerialPortMode->currentIndex());
    jsonObj2.insert(tr("SerialPortOne"),ui->SerialPortOne->value());
    jsonObj2.insert(tr("SerialPortTow"),ui->SerialPortTow->value());
    jsonObj2.insert(tr("SerialAddrOne"),ui->SerialAddrOne->text());
    jsonObj2.insert(tr("SerialAddrTow"),ui->SerialAddrTow->text());
    jsonObj2.insert(tr("PortOne"),ui->PortOne->value());
    jsonObj2.insert(tr("PortTow"),ui->PortTow->value());
    jsonObj2.insert(tr("SerialPortOpenState"),int(ui->SerialPortOpenState->isChecked()));
    jsonObj2.insert(tr("SerialPortCloseState"),int(ui->SerialPortCloseState->isChecked()));
    jsonChild.insert(tr("SerialPort"),QJsonValue(jsonObj2));

    QJsonObject jsonObj3;
    jsonObj3.insert(tr("Alias"),ui->Alias->text());
    jsonChild.insert(tr("Other"),QJsonValue(jsonObj3));

    jsonObjRoot.insert(tr("Channel%1").arg(channelNumber),QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);

    file.write(jsonDoc.toJson());
    file.close();
}

#include <iostream>
void ChannelSettingWidget::jsonRead()
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2/CHANNEL%3.json").arg(QCoreApplication::applicationDirPath()).arg("Json").arg(channelNumber)));
    if(!file.open(QIODevice::ReadOnly)){
        emit messageSignal(tr("open SYSTEM.json error:%1").arg(file.OpenError));
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
                    QString Alias= getJsonValue("Other","Alias",value.toObject()).toString();
                    std::cout<<Alias.toStdString()<<std::endl;
                    int LicensePlate=getJsonValue("Plate","LicensePlate",value.toObject()).toInt();
                    std::cout<<LicensePlate<<std::endl;
                    QString AfterCamer= getJsonValue("Camer","AfterCamer",value.toObject()).toString();
                    QString BeforeCamer= getJsonValue("Camer","BeforeCamer",value.toObject()).toString();
                    QString LeftCamer= getJsonValue("Camer","LeftCamer",value.toObject()).toString();
                    QString RgihtCamer= getJsonValue("Camer","RgihtCamer",value.toObject()).toString();
                    QString PlateCamer= getJsonValue("Camer","PlateCamer",value.toObject()).toString();
                    int PortOne= getJsonValue("SerialPort","PortOne",value.toObject()).toInt();
                    int PortTow= getJsonValue("SerialPort","PortTow",value.toObject()).toInt();
                    QString SerialAddrOne= getJsonValue("SerialPort","SerialAddrOne",value.toObject()).toString();
                    QString SerialAddrTow= getJsonValue("SerialPort","SerialAddrTow",value.toObject()).toString();
                    int SerialPortCloseState= getJsonValue("SerialPort","SerialPortCloseState",value.toObject()).toInt();
                    int SerialPortMode= getJsonValue("SerialPort","SerialPortMode",value.toObject()).toInt();
                    int SerialPortOpenState= getJsonValue("SerialPort","SerialPortOpenState",value.toObject()).toInt();
                    int SerialPortTow= getJsonValue("SerialPort","SerialPortTow",value.toObject()).toInt();
                    }
                }
            }
        }
    else {
        emit messageSignal(tr("load CHANNEL.json error:%1").arg(jsonError.errorString()));
    }
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
                    //int value=jsonValue.toString();
                    return jsonValue.toString();
                }
                else {
                    return jsonValue.toInt();
                }
            }
        }
    }
    emit messageSignal(tr("load CHANNEL.json value error:%1-%2").arg(child).arg(key));
    return  "NULL";
}

void ChannelSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        jsonWrite();
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){
        jsonRead();
    }
}
