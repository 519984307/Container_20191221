#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = nullptr);
    ~DataWidget();

private:
    Ui::DataWidget *ui;

public slots:

    ///
    /// \brief logicStatusSlot 红外状态
    /// \param status 状态
    ///
    void logicStatusSlot(int* status);

signals:

};

#endif // DATAWIDGET_H
