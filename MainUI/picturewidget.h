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
    ~PictureWidget();

private:
    Ui::PictureWidget *ui;

signals:
    void playViedoStreamSignals(uint64_t winID,bool play);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // PICTUREWIDGET_H
