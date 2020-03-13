#include "checkdatabasewidget.h"
#include "ui_checkdatabasewidget.h"

CheckDataBaseWidget::CheckDataBaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckDataBaseWidget)
{
    ui->setupUi(this);
}

CheckDataBaseWidget::~CheckDataBaseWidget()
{
    delete ui;
}

void CheckDataBaseWidget::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Ok)){
        ;
    }
    if(button==ui->buttonBox->button(QDialogButtonBox::Cancel)){
        ;
    }
}
