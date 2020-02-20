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
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

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
};

#endif // PICTUREWIDGET_H
