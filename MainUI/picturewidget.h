#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>

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
    void pictureStreamSlot(const QByteArray &jpgStream,const QString &camerIP);

signals:

    ///
    /// \brief playStreamSignal 播放流
    /// \param winID 窗口ID
    /// \param play 播放状态
    ///
    void playStreamSignal(uint winID,bool play);

    ///
    /// \brief resizeEventSignal 窗口调整刷新信号
    ///
    void resizeEventSignal();

    ///
    /// \brief putCommandSignal 抓取图片动作
    /// \param command /*保留*/
    /// \return
    ///
    bool putCommandSignal(const QString &command="");
};

#endif // PICTUREWIDGET_H
