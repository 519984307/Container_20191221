#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "setting.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    InitializeObject();
    InitializeDataWindow();
    InitializeCamerWindow();
    InitializeOtherWindow();
}

MainWidget::~MainWidget()
{
    widgetMap.clear();
    camerName.clear();

    delete pGetimagesInterface;
    delete ui;
}

void MainWidget::InitializeObject()
{
    Setting setting;
    channelCounnt =setting.pSetting->value(tr("MAIN/ChannelNumber")).toInt();//读取通道数
    camerName<<"Before"<<"After"<<"Left"<<"Right"<<"Plate";

    pGetimagesInterface=nullptr;
}

void MainWidget::InitializeOtherWindow()
{
    QTreeWidgetItem* item=ui->treeWidget->topLevelItem(4);//获取设置根
    auto childImte=new QTreeWidgetItem(item,QStringList(tr("System")));
    item->addChild(childImte);

    widgetMap.insert(childImte,new SystemSetting(this) );
    for(int i=1;i<=channelCounnt;i++){
        auto sunItem=new QTreeWidgetItem (childImte,QStringList(tr("%1 # Channel").arg(i)));
        item->addChild(sunItem);//添加子项
        widgetMap.insert(sunItem,new CamerSetting (this));
    }

    item=ui->treeWidget->topLevelItem(2);//获取服务根
    childImte=new QTreeWidgetItem(item,QStringList(tr("Log")));
    item->addChild(childImte);
    widgetMap.insert(childImte,new ServiceWidget (this));

    item=ui->treeWidget->topLevelItem(3);//获取数据库根
    childImte=new QTreeWidgetItem(item,QStringList(tr("Data")));
    item->addChild(childImte);
    widgetMap.insert(childImte,new DataBaseWidget (this));
}

void MainWidget::InitializeCamerWindow()
{
    QTreeWidgetItem* item=ui->treeWidget->topLevelItem(1);//获取相机根

    for(int i=1;i<=channelCounnt;i++){
        auto childImte=new QTreeWidgetItem (item,QStringList(tr("%1 # Channel").arg(i)));
        item->addChild(childImte);//添加子项
        for(auto name:camerName){
            auto sunItem=new QTreeWidgetItem (childImte,QStringList(name));
            childImte->addChild(sunItem);
            widgetMap.insert(sunItem,new PictureWidget (this));
        }
    }
}

void MainWidget::InitializeDataWindow()
{
    QTreeWidgetItem* item=ui->treeWidget->topLevelItem(0);//获取数据根

    for(int i=1;i<=channelCounnt;i++){
        auto childImte=new QTreeWidgetItem (item,QStringList(tr("%1 # Channel").arg(i)));
        item->addChild(childImte);//添加子项
        widgetMap.insert(childImte,new DataWidget(this));

        if(i==1){//显示第一个窗口
            DataWidget* firstWidget= qobject_cast<DataWidget*>(widgetMap[childImte]);//强制转换成数据窗口
            firstWidget->move(168,80);
            firstWidget->setVisible(true);//显示第一个窗口
        }
    }
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
    //ui->label->setPixmap(*map);

    delete map;
}

void MainWidget::message(const QString &msg)
{
    qDebug()<<msg.toLatin1();
}

void MainWidget::hideWindows()
{
    for(auto key:widgetMap.keys()){
        auto value=widgetMap[key];
        if(DataWidget* tmp=qobject_cast<DataWidget*>(value)){
            tmp->setVisible(false);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(value)){
            tmp->setVisible(false);
        }
         if(CamerSetting* tmp=qobject_cast<CamerSetting*>(value)){
             tmp->setVisible(false);
         }
         if(SystemSetting* tmp=qobject_cast<SystemSetting*>(value)){
             tmp->setVisible(false);
         }
         if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(value)){
             tmp->setVisible(false);
         }
         if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(value)){
             tmp->setVisible(false);
         }
    }
}


void MainWidget::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    qDebug()<<column;

    if(widgetMap.find(item)==widgetMap.end()){
        return;
    }
    hideWindows();
    auto value=widgetMap[item];
    if(value){
        if(DataWidget* tmp=qobject_cast<DataWidget*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(CamerSetting* tmp=qobject_cast<CamerSetting*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(SystemSetting* tmp=qobject_cast<SystemSetting*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
    }
}

void MainWidget::resizeEvent(QResizeEvent *size)
{
    for(auto pWidget:widgetMap){
        if(DataWidget* tmp=qobject_cast<DataWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
        if(CamerSetting* tmp=qobject_cast<CamerSetting*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
        if(SystemSetting* tmp=qobject_cast<SystemSetting*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-80);
        }
    }
}
