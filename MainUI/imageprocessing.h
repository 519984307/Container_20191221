#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QObject *parent = nullptr);

signals:

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief initCamer 初始化相机
    /// \param camerIP 相机地址
    /// \param camerPort 相机端口
    ///
    void initCamer(const QString &camerIP, quint16 camerPort,const QString &CamerUser,const QString &CamerPow);

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief putCommand 相机指令
    /// \param command 指令
    /// \return  返回执行状态
    ///
    bool putCommand(const QString &command);

public slots:

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief camerIDstates 相机状态
    /// \param camerIP 相机地址
    /// \param state 相机状态
    ///
    void camerIDstates(const QString &camerIP,bool state);

    ///------------------------------------------------------------------------------------------------------------GetImgaes
    /// \brief pictureStream 接受图片流
    /// \param jpgStream 图片流
    /// \param camerIP 相机地址
    ///
    void pictureStream(const QByteArray &jpgStream,const QString &camerIP);
};

#endif // IMAGEPROCESSING_H
