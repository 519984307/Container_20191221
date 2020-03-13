#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include <QAbstractItemView>
#include <QAbstractButton>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>

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
    /// \brief loadDataBaseToView 加载数据库到界面
    ///
    void loadDataBaseToView();

    ///
    /// \brief rateDataBase 统计数据
    ///
    void rateDataBase();

    ///
    /// \brief init 初始化
    ///
    void init();

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
    /// \brief on_Type_checkBox_stateChanged 箱型筛选
    /// \param arg1
    ///
    void on_Type_checkBox_stateChanged(int arg1);

    ///
    /// \brief on_Plate_checkBox_stateChanged 车牌筛选
    /// \param arg1
    ///
    void on_Plate_checkBox_stateChanged(int arg1);

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

    /* 数据库对象 */
    QSqlDatabase database;
    QSqlTableModel *pModel;

    //--------------------------------------------------------------- 查询帅筛选条件
    bool channel,date,type,plate,number;

    enum{
        ID=0,
        Timer=1,
        Channel=2,
        ContainerFront=3,
        CheckFront=4,
        ISOFront=5,
        ContainerAfter=6,
        CheckAfter=7,
        ISOAfter=8,
        ImgFront=9,
        ImgLeftFront=10,
        ImgRightFront=11,
        ImgLeftAfter=12,
        ImgRightAfter=13,
        ImgAfter=14,
        Plate=15,
        PlateTimer=16,
        PlateImg=17
    };
};

#endif // DATABASEWIDGET_H
