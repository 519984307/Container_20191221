#ifndef SETTING_H
#define SETTING_H

#include <QDir>
#include <QSettings>
#include <QCoreApplication>

class Setting
{
public:
    Setting();
    ~Setting();

    QSettings *pSetting;
};

#endif // SETTING_H
