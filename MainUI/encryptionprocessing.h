#ifndef ENCRYPTIONPROCESSING_H
#define ENCRYPTIONPROCESSING_H

#include <QObject>

class EncryptionProcessing : public QObject
{
    Q_OBJECT
public:
    explicit EncryptionProcessing(QObject *parent = nullptr);

signals:

    ///
    /// \brief GetEncryptedInformationSignal 获取加密信息
    /// \param data 数据
    ///
    void GetEncryptedInformationSignal(const QString& data);

    ///
    /// \brief GetTheEncryptedState 获取加密状态
    /// \param state
    ///
    void GetTheEncryptedStateSignal(bool state);

public slots:
};

#endif // ENCRYPTIONPROCESSING_H
