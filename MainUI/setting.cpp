#include "setting.h"

Setting::Setting()
{
    pSetting=new QSettings(QCoreApplication::applicationDirPath()+"/SYSTEM.INI",QSettings::IniFormat);
    pSetting->setIniCodec("UTF-8");
}

Setting::~Setting()
{
    delete  pSetting;
}
