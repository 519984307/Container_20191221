#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    pDataBaseCorrelation=new DataBaseCorrelation () ;

    InitializeSystemSet();
    InitializeDataWindow();
    InitializeCamerWindow();
    InitializeOtherWindow();
    InitializeChannelSet();

    loadPlugins();
    bindCamerObjects();
    setStatusBar();
    //initSysInfo();

    /* test */
//    for(auto b:ImageProcessingMap.values()){
//        if(ImageProcessing* pImageProcessing=static_cast<ImageProcessing*>(b)){
//            emit pImageProcessing->initCamerSignal("192.168.1.100",8000,"admin","Zby123456");
//        }
//    }
//    for(auto a :LogicalProcessingMap.values()){
//        if(LogicalProcessing* pLogicalProcessing=static_cast<LogicalProcessing*>(a)){
//            emit pLogicalProcessing->startSlaveSignal("com4","com5");
//        }
//    }
//    if(ImageProcessing* pImageProcessing=static_cast<ImageProcessing*>(ImageProcessingMap[1])){
//        emit pImageProcessing->initCamerSignal("192.168.1.100",8000,"admin","Zby123456");
//    }
//    if(ImageProcessing* pImageProcessing=static_cast<ImageProcessing*>(ImageProcessingMap[2])){
//        emit pImageProcessing->initCamerSignal("192.168.1.100",8000,"admin","Zby123456");
//    }
//    if(ImageProcessing* pImageProcessing=static_cast<ImageProcessing*>(ImageProcessingMap[3])){
//        emit pImageProcessing->initCamerSignal("192.168.1.100",8000,"admin","Zby123456");
//    }
//    if(ImageProcessing* pImageProcessing=static_cast<ImageProcessing*>(ImageProcessingMap[4])){
//        emit pImageProcessing->initCamerSignal("192.168.1.100",8000,"admin","Zby123456");
//    }
//    if(LogicalProcessing* pLogicalProcessing=static_cast<LogicalProcessing*>(LogicalProcessingMap[1])){
//        emit pLogicalProcessing->startSlaveSignal("com4","com5");
//    }
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    emit closeStreamSignal();
    emit exitWhileSignal(true);

//    pGetSysInfo->quit();
//    pGetSysInfo->wait();

    foreach (auto thread, ThreadList) {
        thread->quit();
        thread->wait();
    }
}

MainWidget::~MainWidget()
{
    for(auto obj:ImageProcessingMap.values()){
        delete obj;
    }
    for(auto obj:LogicalProcessingMap.values()){
        delete obj;
    }
    for(auto obj:CamerWidgetMap.values()){
        delete obj;
    }
    for(auto obj:DataWidgetMap.values()){
        delete obj;
    }
    for(auto obj:ChannelSettingWidgetMap.values()){
        delete obj;
    }

    ImageProcessingMap.clear();
    LogicalProcessingMap.clear();
    ThreadList.clear();
    ItemWidgetMap.clear();
    DataWidgetMap.clear();
    CamerWidgetMap.clear();
    CamerNameList.clear();
    channelCamerMultiMap.clear();
    ChannelSettingWidgetMap.clear();

//    delete  statusBar;
//    delete pStatusBarLabel;
    //delete pGetSysInfo;

    delete ui;
}

void MainWidget::InitializeSystemSet()
{
    pSystemSettingWidget=new SystemSettingWidget (this);
    channelCounnt=pSystemSettingWidget->ChannelNumber;
    CamerNameList<<"Before"<<"After"<<"Left"<<"Right";
    //CamerNameList<<"Before"<<"After"<<"Left"<<"Right"<<"Plate";
}

void MainWidget::InitializeDataWindow()
{
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){
        if((*it)->text(0)=="Data"){
            /*  获取数据根   */
            for(int i=1;i<=channelCounnt;i++){
                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
                /*  添加子项    */
                (*it)->addChild(childImte);

                DataWidget* data=new DataWidget(this);
                DataWidgetMap.insert(i,data);
                ItemWidgetMap.insert(childImte,data);

                if(i==1){
                    /*  显示第一个窗口 */
                    on_Navigation_itemActivated(childImte);
                }
            }
        }
        ++it;
    }
}

void MainWidget::InitializeCamerWindow()
{
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){
        if((*it)->text(0)=="Camera"){
            /*  获取相机根   */
            int j=1;
            for(int i=1;i<=channelCounnt;i++){
                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
                /*  添加子项    */
                (*it)->addChild(childImte);
                for(auto name:CamerNameList){
                    auto sunItem=new QTreeWidgetItem (childImte,QStringList(name));
                    childImte->addChild(sunItem);
                    PictureWidget *picutre= new PictureWidget (this);
                    /* 通道对应的几个相机 */
                    channelCamerMultiMap.insert(i,picutre);

                    /*  过滤车牌界面,车牌暂时不用海康SDK  */
                    if(name!="Plate"){
                        CamerWidgetMap.insert(j,picutre);
                        j++;
                    }
                    ItemWidgetMap.insert(sunItem,picutre);
                }
            }
        }
        ++it;
    }
}

void MainWidget::InitializeOtherWindow()
{
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){        
        if((*it)->text(0)=="Setting"){
            /*  获取设置根   */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("System")));
            (*it)->addChild(childImte);

           // ItemWidgetMap.insert(childImte,new SystemSettingWidget(this) );
            ItemWidgetMap.insert(childImte,pSystemSettingWidget);
            for(int i=1;i<=channelCounnt;i++){
                auto sunItem=new QTreeWidgetItem (childImte,QStringList(tr("%1 # Channel").arg(i)));
                /*  添加子项    */
                (*it)->addChild(sunItem);
                ChannelSettingWidget* pChannelSettingWidget=new ChannelSettingWidget (i,this);/* 构造参数通道编号 */
                ChannelSettingWidgetMap.insert(i,pChannelSettingWidget);
                ItemWidgetMap.insert(sunItem,pChannelSettingWidget);
            }
        }
        if((*it)->text(0)=="Service"){
            /*  获取服务根   */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Log")));
            (*it)->addChild(childImte);
            ItemWidgetMap.insert(childImte,new ServiceWidget (this));
        }
        if((*it)->text(0)=="Database"){
            /*  获取数据库根  */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Data")));
            (*it)->addChild(childImte);
            ItemWidgetMap.insert(childImte,new DataBaseWidget (this));
        }
        ++it;
    }
}

void MainWidget::InitializeChannelSet()
{
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){
        if((*it)->text(0)=="Data"){
            for (int i=1;i<=channelCounnt;i++) {
                if(ChannelSettingWidget* pChannelSettingWidget=static_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                    if(!pChannelSettingWidget->Alias.isEmpty()){
                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);

                    }
                }
            }
            //break;
        }
        if((*it)->text(0)=="Camera"){
            for (int i=1;i<=channelCounnt;i++) {
                if(ChannelSettingWidget* pChannelSettingWidget=static_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                    if(!pChannelSettingWidget->Alias.isEmpty()){
                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);

                    }
                }
            }
            break;
        }
        ++it;
    }
}

void MainWidget::loadPlugins()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());

    /*  创建插件目录  */
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

            /*  创建子插件目录 */
            if(!pluginsDir.cd(pluginName)){
                pluginsDir.mkdir(pluginName);
                pluginsDir.cd(pluginName);
            }
            else {
                /*  删除旧插件   */
                const QFileInfoList fileList=pluginsDir.entryInfoList();
                for(QFileInfo file :fileList){
                    if(file.isFile()){
                        file.dir().remove(file.fileName());
                    }
                }
            }

            QString name=pluginName.split("_")[1];
            int num=channelCounnt;
            if(name=="IMG"){
                num=num*4;/* 每条道4个相机,车牌相机车外. */
            }
            else if (name=="GIC") {
                ;/* 每条道2个串口共用一个插件.  */
            }
            else {
                /* 暂时不处理其他插件 */
                /*  返回上层目录  */
                pluginsDir.cdUp();
                continue;
            }

            /*  复制新插件   */
            for(int i=1;i<=num;i++){
                  QFile::copy(QDir::toNativeSeparators(tr("%1/%2").arg(path).arg(fileName)),QDir::toNativeSeparators(tr("%1/%2_%3").arg(pluginsDir.absolutePath()).arg(i).arg(fileName)));
            }

            processingPlugins(pluginsDir,num);

            /*  返回上层目录  */
            pluginsDir.cdUp();
        }
        delete  plugin;
    }
}

void MainWidget::processingPlugins(QDir path, int num)
{
    /* 加载插件 */
    const QStringList entryList=path.entryList(QDir::Files);
    for(const QString &fileName :entryList){

        QPluginLoader  pluginLoader(path.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if(plugin){
            if(GetImagesInterface* pGetimagesInterface=qobject_cast<GetImagesInterface*>(plugin)){
                getImagePlugin(pGetimagesInterface,num--);
            }
            if(InfraredlogicInterface* pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)){
                serialportPlugin(pInfraredlogicInterface,num--);
            }
        }
        else {
            delete  plugin;
        }
    }
}

void MainWidget::getImagePlugin(GetImagesInterface *pGetimagesInterface, int num)
{
    PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(CamerWidgetMap[num]);

    ImageProcessing* pImageProcessing=new ImageProcessing (nullptr);
    ImageProcessingMap.insert(num,pImageProcessing);

    connect(this,&MainWidget::closeStreamSignal,pGetimagesInterface,&GetImagesInterface::closeStreamSlot,Qt::BlockingQueuedConnection);

    connect(pPictureWidget,&PictureWidget::putCommandSignal,pGetimagesInterface,&GetImagesInterface::putCommandSlot);
    connect(pPictureWidget,&PictureWidget::resizeEventSignal,pGetimagesInterface,&GetImagesInterface::resizeEventSlot);
    connect(pPictureWidget, &PictureWidget::playStreamSignal,pGetimagesInterface,&GetImagesInterface::playStreamSlot);

    connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSlot);
    //connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pImageProcessing,&ImageProcessing::pictureStreamSlot);
    connect(pGetimagesInterface,&GetImagesInterface::messageSignal,this,&MainWidget::message);
    //connect(pGetimagesInterface,&GetImagesInterface::camerStateSingal,pImageProcessing, &ImageProcessing::camerIDstatesSlot);

    connect(pImageProcessing,&ImageProcessing::initCamerSignal,pGetimagesInterface,&GetImagesInterface::initCamerSlot);
    connect(pImageProcessing,&ImageProcessing::putCommandSignal,pGetimagesInterface,&GetImagesInterface::putCommandSlot);

    /*  线程运行    */
    QThread* pThread=new QThread(this);
    pGetimagesInterface->moveToThread(pThread);
    pImageProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::serialportPlugin(InfraredlogicInterface *pInfraredlogicInterface, int num)
{
    DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[num]);

    LogicalProcessing* pLogicalProcessing=new LogicalProcessing (nullptr);
    LogicalProcessingMap.insert(num,pLogicalProcessing);

    connect(this,&MainWidget::exitWhileSignal,pInfraredlogicInterface,&InfraredlogicInterface::exitWhileSlot,Qt::BlockingQueuedConnection);

    //connect(pInfraredlogicInterface,&InfraredlogicInterface::logicStatusSignal,pLogicalProcessing,&LogicalProcessing::logicStatusSlot);
    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicStatusSignal,pDataWidget,&DataWidget::logicStatusSlot);
    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicPutImageSignal,pLogicalProcessing,&LogicalProcessing::logicPutImageSlot);
    //connect(pInfraredlogicInterface,&InfraredlogicInterface::logicPutImageSignal,pDataWidget,&DataWidget::logicPutImageSlot);
    connect(pInfraredlogicInterface,&InfraredlogicInterface::messageSignal,this,&MainWidget::message);

    connect(pLogicalProcessing,&LogicalProcessing::startSlaveSignal,pInfraredlogicInterface,&InfraredlogicInterface::startSlaveSlot);
    connect(pLogicalProcessing,&LogicalProcessing::setAlarmModeSignal,pInfraredlogicInterface,&InfraredlogicInterface::setAlarmModeSlot);
    connect(pLogicalProcessing,&LogicalProcessing::exitWhileSignal,pInfraredlogicInterface,&InfraredlogicInterface::exitWhileSlot);

    /*  线程运行    */
    QThread* pThread=new QThread(this);
    pInfraredlogicInterface->moveToThread(pThread);
    pLogicalProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::bindCamerObjects()
{
    /* 获取通道编号 */
    for(int channel:DataWidgetMap.keys()){
        if(LogicalProcessing* pLogicalProcessing=static_cast<LogicalProcessing*>(LogicalProcessingMap[channel])){
            /*  绑定相机组 */
            pLogicalProcessing->setCamerMultiMap(channelCamerMultiMap.values(channel));
            if(DataWidget* pDataWidget=static_cast<DataWidget*>(DataWidgetMap[channel])){
                /* 抓拍图片流链接到数据界面 */
                connect(pLogicalProcessing,&LogicalProcessing::pictureStreamSignal,pDataWidget,&DataWidget::pictureStreamSlot);
            }
        }
    }
}

void MainWidget::setStatusBar()
{
    statusBar=new QStatusBar(this);
    pStatusBarLabel=new QLabel(this);

    statusBar->setStyleSheet("background-color:rgb(39,39,40);color:red");
    this->ui->gridLayout_2->addWidget(statusBar);
}

void MainWidget::initSysInfo()
{
    pGetSysInfo=new GetSysInfo ();
    connect(this,&MainWidget::exitWhileSignal,pGetSysInfo,&GetSysInfo::exitWhileSlot);
    connect(pGetSysInfo,&GetSysInfo::statusMsgSignal,this,&MainWidget::statusMsgSlot);
    pGetSysInfo->start();/* 启动线程 */
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
         if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(value)){
             tmp->setVisible(false);
         }
         if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(value)){
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

void MainWidget::statusMsgSlot(const QString &msg)
{
    pStatusBarLabel->setText(msg);
    statusBar->addPermanentWidget(pStatusBarLabel );
}

void MainWidget::on_Navigation_itemActivated(QTreeWidgetItem *item)
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
        if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(value)){
            tmp->move(168,80);
            tmp->setVisible(true);
        }
        if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(value)){
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
        if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(pWidget)){
            tmp->resize( size->size().width()-168,size->size().height()-105);
        }
        if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(pWidget)){
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

void MainWidget::message(const QString &msg)
{
    this->statusBar->showMessage(msg.toLocal8Bit(),10000);
}


