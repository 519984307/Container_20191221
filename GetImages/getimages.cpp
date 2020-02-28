#include "getimages.h"

GetImages::GetImages(QObject *parent)
{
    this->setParent(parent);

    tcpSocket=new QTcpSocket(this);
    pTimerLinkCamer=new QTimer (this);

    connect(tcpSocket,&QIODevice::readyRead,this,&GetImages::readFortune);
    connect(tcpSocket,&QAbstractSocket::connected,this,&GetImages::connected);
    connect(tcpSocket,&QAbstractSocket::disconnected,this,&GetImages::disconnected);
    connect(tcpSocket,&QAbstractSocket::stateChanged,this,&GetImages::stateChanged);
    connect(tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&GetImages::displayError);

    connect(pTimerLinkCamer,&QTimer::timeout,this,&GetImages::startLinkCamer);
}

GetImages::~GetImages()
{
    jpgStream.clear();
    delete tcpSocket;
    delete pTimerLinkCamer;
}

void GetImages::initCamerSlot(const QString &camerIP, quint16 camerPort,const QString &user,const QString &pow)
{
    this->camerIP=camerIP;
    this->camerPort=camerPort;


    startLinkCamer();
}

void GetImages::startLinkCamer()
{
    tcpSocket->abort();
    tcpSocket->connectToHost(camerIP,camerPort);
}

void GetImages::connected()
{
    emit messageSignal(tr("%1 Camera link successful").arg(camerIP));
    emit camerStateSingal(camerIP,true);

    if(pTimerLinkCamer->isActive())//防止出现链接完成后,物理线路断开
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(25000);
}

void GetImages::disconnected()
{
    emit camerStateSingal(camerIP,false);

    //emit message(tr("%1 Camera link disconnected").arg(id));
}

bool GetImages::putCommandSlot(const int &command)
{
    if(tcpSocket->isValid()){
        const char * str_data="capture 01 ";
        tcpSocket->write(str_data);
        return(tcpSocket->flush());
    }
    return (false);
}

void GetImages::playStreamSlot(uint winID,bool play)
{
}

void GetImages::resizeEventSlot()
{

}

void GetImages::closeStreamSlot()
{

}

void GetImages::stateChanged(QAbstractSocket::SocketState socketState)
{
    emit messageSignal(tr("%1 Camera link state is %2").arg(camerIP).arg(socketState));
}

void GetImages::readFortune()
{
    tcpSocket = qobject_cast<QTcpSocket*>(sender());
    QByteArray tmpStream = tcpSocket->readAll();

    if(tmpStream!="\x00")
    {
        jpgStream.append(tmpStream);
    }

    int end=jpgStream.lastIndexOf("\xFF\xD9");//找到结尾标记
    if(end!=-1)
    {
        int start=jpgStream.indexOf("\xFF\xD8");//找到开头标记
        if(start!=-1)
        {
            jpgStream=jpgStream.mid(start,end-start+2);

            emit messageSignal(tr("%1 Get camera image data").arg(camerIP));
            emit pictureStreamSignal(jpgStream,-1);
            QThread::msleep(10);
        }
        jpgStream.clear();
    }

    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(20000);
}

//链接错误槽
void GetImages::displayError(QAbstractSocket::SocketError socketError)
{
    emit messageSignal(tr("%1 Camera link error is %2").arg(camerIP).arg(socketError));

    if(pTimerLinkCamer->isActive())
    {
        pTimerLinkCamer->stop();
    }
    pTimerLinkCamer->start(10000);
}

