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
    /// \brief numberCheck 集装箱号码校验
    /// \param number 集装箱号码
    /// \param correct 是否矫正
    /// \return  校验结果
    ///
    bool numberCheck(QString &number,bool correct)Q_DECL_OVERRIDE;

private:

    ///
    /// \brief initCheckMap 初始化列表
    ///
    void initCheckMap();

    ///
    /// \brief computeQuadraticPower 计算箱号位的二次方
    /// \param variable 箱号数位
    /// \return 计算结果
    ///
    int computeQuadraticPower(int variable);

private:

    ///
    /// \brief checkMap 校验列表
    ///
    QMap<QChar,int> checkMap;
};

#endif // RESULTSANALYSIS_H
