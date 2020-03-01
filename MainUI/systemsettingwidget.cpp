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
}

SystemSettingWidget::~SystemSettingWidget()
{
    delete ui;
}

void SystemSettingWidget::writeINI()
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("SYSTEM.json")));

    if(!file.open(QIODevice::ReadWrite)){
        emit mesageSignal(tr("open SYSTEM.json error:%1").arg(file.OpenError));
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
    jsonObj4.insert(tr("Minimization"),int(ui->Minimization->checkState()));
    jsonObj4.insert(tr("SaveLog"),int(ui->SaveLog->checkState()));
    jsonObj4.insert(tr("Language"), ui->Language->currentIndex());
    jsonChild.insert("Other",QJsonValue(jsonObj4));

    jsonObjRoot.insert("MAIN",QJsonValue(jsonChild));
    jsonDoc.setObject(jsonObjRoot);
    file.write(jsonDoc.toJson());
    file.close();
}

void SystemSettingWidget::readINI()
{

}

void SystemSettingWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save)){
        writeINI();
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Discard)){

    }
}
