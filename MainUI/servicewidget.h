#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QWidget>

namespace Ui {
class ServiceWidget;
}

class ServiceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceWidget(QWidget *parent = nullptr);
    ~ServiceWidget();

private:
    Ui::ServiceWidget *ui;

public slots:

    ///
    /// \brief messageSlot 日志信息
    /// \param type 信息类型
    /// \param msg 信息体
    ///
    void messageSlot(const QString &type, const QString &msg);
};

#endif // SERVICEWIDGET_H
