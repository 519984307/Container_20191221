#ifndef UPLOADDATAPROCESSING_H
#define UPLOADDATAPROCESSING_H

#include <QObject>

class UploadDataProcessing : public QObject
{
    Q_OBJECT
public:
    explicit UploadDataProcessing(QObject *parent = nullptr);

signals:

    ///
    /// \brief InitializationParameterSlot 初始化参数
    /// \param host 地址
    /// \param port 端口
    /// \param path 路径
    /// \param user 用户名
    /// \param pass 密码
    ///
    void InitializationParameterSignal(const QString& user,const QString& pass,const QString& path,const QString& host,const int& port=21);

    ///
    /// \brief uploadDataSlot 上传数据
    /// \param data 数据
    ///
   void uploadDataSignal(const QString& data);

public slots:
};

#endif // UPLOADDATAPROCESSING_H
