#ifndef CAMERSETTING_H
#define CAMERSETTING_H

#include <QWidget>

namespace Ui {
class CamerSetting;
}

class CamerSetting : public QWidget
{
    Q_OBJECT

public:
    explicit CamerSetting(QWidget *parent = nullptr);
    ~CamerSetting();

private:
    Ui::CamerSetting *ui;
};

#endif // CAMERSETTING_H
