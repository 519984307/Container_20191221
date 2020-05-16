#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QWidget>
#include <QDateTime>

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

    ///
    /// \brief countTcp TCP数量
    ///
    int countTcp;

public slots:

    ///
    /// \brief resultsAnalysisStateSlot  识别结果
    /// \param msg 信息体
    ///
    void resultsAnalysisStateSlot(const int& channel, const QString& msg);

    ///
    /// \brief socketConnectCountSlot socket链接数量
    /// \param count
    ///
    void socketConnectCountSlot(int count);
};

#endif // SERVICEWIDGET_H
