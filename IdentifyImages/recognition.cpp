#include "recognition.h"

Recognition::Recognition(QObject *parent, const QString &image) : QObject(parent)
{
    this->setAutoDelete(true);
    this->setParent(parent);
    this->image=image;
}

void Recognition::run()
{
    QProcess Process;
    QString program="QRecognition.exe";
    Process.setWorkingDirectory(QDir::toNativeSeparators(tr("%1/%2").arg(QCoreApplication::applicationDirPath()).arg(program.split(".")[0])));
    Process.start(program,QStringList()<<image<<"QRecog.dll");
    if(!Process.waitForStarted()){
        emit messageSignal(ZBY_LOG("ERROR"),tr("Recognizer startup error<errorCode=%1>").arg(Process.errorString().toLocal8Bit().data()));
    }
    else {
        /* 停止写入 */
        Process.closeWriteChannel();
        /* 等待识别结果 */
        if(Process.waitForFinished()){
            QByteArray result= Process.readAll();
            emit recognitionResultSignal(result.data(),image);
            emit messageSignal(ZBY_LOG("INFO"),tr("Identify the results:%1").arg(result.data()));
            //QList<QByteArray> list= result.split('|');
        }
        else {
            emit messageSignal(ZBY_LOG("ERROR"),tr("Identify the mistakes error<errorCode=%1>").arg(Process.errorString().toLocal8Bit().data()));
        }
    }
}
