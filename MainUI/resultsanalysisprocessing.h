#ifndef RESULTSANALYSISPROCESSING_H
#define RESULTSANALYSISPROCESSING_H

#include <QObject>
#include <QMap>

class ResultsAnalysisProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ResultsAnalysisProcessing(QObject *parent = nullptr);

signals:

    ///
    /// \brief containerSignal 箱号结果
    /// \param result 箱号
    ///
    void containerSignal(const int& type,const QString &result1,const int& resultCheck1,const QString &iso1,const QString &result2="",const int& resultCheck2=0,const QString &iso2="");

    ///
    /// \brief updateDataBaseSignal 更新箱号数据
    /// \param data 数据字典
    ///
    void updateDataBaseSignal(QMap<QString, QString> data);

    ///
    /// \brief resultsOfAnalysisSignal 分析箱号
    /// \param resultList 识别结果集
    /// \param type 逻辑类型
    /// \param imgTime 箱号时间戳
    ///
    void resultsOfAnalysisSignal(QStringList resultList, int type,const QString& imgTime);

    ///
    /// \brief setChannelSlot 设定通道号
    ///
    void setChannelSignal(int channel);

    ///
    /// \brief setCheckTheResultsSlot 是否校验识别结果
    /// \param correct 校验标志
    ///
    void setCheckTheResultsSignal(bool correct=false);

public slots:
};

#endif // RESULTSANALYSISPROCESSING_H
