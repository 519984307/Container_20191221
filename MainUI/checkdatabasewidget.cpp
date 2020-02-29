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
