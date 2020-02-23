#include "setting.h"

Setting::Setting()
{
    pSetting=new QSettings(QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/SYSTEM.INI"),QSettings::IniFormat);
    pSetting->setIniCodec("UTF-8");
}

Setting::~Setting()
{
    delete  pSetting;
}
