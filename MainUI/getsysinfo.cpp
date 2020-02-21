#include "getsysinfo.h"
#include "math.h"

#if defined(Q_OS_WIN32)
    #define OS 0
#elif defined(Q_OS_LINUX)
    #define OS 1
#endif

GetSysInfo::GetSysInfo()
{
    status=true;
}

void GetSysInfo::run()
{
    if(!OS){

    }
    else {

        double cpuS=0,cpuE=0,ideS=0,ideE=0;

        QList<QString> msgList;

        while (status) {

            QProcess process;

            ///Mem
            process.start("free -m");
            process.waitForFinished();
            process.readLine();
            QString str=process.readLine();
            ///将连续空格替换为单个空格 用于分割
            str.replace(QRegExp("( ){1,}")," ");
            auto strList=str.split(" ");
            if(strList.size()>6){
                msgList.append(tr("MEM:%1G / %2G").arg(strList[2].toDouble()/1000.0).arg(strList[1].toDouble()/1000.0));
            }

            ///CPU
            process.start("cat /proc/stat");
            process.waitForFinished();
            str = process.readLine();
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            auto strCpu = str.split(" ");
            for(int i=1;i<strCpu.length();i++){
                cpuS+=strCpu[i].toDouble();
                if(i==4){
                    ideS=strCpu[i].toDouble();
                }
            }

            sleep(1);

            process.start("cat /proc/stat");
            process.waitForFinished();
            str = process.readLine();
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            strCpu = str.split(" ");
            for(int i=1;i<strCpu.length();i++){
                cpuE+=strCpu[i].toDouble();
                if(i==4){
                    ideE=strCpu[i].toDouble();
                }
            }
            msgList.append(tr("CPU:%1%").arg(round((1-(ideE-ideS)/(cpuE-cpuS))*100.0)));
            cpuE=0;cpuS=0;ideE=0;ideS=0;

            emit statusMsgSignal(tr("| %1 | %2 |").arg(msgList[0]).arg(msgList[1]));
            msgList.clear();
        }
    }
}

void GetSysInfo::exitWhileSlot(bool status)
{
    this->status=status;
}
