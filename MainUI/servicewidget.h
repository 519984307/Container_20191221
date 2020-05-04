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

public slots:

    ///
    /// \brief resultsAnalysisStateSlot  识别结果
    /// \param msg 信息体
    ///
    void resultsAnalysisStateSlot(const int& channel, const QString& msg);
};

#endif // SERVICEWIDGET_H
