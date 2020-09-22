#include "captureunderlying.h"

CaptureUnderlying::CaptureUnderlying(QObject *parent)
{
    this->setParent(parent);
    tcpSocket=nullptr;
    pTimerLinkCamer=nullptr;
    pPutCommand=nullptr;

    streamState=false;
    putState=false;
}

CaptureUnderlying::~CaptureUnderlying()
{
    delete  tcpSocket;
    delete pTimerLinkCamer;
    delete pPutCommand;
}

void CaptureUnderlying::connected()
{
    emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1 Camera Link Success").arg(camerIP));
    emit camerStateSingal(camerIP,true,alias);

    if(pTimerLinkCamer->isActive())    /* 防止出现链接完成后,物理线路断开 */
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(15000);
}

void CaptureUnderlying::readFortune()
{    
    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(10000);

    QThread::msleep(10);

    if(!putState){
        /*****************************
        * @brief: 不是当前库抓拍，不处理。防止同一相机多次接收
        ******************************/
        return;
    }

    //tcpSocket = qobject_cast<QTcpSocket*>(sender());
    QByteArray tmpStream = tcpSocket->readAll();
    if(tmpStream!="\x00")
    {
        jpgStream.append(tmpStream);
    }
    /* 找到结尾标记 */
    int end=jpgStream.lastIndexOf("\xFF\xD9");
    if(end!=-1)
    {        
        /* 找到开头标记 */
        int start=jpgStream.indexOf("\xFF\xD8");
        if(start!=-1)
        {
            jpgStream=jpgStream.mid(start,end-start+2);
            emit messageSignal(ZBY_LOG("INFO"), tr("IP:%1 Get Camera Image Data").arg(camerIP));
            emit pictureStreamSignal(jpgStream,imgNumber,imgTime);
            putState=false;
            QThread::msleep(10);            
        }
        else {
            emit pictureStreamSignal(nullptr,imgNumber,imgTime);
            putState=false;
        }
        jpgStream.clear();        
    }

    if(tmpStream.count()>1){
        /*****************************
        * @brief: 防止相机异常，没有结果输出
        ******************************/
         streamState=true;
    }
    qDebug()<<tmpStream.count();
}

void CaptureUnderlying::disconnected()
{
    emit camerStateSingal(camerIP,false,alias);
    emit messageSignal(ZBY_LOG("ERROR") ,tr("%1 Camera Disconnected").arg(camerIP));
}

void CaptureUnderlying::displayError(QAbstractSocket::SocketError socketError)
{
    emit messageSignal(ZBY_LOG("ERROR"), tr("IP:%1 Camera Link Error<errorCode=%2>").arg(camerIP).arg(socketError));

    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(20000);
}

void CaptureUnderlying::startLinkCamer()
{
    if(tcpSocket->state()==QAbstractSocket:: UnconnectedState){
        tcpSocket->abort();
        tcpSocket->connectToHost(camerIP,static_cast<quint16>(camerPort));
        pPutCommand->linktoServerSlot(camerIP,23000);
    }
}

void CaptureUnderlying::cameraState()
{
    if(!streamState)
    {
        /*****************************
        * @brief:保证流程完成
        ******************************/
        emit pictureStreamSignal(nullptr,imgNumber,imgTime);
    }
}

void CaptureUnderlying::initCamerSlot(const QString &camerIP, const int &camerPort, const QString &CamerUser, const QString &CamerPow, const QString &alias)
{
    this->camerIP=camerIP;
    this->camerPort=camerPort;
    this->alias=alias;

    startLinkCamer();
}

bool CaptureUnderlying::putCommandSlot(const int &imgNumber, const QString &imgTime)
{
    this->imgNumber=imgNumber;
    this->imgTime=imgTime;

    putState=true;
    streamState=false;

    qDebug()<<"CaptureUnderlying:tcpSocket:"<<tcpSocket->state();
    emit messageSignal(ZBY_LOG("DEBUG"),"capture");

    if(!pPutCommand->putCommandSlot())
    {
        /*****************************
        * @brief:保证流程完成
        ******************************/
        emit pictureStreamSignal(nullptr,imgNumber,imgTime);
        return false;
    }

    QTimer::singleShot(1000,this,SLOT(cameraState()));
    return true;
}

void CaptureUnderlying::releaseResourcesSlot()
{
    if(pTimerLinkCamer !=nullptr && pTimerLinkCamer->isActive()){
        pTimerLinkCamer->stop();
    }
}

void CaptureUnderlying::InitializationSlot()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,&QIODevice::readyRead,this,&CaptureUnderlying::readFortune);
    connect(tcpSocket,&QAbstractSocket::connected,this,&CaptureUnderlying::connected);
    connect(tcpSocket,&QAbstractSocket::disconnected,this,&CaptureUnderlying::disconnected);
    //connect(tcpSocket,&QAbstractSocket::stateChanged,this,&UnderlyingGetImages::stateChanged);
    connect(tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&CaptureUnderlying::displayError);

    pTimerLinkCamer=new QTimer (this);
    connect(pTimerLinkCamer,&QTimer::timeout,this,&CaptureUnderlying::startLinkCamer);

    pPutCommand=new PutCommand (this);
}
