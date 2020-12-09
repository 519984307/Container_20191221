#include "resultsanalysis.h"

ResultsAnalysis::ResultsAnalysis(QObject *parent)
{
    this->setParent(parent);
    this->correct=false;
    this->channel=-1;
    sendMid=false;
    initCheckMap();


    QString program="QRecognition";
    QString path=QDir::toNativeSeparators(tr("%1/%2/").arg(QCoreApplication::applicationDirPath()).arg(program));

    QFile file(path+("ISO.txt"),this);
    if(file.open( QIODevice::ReadOnly ) )
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString iso=in.readLine().trimmed();
            if(iso!=""){
                ISOContains.append(iso);
                qDebug()<<iso;
            }
        }
    }
    file.close();

    QFile file1(path+("ISO1.txt"),this);
    if(file1.open( QIODevice::ReadOnly ) )
    {
        QTextStream in(&file1);
        while (!in.atEnd()) {
            QStringList str=in.readLine().trimmed().split('-');
            if(str.count()==2){
                ISOReplaceMap.insert(str[0],str[1]);
            }
        }
    }
    file1.close();
}

ResultsAnalysis::~ResultsAnalysis()
{
    ISOReplaceMap.clear();
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

void ResultsAnalysis::sendMidResultSlot(bool state)
{
    sendMid=state;
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
    if(die==10){
        die=0;
    }
    qDebug()<<"die"<<die;

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

QStringList ResultsAnalysis::queueContainerNumber(QStringList list)
{
    QStringList resultList;
    QMap<int,int> conCountMap;/* 下标和出现次数 */
    QSet<QString> set=list.toSet();/* 去掉重复项 */
    set.remove("");
    QList<QString> tmpList=set.toList();
    if(tmpList.count()==0){
        return resultList;
    }

    if(tmpList.count()>=1){
        for(int i=0;i<tmpList.count();i++){
            int j=0;
            foreach (auto var, list) {
                if(var==tmpList[i]){
                    j+=1;
                    conCountMap.insert(i,j);
                }
            }
        }
    }

    QList<int> tmp=conCountMap.values();
    std::sort(tmp.begin(), tmp.end());


    if(!tmp.isEmpty() && tmp.last()>1){
        QList<int> indList= conCountMap.keys(tmp.last());
        foreach (auto var, indList) {
            resultList.append(tmpList.value(var));
        }
    }

    tmp.clear();
    tmpList.clear();
    set.clear();
    conCountMap.clear();

    return  resultList;
}

void ResultsAnalysis::resultsOfAnalysisSlot(QStringList resultList, int type, QStringList imgList)
{   
    /* 外发协议,集装箱类别:
     * -1 – 未知
     * 0 – 一个 20 集装箱
     * 1 – 一个 40 吋/45 吋集装箱
     * 2 – 两个 20 吋集装箱
     */

    QList<uint32_t> conProbabilityTemp;/* 箱号置信度 */
    QList<uint32_t> isoProbabilityTemp;/* 箱型置信度 */   

    for(auto var:resultList){
        QString con=""; QString iso=""; uint32_t Cprobability=0;  uint32_t Iprobability=0;   int check=0;
        if(var.startsWith("RESULT")){
            QStringList tmp=var.split(":")[1].split("|");
            if(tmp.count()==4){
                //con="BSIU9815070";
                con=tmp[0].trimmed();
                check=numberCheck(con);
                if(ISOContains.count()!=0 || ISOReplaceMap.count()!=0){/* 比对箱型结果 */
                    if(ISOContains.indexOf(tmp[1])==-1){
                        iso=ISOReplaceMap.value(tmp[1],"");/* 匹配不成功,置空  */
                        if(iso==""){
                            Iprobability=0;/* 箱型置信度置零 */
                        }
                        else {
                            Iprobability=tmp[3].toUInt();
                        }
                    }
                    else {
                        iso=tmp[1];
                        Iprobability=tmp[3].toUInt();
                    }
                }
                else {
                    iso=tmp[1];
                    Iprobability=tmp[3].toUInt();
                }
                Cprobability=tmp[2].toUInt();
            }
        }
        conTemp.append(con);/* 箱号 */
        isoTemp.append(iso);/* 箱型 */
        checkConList.append(check);/* 校验结果 */
        conProbabilityTemp.append(Cprobability);/* 箱号置信度 */
        isoProbabilityTemp.append(Iprobability);/* 箱型置信度 */
    }

    bool notISO=true;/* 没有识别到箱型代码就默认指定一个 */
    foreach (auto var, isoTemp) {
        if(var!=""){
            notISO=false;
            break;
        }
    }
    if(notISO){
        switch (type) {
        case 0:
            if(isoTemp.count()==4){
                isoTemp[0]="22G1";
            }
            break;
        case 1:
            if(isoTemp.count()==6){
                isoTemp[0]="45G1";
            }
            break;
        case 2:
            if(isoTemp.count()==6){
                isoTemp[0]="22G1";
                isoTemp[3]="22G1";
            }
            break;
        }
    }
    else {
        if(isoTemp.count()==6){/* 过滤双箱误判成长箱,系统改正双箱 */
            foreach (auto var, isoTemp) {
                if(var.startsWith("22")){
                    type=2;
                    break;
                }
            }
//            if(type!=2){/* 系统修正为长箱 */
//                type=1;
//            }
        }
    }

    /*****************************
    * @brief: 时间戳
    ******************************/
    QString time;
    if(imgList.count()>0){
        time=imgList[0].mid(0,14);
    }

    QString dateTime=QDateTime::fromString(time,"yyyyMMddhhmmss").toString("yyyy-MM-dd hh:mm:ss");
    /*///////////////////////////////////////////////////*/


    /* 双箱，分前3个结果和后3个结果独立处理,前箱下标,前箱型下标,后箱下标,后箱型下标,箱号置信度下表,箱型置信度下标 */
    int Cindex1=0;    int Iindex1=0;    int Cindex2=0;    int Iindex2=0;    uint32_t Cprobability=0;    uint32_t Iprobability=0;
    if(type==2 && conProbabilityTemp.count()==6){
        /*****************************
        * @brief:20201203 11：52
        ******************************/
        QStringList numberList=queueContainerNumber(conTemp.mid(3));
        if(numberList.count()==1){/* 有多组相同箱号，分析置信度和校验*/
            for (int var = 3; var < 6; ++var) {
                if(numberList[0]==conTemp[var]){
                    Cindex1=var;
                }
            }
        }
        else {
            int i=0;
            for (int var = 3; var < 6; ++var) {/* 箱号校验 */
                if(checkConList[var]){/* 只有一个检验正确，直接输出 */
                    Cindex1=var;
                    i++;
                }
                if(isoProbabilityTemp[var]>Iprobability){
                    Iprobability=isoProbabilityTemp[var];/* 比对箱型置信度 */
                    Iindex1=var;
                }
            }
            if(i>1){
                for (int var = 3; var < 6; ++var) {/* 箱号校验正确大于1个，对比置信度 */
                    if(checkConList[var] && conProbabilityTemp[var]>Cprobability){
                        Cindex1=var;
                    }
                }
            }
            if(i==0){/* 箱号校验都错，直接对比置信度 */
                for (int var = 3; var < 6; ++var) {
                    if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
                        Cprobability=conProbabilityTemp[var];
                        Cindex1=var;
                    }
                }
            }

        }


        Cprobability=0; Iprobability=0;//checkCon=false;
        numberList.clear();
        numberList=queueContainerNumber(conTemp.mid(0,3));
        if(numberList.count()==1){/* 有多组相同箱号，分析置信度和校验*/
            for (int var = 0; var < 3; ++var) {
                if(numberList[0]==conTemp[var]){
                    Cindex2=var;
                }
            }
        }
        else {
            int i=0;
            for (int var = 0; var < 3; ++var) {/* 箱号校验 */
                if(checkConList[var]){/* 只有一个检验正确，直接输出 */
                    Cindex2=var;
                    i++;
                }
                if(isoProbabilityTemp[var]>Iprobability){
                    Iprobability=isoProbabilityTemp[var];/* 比对箱型置信度 */
                    Iindex2=var;
                }
            }
            if(i>1){
                for (int var = 0; var < 3; ++var) {/* 箱号校验正确大于1个，对比置信度 */
                    if(checkConList[var] && conProbabilityTemp[var]>Cprobability){
                        Cindex2=var;
                    }
                }
            }
            if(i==0){/* 箱号校验都错，直接对比置信度 */
                for (int var = 0; var < 3; ++var) {
                    if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
                        Cprobability=conProbabilityTemp[var];
                        Cindex2=var;
                    }
                }
            }

        }


        if(conTemp[Cindex1]==conTemp[Cindex2] && !conTemp[Cindex1].isEmpty()){/* 前后相同修正长箱 */
            type=1;
            /*****************************
            * @brief:时间戳供车牌使用(+"@"+dateTime+"@"+channel)
            ******************************/
            if(isoTemp[Iindex1]==""){
                isoTemp[Iindex1]="45G1";
            }
            emit containerSignal(type,conTemp[Cindex1]+"@"+dateTime+"@"+channel,checkConList[Cindex1],isoTemp[Iindex1]);
            Cindex2=0;
            Iindex2=0;
        }
        else {
            /*****************************
            * @brief:时间戳供车牌使用(+"@"+dateTime+"@"+channel)
            ******************************/
            if(isoTemp[Iindex1]==""){
                isoTemp[Iindex1]="22G1";
            }
            if(isoTemp[Iindex2]==""){
                isoTemp[Iindex2]="22G1";
            }
            emit containerSignal(type,conTemp[Cindex1]+"@"+dateTime+"@"+channel, checkConList[Cindex1],isoTemp[Iindex1],conTemp[Cindex2],checkConList[Cindex2],isoTemp[Iindex2]);
        }
//        Cprobability=0; Iprobability=0;//checkCon=false;
//        for (int var = 0; var < 3; ++var) {
//            if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
//                Cprobability=conProbabilityTemp[var];
//                Cindex2=var;
//            }
//            if(isoProbabilityTemp[var]>Iprobability){/* 比对箱型置信度 */
//                Iprobability=isoProbabilityTemp[var];
//                Iindex2=var;
//            }
//            if(checkConList[var]){
//                Cindex2=var;/* 结果为真,不比对置信读 */
//                checkCon=true;
//                continue;
//            }
//            else if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
//                if(!checkCon){/* 有正确结果后续不再比对 */
//                    Cprobability=conProbabilityTemp[var];
//                    Cindex2=var;
//                }
//            }
//        }

//        /*****************************
//        * @brief:时间戳供车牌使用(+"@"+dateTime+"@"+channel)
//        ******************************/
//        emit containerSignal(type,conTemp[Cindex1]+"@"+dateTime+"@"+channel, checkConList[Cindex1],isoTemp[Iindex1],conTemp[Cindex2],checkConList[Cindex2],isoTemp[Iindex2]);
    }
    else {
        //bool checkCon=false;
        QStringList numberList=queueContainerNumber(conTemp);
        if(numberList.count()==1){/* 有多组相同箱号，分析置信度和校验*/
            for (int var = 0; var < conTemp.count(); ++var) {
                if(numberList[0]==conTemp[var]){
                    Cindex1=var;
                }
            }
        }
        else {
            int i=0;
            for (int var = 0; var < checkConList.count(); ++var) {/* 箱号校验 */
                if(checkConList[var]){/* 只有一个检验正确，直接输出 */
                    Cindex1=var;
                    i++;
                }
                if(isoProbabilityTemp[var]>Iprobability){
                    Iprobability=isoProbabilityTemp[var];/* 比对箱型置信度 */
                    Iindex1=var;
                }
            }
            if(i>1){
                for (int var = 0; var < checkConList.count(); ++var) {/* 箱号校验正确大于1个，对比置信度 */
                    if(checkConList[var] && conProbabilityTemp[var]>Cprobability){
                        Cindex1=var;
                    }
                }
            }
            if(i==0){/* 箱号校验都错，直接对比置信度 */
                for (int var = 0; var < checkConList.count(); ++var) {
                    if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
                        Cprobability=conProbabilityTemp[var];
                        Cindex1=var;
                    }
                }
            }

        }

//        else {//202012042145
//            bool checkCon=false;
//            for (int var = 0; var < conProbabilityTemp.count(); ++var) {
//                if(conProbabilityTemp[var]>Cprobability){/* 比对箱号置信度 */
//                    Cprobability=conProbabilityTemp[var];
//                    Cindex1=var;
//                    checkCon=false;
//                }
//                else if (conProbabilityTemp[var]==Cprobability) {
//                    checkCon=true;
//                }

//                if(isoProbabilityTemp[var]>Iprobability){
//                    Iprobability=isoProbabilityTemp[var];/* 比对箱型置信度 */
//                    Iindex1=var;
//                }
//            }
//            if(checkCon){/* 多个置信度多个相同，比较校验位 */
//                for (int var = 0; var < conProbabilityTemp.count(); ++var) {
//                    if(conProbabilityTemp[var]==Cprobability){
//                        if(checkConList[var]){
//                            Cindex1=var;
//                            continue;
//                        }
//                    }
//                }
//            }
//        }

//        for (int var = 0; var < conProbabilityTemp.count(); ++var) {
//            if(conProbabilityTemp[var]>Cprobability){/* 对比箱号置信度 */
//                Cprobability=conProbabilityTemp[var];
//                Cindex1=var;
//            }
//            if(isoProbabilityTemp[var]>Iprobability){
//                Iprobability=isoProbabilityTemp[var];
//                Iindex1=var;
//            }
//            if(checkConList[var]){
//                Cindex1=var;/* 结果为真,不比对置信读 */
//                checkCon=true;
//                continue;
//            }
//            else if(conProbabilityTemp[var]>Cprobability){
//                if(!checkCon){/* 有正确结果后续不再比对 */
//                    Cprobability=conProbabilityTemp[var];
//                    Cindex1=var;
//                }
//            }
//        }

        /*****************************
        * @brief:时间戳供车牌使用(+"@"+dateTime+"@"+channel)
        ******************************/
        if(isoTemp[Iindex1]==""){
            isoTemp[Iindex1]="45G1";
        }
        emit containerSignal(type,conTemp[Cindex1]+"@"+dateTime+"@"+channel,checkConList[Cindex1],isoTemp[Iindex1]);
    }
    updateDataBase(type,Cindex1,Iindex1,Cindex2,Iindex2,imgList);

    resultList.clear();
    conTemp.clear();
    isoTemp.clear();
    checkConList.clear();
    conProbabilityTemp.clear();
    isoProbabilityTemp.clear();
}

void ResultsAnalysis::updateDataBase(int type, int Cindex1,int Iindex1, int Cindex2, int Iindex2,QStringList imgList)
{    
    QString time;
    if(imgList.count()>0){
        time=imgList[0].mid(0,14);
    }

    QString dateTime=QDateTime::fromString(time,"yyyyMMddhhmmss").toString("yyyy-MM-dd hh:mm:ss");

    emit resultsAnalysisStateSignal(channel,tr("%1 start").arg(dateTime));/* 日志起始 */

    /* Tupe,集装箱类别:
     * -1 – 未知
     * 0 – 一个 20 集装箱
     * 1 – 一个 40 吋/45 吋集装箱
     * 2 – 两个 20 吋集装箱
     */

    QMap<int,int> indMap;
    for (int ind = 0; ind < imgList.count(); ++ind) {
        indMap.insert(imgList[ind].mid(14,1).toInt(),ind);
        qDebug()<<imgList[ind].mid(14,1).toInt();
    }

    for (int var = 0; var < conTemp.count(); ++var) {
        /* 识别结果写入日志,[标志|时间戳|通道号(2位)|相机号(2位)|箱号|校验|箱型] */
        QString result=QString("[%1|%2|%3|%4|%5|%6|%7]\r\n").arg("I").arg(time).arg(channel,2,10,QLatin1Char('0')).arg(indMap.key(var),2,10,QLatin1Char('0')).arg(conTemp[var]).arg(checkConList[var]?"Y":"N").arg(isoTemp[var]);
        emit resultsAnalysisStateSignal(channel,result);
        if(!sendMid){
            emit sendResultSignal(channel,result);
        }
    }

    if(type==2){
        /* 识别结果写入日志,[标志|时间戳|通道号(2位)|逻辑|箱号|校验|箱号|校验|箱型|箱型] */
        QString result=QString("[%1|%2|%3|%4|%5|%6|%7|%8|%9|%10]").arg("C").arg(time).arg(channel,2,10,QLatin1Char('0')).arg(type).arg(conTemp[Cindex1]).arg(checkConList[Cindex1]?"Y":"N").arg(conTemp[Cindex2]).arg(checkConList[Cindex2]?"Y":"N").arg(isoTemp[Iindex1]).arg(isoTemp[Iindex2]);
        emit resultsAnalysisStateSignal(channel,result);

        //-------------------

        //emit sendResultSignal(channel,result);
        /* dataWidget发送，这里不发送 */

        //------------------


    }
    else {
        /* 识别结果写入日志,[标志|时间戳|通道号(2位)|逻辑|箱号|校验|箱型]*/
        QString result=QString("[%1|%2|%3|%4|%5|%6|%7]").arg("C").arg(time).arg(channel,2,10,QLatin1Char('0')).arg(type).arg(conTemp[Cindex1]).arg(checkConList[Cindex1]?"Y":"N").arg(isoTemp[Iindex1]);
        emit resultsAnalysisStateSignal(channel,result);


        //----------------------

        //emit sendResultSignal(channel,result);
        /* dataWidget发送，这里不发送 */



        //------------------------

    }

    QMap<QString,QString> data;
    data.insert("Timer",dateTime);
    if(channel!=-1){
         data.insert("Channel",QString::number(channel));
    }

    data["Type"]=QString::number(type);
    data["ContainerFront"]=conTemp[Cindex1];
    data["ISOFront"]=isoTemp[Iindex1];
    data["CheckFront"]=QString::number(checkConList[Cindex1]);

    if(type==2){
        data["ContainerAfter"]=conTemp[Cindex2];
        data["ISOAfter"]=isoTemp[Iindex2];
        data["CheckAfter"]=QString::number(checkConList[Cindex2]);
    }

    if(conTemp.count()==4){
        data["ImgFrontNumber"]=conTemp[indMap.value(1)];
        data["ImgFrontCheck"]=QString::number(checkConList[indMap.value(1)]);
        data["ImgLeftFrontNumber"]=conTemp[indMap.value(3)];
        data["ImgLeftFrontCheck"]=QString::number(checkConList[indMap.value(3)]);
        data["ImgRightFrontNumber"]=conTemp[indMap.value(2)];
        data["ImgRightFrontCheck"]=QString::number(checkConList[indMap.value(2)]);
        data["ImgAfterNumber"]=conTemp[indMap.value(6)];
        data["ImgAfterCheck"]=QString::number(checkConList[indMap.value(6)]);
    }
    else if (conTemp.count()==6) {
        data["ImgFrontNumber"]=conTemp[indMap.value(1)];
        data["ImgFrontCheck"]=QString::number(checkConList[indMap.value(1)]);
        data["ImgLeftFrontNumber"]=conTemp[indMap.value(3)];
        data["ImgLeftFrontCheck"]=QString::number(checkConList[indMap.value(3)]);
        data["ImgRightFrontNumber"]=conTemp[indMap.value(2)];
        data["ImgRightFrontCheck"]=QString::number(checkConList[indMap.value(2)]);
        data["ImgLeftAfterNumber"]=conTemp[indMap.value(5)];
        data["ImgLeftAfterCheck"]=QString::number(checkConList[indMap.value(5)]);
        data["ImgRightAfterNumber"]=conTemp[indMap.value(4)];
        data["ImgRightAfterCheck"]=QString::number(checkConList[indMap.value(4)]);
        data["ImgAfterNumber"]=conTemp[indMap.value(6)];
        data["ImgAfterCheck"]=QString::number(checkConList[indMap.value(6)]);
    }

    emit updateDataBaseSignal(data);
    data.clear();
    indMap.clear();
    //tmp.clear();
}
