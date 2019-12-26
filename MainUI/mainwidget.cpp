#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    pGetimagesInterface=nullptr;

  loadPlugin();
    initCamer("192.168.1.101",23001);
}

MainWidget::~MainWidget()
{
    delete pGetimagesInterface;
    delete ui;
}

void MainWidget::loadPlugin()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");

    const QStringList entryList=pluginsDir.entryList(QDir::Files);
    for(const QString &fileName :entryList){
        QPluginLoader  pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if(plugin){
                processingPlug(plugin);
            }
        else {
            delete  plugin;
        }
    }
}

void MainWidget::processingPlug(QObject *plugin)
{
     pGetimagesInterface=qobject_cast<GetImagesInterface *>(plugin) ;
    if(pGetimagesInterface){
        connect(pGetimagesInterface,&GetImagesInterface::camerStateSingal,this,&MainWidget::camerIDstates);
        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,this,&MainWidget::pictureStream);
        connect(this,&MainWidget::initCamer,pGetimagesInterface,&GetImagesInterface::initCamerSlot);
        connect(this,&MainWidget::putCommand,pGetimagesInterface,&GetImagesInterface::putCommandSlot);
        connect(pGetimagesInterface,&GetImagesInterface::messageSignal,this,&MainWidget::message);
    }
}

void MainWidget::camerIDstates(const QString &camerIP, bool state)
{
}

void MainWidget::pictureStream(const QByteArray &jpgStream, const QString &camerIP)
{   
    QPixmap *map = new QPixmap();
    map->loadFromData(jpgStream);
    ui->label->setPixmap(*map);

    delete map;
}

void MainWidget::message(const QString &msg)
{
    qDebug()<<msg.toLatin1();
}

void MainWidget::on_pushButton_clicked()
{
    if( putCommand(tr("capture 10\n")))
    {
        qDebug()<<1;
    }
}
