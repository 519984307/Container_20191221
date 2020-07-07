#include "socketclient.h"

SocketClient::SocketClient(QObject *parent)
{
    this->setParent(parent);

    land=-1;/* 默认通道号 */

    connect(this,SIGNAL(readyRead()),this,SLOT(readClientSlot()));
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}

void SocketClient::readClientSlot()
{
    /* 读取客户端数据 */
    QByteArray buf=readAll();

    qDebug()<<this->socketDescriptor();

    if(buf.startsWith('[')){
        QList<QByteArray> tmp=buf.split('|');
        if(tmp.count()==2){
            if(tmp[0].indexOf('L')!=-1){/* 找到设置通道标标志位 */
                land=tmp[1].split(']')[0].toInt();
                emit setClientLandSignal(land,this->socketDescriptor());
            }
            else if (tmp[0].indexOf('R')!=-1) {/* 找到取结果标志位 */
                emit getLastResultSignal(this->socketDescriptor());
//                if(tmp[1].split(']')[0].toInt()==land){/* 暂时不区分通道号 */
//                    emit getLastResultSignal(this->socketDescriptor());
//                }
            }
        }
    }
}
