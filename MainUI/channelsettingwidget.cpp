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

    jsonObjRoot.insert(tr("Channel%1").arg(channelNumber),QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);

    file.write(jsonDoc.toJson());
    file.close();
}

void ChannelSettingWidget::jsonRead()
{

}

void ChannelSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        jsonWrite();
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){

    }
}
