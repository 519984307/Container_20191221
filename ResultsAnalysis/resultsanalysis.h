#ifndef RESULTSANALYSIS_H
#define RESULTSANALYSIS_H

#include "resultsanalysis_global.h"
#include "resultsanalysisinterface.h"

class RESULTSANALYSISSHARED_EXPORT ResultsAnalysis:public ResultsAnalysisInterface
{
    Q_OBJECT
    Q_INTERFACES(ResultsAnalysisInterface)
    Q_PLUGIN_METADATA(IID ResultsAnalysisInterfaceIID)

public:
    ResultsAnalysis(QObject* parent=nullptr);
    ~ResultsAnalysis()Q_DECL_OVERRIDE;

public:

    ///
    /// \brief resultsOfAnalysisSlot 分析箱号
    /// \param resultList 识别结果集
    /// \param type 逻辑类型
    /// \param imgList 图片名
    ///
    void resultsOfAnalysisSlot(QStringList resultList, int type, QStringList imgList)Q_DECL_OVERRIDE;

    ///
    /// \brief setCheckTheResultsSlot 是否校验识别结果
    /// \param correct 校验标示
    ///
    void setCheckTheResultsSlot(bool correct)Q_DECL_OVERRIDE;

    ///
    /// \brief setChannelSlot 设定通道号
    ///
    void setChannelSlot(int channel)Q_DECL_OVERRIDE;

    ///
    /// \brief sendMidResultSlot 是否发中间结果集
    /// \param state
    ///
    void sendMidResultSlot(bool state)Q_DECL_OVERRIDE;

private:

    ///
    /// \brief updateDataBase 更新数据库
    /// \param type 逻辑箱型
    /// \param Cindex1 箱号下标1
    /// \param Iindex1 箱型下标
    /// \param Cindex2 箱号下标2
    /// \param Iindex2 箱型下标
    ///
    void updateDataBase(int type,int Cindex1, int Iindex1,int Cindex2,int Iindex2,QStringList imgList);

    ///
    /// \brief initCheckMap 初始化校验列表
    ///
    void initCheckMap();

    ///
    /// \brief computeQuadraticPower 计算箱号位的二次方
    /// \param variable 箱号数位
    /// \return 计算结果
    ///
    int computeQuadraticPower(int variable);

    ///
    /// \brief numberCheck 集装箱号码校验
    /// \param number 集装箱号码
    /// \return  校验结果
    ///
    bool numberCheck(QString &number);

    ///
    /// \brief queueContainerNumber 统计箱号出现次数，分析箱号
    /// \param QString
    /// \return
    ///
    QString queueContainerNumber(QList<QString> list);

private:

    ///
    /// \brief ISOContains 箱型包含
    ///
    QStringList ISOContains;

    ///
    /// \brief ISOReplaceMap 箱型替换
    ///
    QMap<QString,QString> ISOReplaceMap;

    ///
    /// \brief checkMap 校验列表
    ///
    QMap<QChar,int> checkMap;

    ///
    /// \brief conTemp 箱号列表
    ///
    QStringList conTemp;

    ///
    /// \brief isoTemp 箱型列表
    ///
    QStringList isoTemp;

    ///
    /// \brief checkConList 箱号校验列表
    ///
    QList<int> checkConList;

    ///
    /// \brief correct 校验标志
    ///
    bool correct;

    ///
    /// \brief channel 通道号
    ///
    int channel;

    ///
    /// \brief sendMid 是否发送中间结果集
    ///
    bool sendMid;
};

#endif // RESULTSANALYSIS_H
