#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();

private:
    Ui::LogWidget *ui;


public slots:

    ///
    /// \brief messageSlot 日志信息
    /// \param type 信息类型
    /// \param msg 信息体
    ///
    void messageSlot(const QString &type, const QString &msg);


};

#endif // LOGWIDGET_H
