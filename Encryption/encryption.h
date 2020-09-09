#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "encryption_global.h"
#include "encryptioninterface.h"

class ENCRYPTIONSHARED_EXPORT Encryption:public EncryptionInterface
{
    Q_OBJECT
    Q_INTERFACES(EncryptionInterface)
    Q_PLUGIN_METADATA(IID EncryptionInterfaceIID)

public:
    Encryption(QObject *parent=nullptr);
    ~Encryption()Q_DECL_OVERRIDE;

private:

    ///
    /// \brief key1 唯一KEY
    ///
    QByteArray  key1;

    ///
    /// \brief ind 检查KEY次数
    ///
    int ind;


    ///
    /// \brief pTimer 定时查找加密狗
    ///
    QTimer* pTimer;

    ////
    /// \brief UID 加密锁唯一硬件ID,为32字符长度字符串
    ///
    char UID[33]={0};

    ///
    /// \brief keyHandles 当前系统连接的所有SmartX加密锁Handle数组，Smart X最大支持同时插32支.
    ///
    long keyHandles[8]={0};

    ///
    /// \brief appID 程序标识符
    ///
    char appID[32]={"HCA5NT4DKKUE48ULHT"};/* HCA5NT4DKKUE48ULHT */

    ///
    /// \brief keyNumber 加密狗数量
    ///
    long keyNumber=0;

    ///
    /// \brief dogState 加密狗状态
    ///
    bool dogState;

    ///
    /// \brief pDLL 动态库对象
    ///
    QLibrary* pDLL;

    typedef   long (*SmartX3FindFUN)(char appID[32], long * keyHandles, long * keyNumber);
    ///
    /// \brief SmartXFind 查找加密狗
    ///
    SmartX3FindFUN SmartX3Find;

    typedef   long (*SmartX3GetUidFUN)(long nKeyHandle, char uid[33]);
    ///
    /// \brief SmartXGetUid 读取加密狗ID
    ///
    SmartX3GetUidFUN SmartX3GetUid;

    typedef   long (*SmartX3CheckExistFUN)(long keyHandle);
    ///
    /// \brief SmartXCheckExist  检查加密狗状态
    ///
    SmartX3CheckExistFUN SmartX3CheckExist;

private slots:

    ///
    /// \brief SmartXCheckExistSlot 检查加密狗
    ///
    void SmartXCheckExistSlot();

    ///
    /// \brief checkTheKeyFunc 校验MD5密匙
    ///
    void checkTheKeyFunc();


private:

    ///
    /// \brief smartXGetUidFunc 获取加密狗ID
    ///
    void smartXGetUidFunc();


    QString getKey(QByteArray arr);
    QByteArray runPro(QString cmd,QStringList arg);

public:

    ///
    /// \brief InitializationSlot 初始化参数
    ///
    void InitializationSlot()Q_DECL_OVERRIDE;

    ///
    /// \brief releaseResourcesSlot 释放动资源
    ///
    void releaseResourcesSlot()Q_DECL_OVERRIDE;

};

#endif // ENCRYPTION_H
