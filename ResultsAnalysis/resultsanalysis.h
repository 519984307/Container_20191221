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
    /// \param imgTime 箱号时间戳
    ///
    void resultsOfAnalysisSlot(QStringList resultList, int type,const QString& imgTime)Q_DECL_OVERRIDE;

    ///
    /// \brief setCheckTheResultsSlot 是否校验识别结果
    /// \param correct 校验标示
    ///
    void setCheckTheResultsSlot(bool correct)Q_DECL_OVERRIDE;

    ///
    /// \brief setChannelSlot 设定通道号
    ///
    void setChannelSlot(int channel)Q_DECL_OVERRIDE;

private:

    ///
    /// \brief updateDataBase 更新数据库
    /// \param type 逻辑箱型
    /// \param index1 箱号下标1
    /// \param index2 箱号下标2
    ///
    void updateDataBase(int type,int index1, int index2);

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

private:

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
    /// \brief imgTime 箱号时间戳
    ///
    QString imgTime;

    ///
    /// \brief channel 通道号
    ///
    int channel;
};

#endif // RESULTSANALYSIS_H
