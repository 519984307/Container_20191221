#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QResizeEvent>

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget()Q_DECL_OVERRIDE;

    ///
    /// \brief resizeEvent 重写窗口调整事件
    /// \param size
    ///
    void resizeEvent(QResizeEvent* size)Q_DECL_OVERRIDE;

private:

    Ui::DataWidget *ui;

    QMutex mutex;

    bool init;

public slots:

    ///
    /// \brief logicStatusSlot 红外状态
    /// \param status 状态值
    ///
    void logicStatusSlot(int* status);

    ///
    /// \brief pictureStreamSlot 图片流数据
    /// \param jpgStream 图片流
    /// \param imgNumber 编号
    ///
    void pictureStreamSlot(const QByteArray &jpgStream,const int &imgNumber);

signals:

    void simulateTriggerSignal(int type);

private slots:

    void on_test_22_pushButton_clicked();
    void on_test_45_pushButton_clicked();
    void on_test_double_22_front_pushButton_clicked();
    void on_test_double_22_before_pushButton_clicked();
    void on_while_cycle_capture_checkBox_stateChanged(int arg1);
    void on_clearn_image_pushButton_clicked();
};

#endif // DATAWIDGET_H
