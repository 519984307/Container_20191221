#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    InitializeObject();
    InitializeDataWindow();
    InitializeCamerWindow();
    InitializeOtherWindow();

    setStatusBar();
    loadPlugins();
}

MainWidget::~MainWidget()
{
    foreach (auto thread, ThreadList) {
        thread->terminate();
        thread->wait();
    }

    ItemWidgetMap.clear();
    GetImagePluginList.clear();
    SerialPortPluginList.clear();
    CamerNameList.clear();
    ThreadList.clear();

    delete ui;
}

void MainWidget::InitializeObject()
{
    Setting setting;
    /*
    *读取通道数
    */
    channelCounnt =setting.pSetting->value(tr("MAIN/ChannelNumber")).toInt();
    CamerNameList<<"Before"<<"After"<<"Left"<<"Right"<<"Plate";
}

void MainWidget::InitializeOtherWindow()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while(*it){
        /*
        * 获取设置根
        */
        if((*it)->text(0)=="Setting"){
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("System")));
            (*it)->addChild(childImte);

            ItemWidgetMap.insert(childImte,new SystemSetting(this) );
            for(int i=1;i<=channelCounnt;i++){
                auto sunItem=new QTreeWidgetItem (childImte,QStringList(tr("%1 # Channel").arg(i)));
                /*
                 * 添加子项
                 */
                (*it)->addChild(sunItem);
                ItemWidgetMap.insert(sunItem,new CamerSetting (this));
            }
        }
        if((*it)->text(0)=="Service"){
            /*
              * 获取服务根
            */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Log")));
            (*it)->addChild(childImte);
            ItemWidgetMap.insert(childImte,new ServiceWidget (this));
        }
        if((*it)->text(0)=="Database"){
            /*
             * 获取数据库根
             */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Data")));
            (*it)->addChild(childImte);
            ItemWidgetMap.insert(childImte,new DataBaseWidget (this));
        }
        ++it;
    }
}

void MainWidget::InitializeCamerWindow()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while(*it){
        if((*it)->text(0)=="Camera"){
            /*
             * 获取相机根
             */
            for(int i=1;i<=channelCounnt;i++){
                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
                /*
                 * 添加子项
                 */
                (*it)->addChild(childImte);
                for(auto name:CamerNameList){
                    auto sunItem=new QTreeWidgetItem (childImte,QStringList(name));
                    childImte->addChild(sunItem);

                    PictureWidget *picutre= new PictureWidget (this);
                    CamerWidgetMap.insert(i,picutre);
                    ItemWidgetMap.insert(sunItem,picutre);
                }
            }
        }
        ++it;
    }
}

void MainWidget::InitializeDataWindow()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    while(*it){
        if((*it)->text(0)=="Data"){
            /*
             * 获取数据根
             */
            for(int i=1;i<=channelCounnt;i++){
                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
                /*
                 * 添加子项
                 */
                (*it)->addChild(childImte);

                DataWidget* data=new DataWidget(this);
                DataWidgetMap.insert(i,data);
                ItemWidgetMap.insert(childImte,data);

                if(i==1){
                    /*
                     * 显示第一个窗口
                     */
                    on_treeWidget_itemActivated(childImte);
                }
            }
        }
        ++it;
    }
}

void MainWidget::hideWindows()
{
    for(auto key:ItemWidgetMap.keys()){
        auto value=ItemWidgetMap[key];
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

void MainWidget::setStatusBar()
{
    statusBar=new QStatusBar(this);
    statusBar->setStyleSheet("background-color:rgb(39,39,40);color:red");
    statusBar->addPermanentWidget(new QLabel (tr("CPU:     |"),this));
    statusBar->addPermanentWidget(new QLabel (tr("RAM:     |"),this));
    statusBar->addPermanentWidget(new QLabel (tr("GPU:     |"),this));
    this->ui->gridLayout_2->addWidget(statusBar);
}

void MainWidget::on_treeWidget_itemActivated(QTreeWidgetItem *item)
{
    if(ItemWidgetMap.find(item)==ItemWidgetMap.end()){
        return;
    }

    hideWindows();

    auto value=ItemWidgetMap[item];
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
    for(auto pWidget:ItemWidgetMap){
        if(DataWidget* tmp=qobject_cast<DataWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(CamerSetting* tmp=qobject_cast<CamerSetting*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(SystemSetting* tmp=qobject_cast<SystemSetting*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
    }
}

void MainWidget::loadPlugins()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());

    ///创建插件目录
    const QString pluginPath="plugins";
    if(!pluginsDir.cd(pluginPath)){
        pluginsDir.mkdir(pluginPath);
        pluginsDir.cd(pluginPath);
    }

    const QString path=pluginsDir.path();    
    const QStringList entryList=pluginsDir.entryList(QDir::Files);

    for(const QString &fileName :entryList){
        QPluginLoader  pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if(plugin){
            const QString pluginName=tr("%1").arg(fileName.split(".")[0]);

            ///创建子插件目录
            if(!pluginsDir.cd(pluginName)){
                pluginsDir.mkdir(pluginName);
                pluginsDir.cd(pluginName);
            }
            else {
                ///删除旧插件
                const QFileInfoList fileList=pluginsDir.entryInfoList();
                for(QFileInfo file :fileList){
                    if(file.isFile()){
                        file.dir().remove(file.fileName());
                    }
                }
            }

            QString name=pluginName.split("_")[1];            int num=channelCounnt;
            if(name=="IMG"){
                num=num*4;///每条道4个相机
            }
            else if (name=="GIC") {
                num=num*2;///每条道2个串口
            }

            ///创建新插件
            for(int i=1;i<=num;i++){
                  QFile::copy(QDir::toNativeSeparators(tr("%1/%2").arg(path).arg(fileName)),QDir::toNativeSeparators(tr("%1/%2_%3").arg(pluginsDir.absolutePath()).arg(i).arg(fileName)));
            }

            processingPlugins(pluginsDir);

            ///返回上层目录
            pluginsDir.cdUp();
            delete  plugin;
        }
    }
}

void MainWidget::processingPlugins(QDir path)
{   
    ///加载插件
    const QStringList entryList=path.entryList(QDir::Files);
    for(const QString &fileName :entryList){

        QPluginLoader  pluginLoader(path.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if(plugin){
            if(GetImagesInterface* pGetimagesInterface=qobject_cast<GetImagesInterface*>(plugin)){
                GetImagePluginList.append(pGetimagesInterface);
            }
            if(InfraredlogicInterface* pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)){
                SerialPortPluginList.append(pInfraredlogicInterface);
            }
        }
        else {
            delete  plugin;
        }
    }

    if(GetImagePluginList.count()>0){
        getImagePlugin();
    }
    if(SerialPortPluginList.count()>0){
        serialportPlugin();
    }
}

void MainWidget::getImagePlugin()
{
//    for(int i=1;i<=channelCounnt;i++){
//        DataWidget* pDataWidget=qobject_cast<DataWidget*>(WidgetIntMap[i]);
//        GetImagesInterface* pGetimagesInterface=qobject_cast<GetImagesInterface*>(GetImagePluginMap[i]);

//        connect(pGetimagesInterface,&GetImagesInterface::camerStateSingal,pDataWidget, &DataWidget::camerIDstates);
//        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pDataWidget,&DataWidget::pictureStream);
//        connect(pDataWidget,&DataWidget::initCamer,pGetimagesInterface,&GetImagesInterface::initCamerSlot);
//        connect(pDataWidget,&DataWidget::putCommand,pGetimagesInterface,&GetImagesInterface::putCommandSlot);
//        connect(pGetimagesInterface,&GetImagesInterface::messageSignal,this,&MainWidget::message);

//        ///线程运行
//        QThread* thread=new QThread(this);
//        pGetimagesInterface->moveToThread(thread);
//        thread->start();
//        ThreadList.append(thread);
//    }
}

void MainWidget::serialportPlugin()
{
//    LogicMap.insert(item->child(i),pInfraredlogicInterface);
//    DataWidget* pDataWidget=qobject_cast<DataWidget*>(WidgetMap.value(item->child(i)));

//    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicStatus,pDataWidget,&DataWidget::logicStatus);
//    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicPutImage,pDataWidget,&DataWidget::logicPutImage);
//    connect(pDataWidget,&DataWidget::startSlave,pInfraredlogicInterface,&InfraredlogicInterface::startSlave);
//    connect(pDataWidget,&DataWidget::setAlarmMode,pInfraredlogicInterface,&InfraredlogicInterface::setAlarmMode);
//    connect(pDataWidget,&DataWidget::exitWhile,pInfraredlogicInterface,&InfraredlogicInterface::exitWhile);
//    connect(pInfraredlogicInterface,&InfraredlogicInterface::message,this,&MainWidget::message);
}

void MainWidget::message(const QString &msg)
{
    this->statusBar->showMessage(msg.toLatin1(),6000);
    //qDebug()<<msg.toLatin1();
}
