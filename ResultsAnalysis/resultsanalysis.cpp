#include "resultsanalysis.h"

ResultsAnalysis::ResultsAnalysis(QObject *parent)
{
    this->setParent(parent);
    this->correct=false;
    this->channel=-1;
    initCheckMap();
}

ResultsAnalysis::~ResultsAnalysis()
{
    checkMap.clear();
}

void ResultsAnalysis::setCheckTheResultsSlot(bool correct)
{
    this->correct=correct;
}

void ResultsAnalysis::setChannelSlot(int channel)
{
    this->channel=channel;
}

void ResultsAnalysis::initCheckMap()
{
    char ch = 'A';
    for (int i = 10; i <= 38; i++)
    {
        if ((i == 11) || (i == 22) || (i == 33))
        {
            i++;
        }
        checkMap.insert(ch,i);
        ch++;
    }
}

int ResultsAnalysis::computeQuadraticPower(int variable)
{
    int result;
    if (variable == 0)
    {
        return 1;
    }
    result = 2 * computeQuadraticPower(variable - 1);
    return result;
}

bool ResultsAnalysis::numberCheck(QString &number)
{
    if(number.length()<10)/* 最后一位可以计算出来 */
    {
        return false;
    }

    int sum=0;
    int i = 1;
    foreach (QChar ch , number)
    {/* 计算校验总值 */
        if (i == 11)
        {
            break;
        }
        if (i > 4)
        {
            sum += (ch.toLatin1()-'0') * (computeQuadraticPower(i-1));
        }
        else
        {
            if (checkMap.value(ch)!=0)
            {
                sum += checkMap.value(ch) * computeQuadraticPower(i - 1);
            }
            else
            {/* 箱号前4位必须是英文,否则箱号格式错误 */
                return false;
            }
        }
        i++;
    }

    int die=sum % 11;

    if(number.count()==10){
        if(correct){
            number=number.append(QString::number(die));
            return true;
        }
        return false;
    }
    if (number.count()==11 && die!=number[10].toLatin1()-'0')
    {
        if(0<=die && die <=9 && correct)
        {
            number[10]=die+'0';/* 矫正结果 */
            return true;
        }
        return false;
    }
    return true;
}

void ResultsAnalysis::resultsOfAnalysisSlot(QStringList resultList, int type, const QString &imgTime)
{
    /* 1:22G1 */
    /* 2:45G1 */
    /* 3:双22G1 */
    this->imgTime=imgTime;

    QList<uint32_t> probabilityTemp;/* 置信度 */

    for(auto var:resultList){
        QString con="";        QString iso="";        uint32_t probability=0;        int check=0;
        if(var.startsWith("RESULT")){
            QStringList tmp=var.split(":")[1].split("|");
            if(tmp.count()>=3){
                QString conT=tmp[0].trimmed();
                check=numberCheck(conT);
                con=conT;
                iso=tmp[1];
                probability=tmp[2].toUInt();
            }
        }
        conTemp.append(con);
        isoTemp.append(iso);
        checkConList.append(check);
        probabilityTemp.append(probability);
    }

    /* 双箱，分前3个结果和后3个结果独立处理 */
    int index1=0;    int index2=-1;    uint32_t probability=0;
    if(type==3){
        for (int var = 0; var < 3; ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index1=var;
            }
        }
        probability=0;
        for (int var = 3; var < 6; ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index2=var;
            }
        }
        emit containerSignal(type,conTemp[index1],checkConList[index1],isoTemp[index1],conTemp[index2],checkConList[index2],isoTemp[index2]);
    }
    else {
        for (int var = 0; var < probabilityTemp.count(); ++var) {
            if(probabilityTemp[var]>probability){
                probability=probabilityTemp[var];
                index1=var;
            }
        }
        emit containerSignal(type,conTemp[index1],checkConList[index1],isoTemp[index1]);
    }
    updateDataBase(index1,index2);

    conTemp.clear();
    isoTemp.clear();
    checkConList.clear();
    probabilityTemp.clear();
}

void ResultsAnalysis::updateDataBase(int index1,int index2)
{
    QStringList tmp=imgTime.split(QDir::toNativeSeparators("/"));
    QString dateTime="";
    if(tmp.count()>0){
        dateTime=QDateTime::fromString(tmp[tmp.count()-1].split(".")[0].mid(0,14),"yyyyMMddhhmmss").toString("yyyy-MM-dd hh:mm:ss");
    }

    QMap<QString,QString> data;

    data.insert("Timer",dateTime);
    if(channel!=-1){
         data.insert("Channel",QString::number(channel));
    }

    data["ContainerFront"]=conTemp[index1];
    data["ISOFront"]=isoTemp[index1];
    data["CheckFront"]=QString::number(checkConList[index1]);

    if(index2!=-1){
        data["ContainerAfter"]=conTemp[index2];
        data["ISOAfter"]=isoTemp[index2];
        data["CheckAfter"]=QString::number(checkConList[index2]);
    }

    if(conTemp.count()==4){
        data["ImgFrontNumber"]=conTemp[0];
        data["ImgFrontCheck"]=QString::number(checkConList[0]);
        data["ImgLeftFrontNumber"]=conTemp[1];
        data["ImgLeftFrontCheck"]=QString::number(checkConList[1]);
        data["ImgRightFrontNumber"]=conTemp[2];
        data["ImgRightFrontCheck"]=QString::number(checkConList[2]);
        data["ImgAfterNumber"]=conTemp[3];
        data["ImgAfterCheck"]=QString::number(checkConList[3]);
    }
    else if (conTemp.count()==6) {
        data["ImgFrontNumber"]=conTemp[0];
        data["ImgFrontCheck"]=QString::number(checkConList[0]);
        data["ImgLeftFrontNumber"]=conTemp[1];
        data["ImgLeftFrontCheck"]=QString::number(checkConList[1]);
        data["ImgRightFrontNumber"]=conTemp[2];
        data["ImgRightFrontCheck"]=QString::number(checkConList[2]);
        data["ImgLeftAfterNumber"]=conTemp[3];
        data["ImgLeftAfterCheck"]=QString::number(checkConList[3]);
        data["ImgRightAfterNumber"]=conTemp[4];
        data["ImgRightAfterCheck"]=QString::number(checkConList[4]);
        data["ImgAfterNumber"]=conTemp[5];
        data["ImgAfterCheck"]=QString::number(checkConList[5]);
    }
    emit updateDataBaseSignal(data);
    data.clear();
    tmp.clear();
}
