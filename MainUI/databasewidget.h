#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include "defineobj.h"

#include <QWidget>
#include <QAbstractItemView>
#include <QAbstractButton>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QAbstractItemView>

namespace Ui {
class DataBaseWidget;
}

class DataBaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataBaseWidget(QWidget *parent = nullptr);
    ~DataBaseWidget();

private:

    ///
    /// \brief checkFilter 查找条件
    ///
    QString checkFilter();

private slots:

    ///
    /// \brief on_checkBox_stateChanged 切换箱号和车牌窗口
    /// \param arg1
    ///
    void on_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Find_pushButton_clicked 查找数据
    ///
    void on_Find_pushButton_clicked();

    ///
    /// \brief on_ImageOrData_PushButton_toggled 切换图片和数据窗口
    /// \param checked
    ///
    void on_ImageOrData_PushButton_toggled(bool checked);

    ///
    /// \brief on_buttonBox_clicked 打开查询对话框
    /// \param button
    ///
    void on_buttonBox_clicked(QAbstractButton *button);

    ///-----------------------------------------------------------------------------------------------------------筛选条件
    ///
    /// \brief on_Datatime_checkBox_stateChanged 时间筛选
    /// \param arg1
    ///
    void on_Datatime_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Channel_checkBox_stateChanged 通道筛选
    /// \param arg1
    ///
    void on_Channel_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Numbers_checkBox_stateChanged 箱号筛选
    /// \param arg1
    ///
    void on_Numbers_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_IsoType_checkBox_stateChanged 箱型代码筛选
    /// \param arg1
    ///
    void on_IsoType_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Plate_checkBox_stateChanged 车牌筛选
    /// \param arg1
    ///
    void on_Plate_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Check_checkBox_stateChanged 结果筛选
    /// \param arg1
    ///
    void on_Check_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Type_checkBox_stateChanged 箱型筛选
    /// \param arg1
    ///
    void on_Type_checkBox_stateChanged(int arg1);

    ///-----------------------------------------------------------------------------------------------------------数据切换
    ///
    /// \brief on_tableView_clicked 选取数据
    /// \param index
    ///
    void on_tableView_clicked(const QModelIndex &index);

    ///
    /// \brief on_Home_pushButton_clicked 首页
    ///
    void on_Home_pushButton_clicked();

    ///
    /// \brief on_End_pushButton_clicked 末页
    ///
    void on_End_pushButton_clicked();

    ///
    /// \brief on_Before_pushButton_clicked 前一页
    ///
    void on_Before_pushButton_clicked();

    ///
    /// \brief on_After_pushButton_clicked 后一页
    ///
    void on_After_pushButton_clicked();

private:
    Ui::DataBaseWidget *ui;   

    ///
    /// \brief pModel 数据模型对象(作用于查询插件返回的model指针对象)
    ///
    QSqlTableModel *pModel;

    //--------------------------------------------------------------- 查询条件
    bool channel,date,Isotype,plate,number,check,type;

    //-------------------------------------------------------------- 字段枚举
    enum{
        ID=0,
        Timer=1,
        Channel=2,
        Type=3,
        ContainerFront=4,
        CheckFront=5,
        ISOFront=6,
        ContainerAfter=7,
        CheckAfter=8,
        ISOAfter=9,
        ImgFront=10,
        ImgFrontNumber=11,
        ImgLeftFront=12,
        ImgLeftFrontNumber=13,
        ImgRightFront=14,
        ImgRightFrontNumber=15,
        ImgLeftAfter=16,
        ImgLeftAfterNumber=17,
        ImgRightAfter=18,
        ImgRightAfterNumber=19,
        ImgAfter=20,
        ImgAfterNumber=21,
        Plate=22,
        PlateTimer=23,
        PlateImg=24
    };

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 信息类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief setDataBaseFilterSlot 设置数据库筛选条件
    /// \param filter 筛选条件
    ///
    void setDataBaseFilterSignal(const QString &filter);

public slots:

    ///
    /// \brief returnModelSlot 读取数据库
    /// \param model 数据库模型
    ///
    void returnModelSlot(QSqlTableModel *model);

    ///
    /// \brief statisticalDataSlot 统计数据
    /// \param rows 总数
    /// \param correct 正确
    /// \param error 错误
    /// \param statistical 统计
    ///
     void statisticalDataSlot(int rows,double correct,double error,double statistical);
};

#endif // DATABASEWIDGET_H
