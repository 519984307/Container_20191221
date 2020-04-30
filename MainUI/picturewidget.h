#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class PictureWidget;
}

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PictureWidget(QWidget *parent = nullptr);
    ~PictureWidget()Q_DECL_OVERRIDE;

private:
    Ui::PictureWidget *ui;

    ///
    /// \brief resizeEvent 重写窗口调整事件
    /// \param size
    ///
    void resizeEvent(QResizeEvent* size)Q_DECL_OVERRIDE;

    ///
    /// \brief hideEvent 重写窗口隐藏事件
    /// \param event
    ///
    void hideEvent(QHideEvent *event)Q_DECL_OVERRIDE;

private slots:

    ///
    /// \brief on_pushButton_clicked 抓取图片
    ///
    void on_pushButton_clicked();

    ///
    /// \brief on_pushButton_2_clicked 打开流
    ///
    void on_pushButton_2_clicked();

    ///
    /// \brief on_pushButton_3_clicked 停止流
    ///
    ///
    void on_pushButton_3_clicked();

    ///
    /// \brief on_pushButton_4_clicked 识别图片
    ///
    void on_pushButton_4_clicked();

public slots:

    ///
    /// \brief pictureStreamSlot 获取图片帧
    /// \param jpgStream 图片流
    /// \param camerIP 相机地址
    ///
    void pictureStreamSlot(const QByteArray &jpgStream, const int &imgNumber);

signals:

    ///
    /// \brief playStreamSignal 播放流
    /// \param winID 窗口ID
    /// \param play 播放状态
    ///
    void playStreamSignal(quint64 winID,bool play);

    ///
    /// \brief resizeEventSignal 窗口调整刷新信号
    ///
    void resizeEventSignal();

    ///
    /// \brief putCommandSignal 抓取图片
    /// \param command 图片编号
    /// \param imgName  图片时间戳
    /// \return
    ///
    bool putCommandSignal(const int &imgNumber=0,const QString &imgTime="");

    ///
    /// \brief pictureStreamSignal
    /// \param jpgStream
    /// \param command
    ///
    void pictureStreamSignal(const QByteArray &jpgStream, const int &imgNumber,const QString &imgTime="");
};

#endif // PICTUREWIDGET_H
