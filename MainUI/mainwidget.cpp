#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    setStatusBar();

    InitializeSystemSet();
    InitializeDataWindow();
    InitializeCamerWindow();
    InitializeOtherWindow();
    InitializeChannelSet();

    loadPlugins();
    publicConnect();
    loadingParameters();
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    emit releaseResourcesSignal();
    emit exitWhileSignal(true);

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
    for(auto obj:InfraredProcessingMap.values()){
        delete obj;
    }
    for(auto obj:DataBaseProcessingMap.values()){
        delete obj;
    }
    for(auto obj:PictureWidgetMap.values()){
        delete obj;
    }
    for(auto obj:DataWidgetMap.values()){
        delete obj;
    }
    for(auto obj:ChannelSettingWidgetMap.values()){
        delete obj;
    }
    for(auto obj:RecognizerProcessingMqp.values()){
        delete obj;
    }
    for(auto obj:ResultsAnalysisProcessingMap.values()){
        delete obj;
    }
    for(auto obj:SocketServiceProcessingMap.values()){
        delete obj;
    }
    foreach (auto obj, ThreadList) {
        delete obj;
    }

    ImageProcessingMap.clear();
    InfraredProcessingMap.clear();
    DataBaseProcessingMap.clear();
    ThreadList.clear();
    ItemWidgetMap.clear();
    DataWidgetMap.clear();
    PictureWidgetMap.clear();
    CamerNameList.clear();
    channelCamerMultiMap.clear();
    ChannelSettingWidgetMap.clear();
    RecognizerProcessingMqp.clear();
    ResultsAnalysisProcessingMap.clear();
    SocketServiceProcessingMap.clear();

    delete pDataBaseWidget;
    delete pSystemSettingWidget;
    delete pStatusBarLabel;
    delete pStatusBarLabelPermanet;
    delete pStatusBar;

    delete ui;
}

void MainWidget::loadingParameters()
{
    int var=1;

    for (int channel = 1; channel <= channelCounnt; ++channel) {

        /* 相机参数初始化 */
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){
            QStringList FrontCamer=pChannelSettingWidget->FrontCamer.split(";");
            QStringList AfterCamer=pChannelSettingWidget->AfterCamer.split(";");
            QStringList LeftCamer=pChannelSettingWidget->LeftCamer.split(";");
            QStringList RgihtCamer=pChannelSettingWidget->RgihtCamer.split(";");

            int num=1;
            for (;var <=channel*4 ; ++var) {
                if(ImageProcessing* pImageProcessing=qobject_cast<ImageProcessing*>(ImageProcessingMap[var])){
                    if(FrontCamer.count()==4&&num==1){
                        emit pImageProcessing->initCamerSignal(FrontCamer[0],FrontCamer[1].toInt(),FrontCamer[2],FrontCamer[3]);
                    }
                    if(AfterCamer.count()==4&&num==2){
                        emit pImageProcessing->initCamerSignal(AfterCamer[0],AfterCamer[1].toInt(),AfterCamer[2],AfterCamer[3]);
                    }
                    if(LeftCamer.count()==4&&num==3){
                        emit pImageProcessing->initCamerSignal(LeftCamer[0],LeftCamer[1].toInt(),LeftCamer[2],LeftCamer[3]);
                    }
                    if(RgihtCamer.count()==4&&num==4){
                        emit pImageProcessing->initCamerSignal(RgihtCamer[0],RgihtCamer[1].toInt(),RgihtCamer[2],RgihtCamer[3]);
                    }
                }
                ++num;
            }
        }

        /* 红外参数初始化 */
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){
            QString com1=QString("com%1").arg(pChannelSettingWidget->SerialPortOne);
            QString com2=QString("com%1").arg(pChannelSettingWidget->SerialPortTow);
            if(InfraredProcessing* pInfraredProcessing=qobject_cast<InfraredProcessing*>(InfraredProcessingMap[channel])){
                /* 设置红外模式 */
                emit pInfraredProcessing->setAlarmModeSignal(pChannelSettingWidget->infraredStatus);
                /* 启动串口 */
                emit pInfraredProcessing->startSlaveSignal(com1,com2);
                /*  绑定相机组抓到逻辑处理 */
                pInfraredProcessing->setCamerMultiMap(channelCamerMultiMap.values(channel),channel);
            }
        }

        if(pSystemSettingWidget!=nullptr){
            /* 识别器设置 */
            if(ResultsAnalysisProcessing*  pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[channel])){
                /* 设置校验结果  */
                emit pResultsAnalysisProcessing->setCheckTheResultsSignal(pSystemSettingWidget->pSettingValues->CheckResult);
            }
        }
    } 

    if(pSystemSettingWidget!=nullptr){
        /* 服务设置 */
        switch (pSystemSettingWidget->pSettingValues->Service_Type) {
        case 0:/* 单例模式 */
            if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[1])){
                QStringList addr=pSystemSettingWidget->pSettingValues->SingletonAddress.split(":");
                if(addr.count()==2){
                    pSocketServerProcessing->InitializationParameterSignal(addr[0],addr[1].toUShort(),pSystemSettingWidget->pSettingValues->ServiceModel);
                }
            }
            break;
        case 1:/* 多例模式 */
            QStringList addrList=pSystemSettingWidget->pSettingValues->ManyCasesAddress.split(",");
            for (int var = 0; var < addrList.count(); ++var) {
                QStringList addr=addrList[var].split(":");
                if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[var])){
                    if(addr.count()==2){
                        pSocketServerProcessing->InitializationParameterSignal(addr[0],addr[1].toUShort(),pSystemSettingWidget->pSettingValues->ServiceModel);
                    }
                }
            }
            break;
        }
    }
}

void MainWidget::InitializeSystemSet()
{
    /* 创建日志文件夹 */
    QDir mkPath(QCoreApplication::applicationDirPath());
    mkPath.mkdir("Log");
    mkPath.cd("Log");
    logPath=mkPath.path();

    qRegisterMetaType<QMap<QString,QString>>("QMap<QString,QString>");

    pSystemSettingWidget=new SystemSettingWidget (this);
    connect(pSystemSettingWidget,&SystemSettingWidget::messageSignal,this,&MainWidget::messageSlot);

    channelCounnt=pSystemSettingWidget->pSettingValues->ChannelNumber;
    CamerNameList<<tr("Front")<<tr("After")<<tr("Left")<<tr("Right");
    //CamerNameList<<"Front"<<"After"<<"Left"<<"Right"<<"Plate";
}

void MainWidget::InitializeDataWindow()
{
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){
        if((*it)->text(0)==tr("Data")){
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
        if((*it)->text(0)==tr("Camera")){
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
                        PictureWidgetMap.insert(j,picutre);
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
        if((*it)->text(0)==tr("Setting")){
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
        if((*it)->text(0)==tr("Service")){
            /*  获取服务根   */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Log")));
            (*it)->addChild(childImte);
            pServiceWidget=new ServiceWidget (this);
            ItemWidgetMap.insert(childImte,pServiceWidget);
        }
        if((*it)->text(0)==tr("Database")){
            /*  获取数据库根  */
            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("History")));
            (*it)->addChild(childImte);
            pDataBaseWidget=new DataBaseWidget (this);
            ItemWidgetMap.insert(childImte,pDataBaseWidget);
        }
        ++it;
    }
}

void MainWidget::InitializeChannelSet()
{
    /* 设置通道别名 */
    QTreeWidgetItemIterator it(ui->Navigation);
    while(*it){
        if((*it)->text(0)==tr("Data") && (*it)->childCount()==channelCounnt){
            for (int i=1;i<=channelCounnt;i++) {
                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                    if(!pChannelSettingWidget->Alias.isEmpty()){
                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);
                    }
                }
            }
        }
        if((*it)->text(0)==tr("Camera") && (*it)->childCount()==channelCounnt){
            for (int i=1;i<=channelCounnt;i++) {
                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                    if(!pChannelSettingWidget->Alias.isEmpty()){
                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);
                    }
                }
            }
        }
        if((*it)->text(0)==tr("System") && (*it)->childCount()==channelCounnt){
            for (int i=1;i<=channelCounnt;i++) {
                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                    if(!pChannelSettingWidget->Alias.isEmpty()){
                        (*it)->child(i-1) ->setText(0,pChannelSettingWidget->Alias);
                    }
                }
            }
        }
        ++it;
    }
}

void MainWidget::loadPlugins()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());

    /*  创建插件目录  */
    const QString pluginPath="Plugins";
    pluginsDir.mkdir(pluginPath);
    pluginsDir.cd(pluginPath);

    const QString path=pluginsDir.path();
    for(const QString &fileName :pluginsDir.entryList(QDir::Files)){
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
                for(QFileInfo file :pluginsDir.entryInfoList()){
                    if(file.isFile()){
                        file.dir().remove(file.fileName());
                    }
                }
            }

            int num=0;/* 通道数量 */

            if(GetImagesInterface* pGetimagesInterface=qobject_cast<GetImagesInterface*>(plugin)){
                delete pGetimagesInterface;
                pGetimagesInterface=nullptr;
                num=channelCounnt*4;
            }
            else if(InfraredlogicInterface* pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)){
                delete pInfraredlogicInterface;
                pInfraredlogicInterface=nullptr;
                num=channelCounnt;
            }
            else if(DataBaseInsertInterface* pDataBaseInsertInterface=qobject_cast<DataBaseInsertInterface*>(plugin)){
                delete pDataBaseInsertInterface;
                pDataBaseInsertInterface=nullptr;
                num=channelCounnt;
            }
            else if (DataBaseReadInterface* pDataBaseReadInterface=qobject_cast<DataBaseReadInterface*>(plugin)) {
                delete pDataBaseReadInterface;
                pDataBaseReadInterface=nullptr;
                num=1;
            }
            else if (RecognizerInterface* pRecognizerInterface=qobject_cast<RecognizerInterface*>(plugin)){
                delete pRecognizerInterface;
                pRecognizerInterface=nullptr;
                num=channelCounnt;
            }
            else if (ResultsAnalysisInterface* pResultsAnalysisInterface=qobject_cast<ResultsAnalysisInterface*>(plugin)) {
                delete pResultsAnalysisInterface;
                pResultsAnalysisInterface=nullptr;
                num=channelCounnt;
            }
            else if(SocketServerInterface* pSocketServerInterface=qobject_cast<SocketServerInterface*>(plugin)) {
                delete  pSocketServerInterface;
                pSocketServerInterface=nullptr;
                if(pSystemSettingWidget!=nullptr){
                    switch (pSystemSettingWidget->pSettingValues->Service_Type) {
                    case 0:/* 单例模式 */
                        num=1;
                        break;
                    case 1:/* 多例模式 */
                        num=channelCounnt;
                        break;
                    }
                }
            }
            else {
                delete  plugin;/* 暂不处理其他插件 */
            }

            /*  复制新插件   */
            for(int i=1;i<=num;i++){
                  QFile::copy(QDir::toNativeSeparators(tr("%1/%2").arg(path).arg(fileName)),QDir::toNativeSeparators(tr("%1/%2_%3").arg(pluginsDir.absolutePath()).arg(i).arg(fileName)));
            }

            if(num!=0){/* 加载插件 */
                processingPlugins(pluginsDir,num);
            }

            /*  返回上层目录  */
            pluginsDir.cdUp();
        }
    }
}

void MainWidget::processingPlugins(QDir path, int num)
{
    /* 加载插件 */
    const QStringList entryList=path.entryList(QDir::Files);
    for(const QString &fileName :entryList){

        QPluginLoader  pluginLoader(path.absoluteFilePath(fileName));
        QObject* plugin = pluginLoader.instance();

        if(plugin){
            if(GetImagesInterface* pGetimagesInterface=qobject_cast<GetImagesInterface*>(plugin)){
                getImagePlugin(pGetimagesInterface,num--);
            }
            else if(InfraredlogicInterface* pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)){
                infraredLogicPlugin(pInfraredlogicInterface,num--);
            }
            else if(DataBaseInsertInterface* pDataBaseInsertInterface=qobject_cast<DataBaseInsertInterface*>(plugin)){
                dataBaseInsertPlugin(pDataBaseInsertInterface,num--);
            }
            else if (DataBaseReadInterface* pDataBaseReadInterface=qobject_cast<DataBaseReadInterface*>(plugin)) {
                dataBaseReadPlugin(pDataBaseReadInterface);
            }
            else if (RecognizerInterface* pRecognizerInterface=qobject_cast<RecognizerInterface*>(plugin)) {
                recognizerPlugin(pRecognizerInterface,num--);
            }
            else if (ResultsAnalysisInterface* pRecognizerInterface=qobject_cast<ResultsAnalysisInterface*>(plugin)) {
                resultsAnalysisPlugin(pRecognizerInterface,num--);
            }
            else if (SocketServerInterface* pSocketServerInterface=qobject_cast<SocketServerInterface*>(plugin)) {
                socketServerPlugin(pSocketServerInterface,num--);
            }
            else {
                delete plugin;
            }
        }
        else {
            delete  plugin;
        }
    }
}

void MainWidget::getImagePlugin(GetImagesInterface *pGetimagesInterface, int num)
{
    ImageProcessing* pImageProcessing=new ImageProcessing (nullptr);
    ImageProcessingMap.insert(num,pImageProcessing);

    if(PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(PictureWidgetMap[num])){
        /* 日志信息 */
        connect(pGetimagesInterface,&GetImagesInterface::messageSignal,this,&MainWidget::messageSlot);
        /* 释放动态库资源 */
        connect(this,&MainWidget::releaseResourcesSignal,pGetimagesInterface,&GetImagesInterface::releaseResourcesSlot,Qt::BlockingQueuedConnection);
        /* 抓取图片 */
        connect(pPictureWidget,&PictureWidget::putCommandSignal,pGetimagesInterface,&GetImagesInterface::putCommandSlot);
        /* 调整窗口 */
        connect(pPictureWidget,&PictureWidget::resizeEventSignal,pGetimagesInterface,&GetImagesInterface::resizeEventSlot);
        /* 播放视频流 */
        connect(pPictureWidget, &PictureWidget::playStreamSignal,pGetimagesInterface,&GetImagesInterface::playStreamSlot);
        /* 接收图片流 */
        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSlot);
        /* 初始化相机 */
        connect(pImageProcessing,&ImageProcessing::initCamerSignal,pGetimagesInterface,&GetImagesInterface::initCamerSlot);
        /* 相机状态 */
        connect(pGetimagesInterface,&GetImagesInterface::camerStateSingal,pImageProcessing, &ImageProcessing::camerIDstatesSlot);
        /* 转发图片流信号,分流到数据界面(信号与信号绑定) */
        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSignal);
    }

    /* 线程运行 */
    QThread* pThread=new QThread(this);
    pGetimagesInterface->moveToThread(pThread);
    pImageProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::infraredLogicPlugin(InfraredlogicInterface *pInfraredlogicInterface, int num)
{
    InfraredProcessing* pInfraredProcessing=new InfraredProcessing (nullptr);
    InfraredProcessingMap.insert(num,pInfraredProcessing);

    if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[num])){
        /* 清除界面图片 */
        connect(pInfraredProcessing,&InfraredProcessing::clearnPictureSignal,pDataWidget,&DataWidget::pictureStreamSlot);
        /* 红外状态到界面 */
        connect(pInfraredlogicInterface,&InfraredlogicInterface::logicStatusSignal,pDataWidget,&DataWidget::logicStatusSlot);
        /* 模拟抓拍流程 */
        connect(pDataWidget,&DataWidget::simulateTriggerSignal,pInfraredlogicInterface,&InfraredlogicInterface::simulateTriggerSlot);
    }

    /* 红外状态到日志 */
    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicStatusSignal,pInfraredProcessing,&InfraredProcessing::logicStatusSlot);
    /* 开始逻辑检测 */
    connect(pInfraredProcessing,&InfraredProcessing::startSlaveSignal,pInfraredlogicInterface,&InfraredlogicInterface::startSlaveSlot);
    /* 设置红外模式 */
    connect(pInfraredProcessing,&InfraredProcessing::setAlarmModeSignal,pInfraredlogicInterface,&InfraredlogicInterface::setAlarmModeSlot);
    /* 退出逻辑检测循环 */
    connect(this,&MainWidget::exitWhileSignal,pInfraredlogicInterface,&InfraredlogicInterface::exitWhileSlot,Qt::BlockingQueuedConnection);
    /* 日志i信息 */
    connect(pInfraredlogicInterface,&InfraredlogicInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 逻辑抓取图片 */
    connect(pInfraredlogicInterface,&InfraredlogicInterface::logicPutImageSignal,pInfraredProcessing,&InfraredProcessing::logicPutImageSlot);
    /* 抓拍状态写入日志 */
    connect(pInfraredProcessing,&InfraredProcessing::putCommantStateSignal,this,&MainWidget::putCommantStateSlot);

    /*  线程运行    */
    QThread* pThread=new QThread(this);
    pInfraredlogicInterface->moveToThread(pThread);
    pInfraredProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::dataBaseInsertPlugin(DataBaseInsertInterface* pDataBaseInsertInterface, int num)
{       
    DataBaseProcessing* pDataBaseProcessing=new DataBaseProcessing (nullptr);
    DataBaseProcessingMap.insert(num,pDataBaseProcessing);

    /* 日志信息 */
    connect(pDataBaseInsertInterface,&DataBaseInsertInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 初始化数据库 */
    connect(pDataBaseProcessing,&DataBaseProcessing::initDataBaseSignal,pDataBaseInsertInterface,&DataBaseInsertInterface::initDataBaseSlot);
    /* 插入数据库 */
    connect(pDataBaseProcessing,&DataBaseProcessing::insertDataBaseSignal,pDataBaseInsertInterface,&DataBaseInsertInterface::insertDataBaseSlot);
    /* 更新数据库 */
    connect(pDataBaseProcessing,&DataBaseProcessing::updateDataBaseSignal,pDataBaseInsertInterface,&DataBaseInsertInterface::updateDataBaseSlot);

    /* 初始化数据库(插入数据库插件) */
    emit pDataBaseProcessing->initDataBaseSignal(QString::number(num),"admin","Zby123456","localhost");

    /* 移动到线程运行 */
    QThread* pThread=new QThread(this);
    pDataBaseInsertInterface->moveToThread(pThread);
    pDataBaseProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::dataBaseReadPlugin(DataBaseReadInterface* pDataBaseReadInterface)
{
    DataBaseProcessing* pDataBaseProcessing=new DataBaseProcessing (nullptr);
    DataBaseProcessingMap.insert(channelCounnt+1,pDataBaseProcessing);/* 单独一条一个线程 */

    if(pDataBaseWidget!=nullptr){
        /* 日志信息 */
        connect(pDataBaseReadInterface,&DataBaseReadInterface::messageSignal,this,&MainWidget::messageSlot);
        /* 初始化数据库 */
        connect(pDataBaseProcessing,&DataBaseProcessing::initDataBaseSignal,pDataBaseReadInterface,&DataBaseReadInterface::initDataBaseSlot);
        /* 查询数据 */
        connect(pDataBaseProcessing,&DataBaseProcessing::setDataBaseFilterSignal,pDataBaseReadInterface,&DataBaseReadInterface::setDataBaseFilterSlot);
        /* 返回数据模型到数据库界面 */
        connect(pDataBaseReadInterface,&DataBaseReadInterface::returnModelSingal,pDataBaseWidget,&DataBaseWidget::returnModelSlot);
        /* 查询数据绑定到数据库处理逻辑(信号与信号绑定) */
        connect(pDataBaseWidget,&DataBaseWidget::setDataBaseFilterSignal,pDataBaseProcessing,&DataBaseProcessing::setDataBaseFilterSignal);
        /* 统计数据到界面 */
        connect(pDataBaseReadInterface,&DataBaseReadInterface::statisticalDataSignal,pDataBaseWidget,&DataBaseWidget::statisticalDataSlot);
        /* 设置数据库图片查询路径 */
        connect(pDataBaseProcessing,&DataBaseProcessing::seFindtImgPathSlgnal,pDataBaseWidget,&DataBaseWidget::seFindtImgPathSlot);
    }

    /* 初始化数据库图片查询路径 */
    emit pDataBaseProcessing->seFindtImgPathSlgnal(pSystemSettingWidget->pSettingValues->ImgPathOne,pSystemSettingWidget->pSettingValues->ImageFormatOne);
    /* 初始化数据库(读取数据库插件) */
    emit pDataBaseProcessing->initDataBaseSignal("DataBaseRead","admin","Zby123456","localhost");

    /* 移动到线程运行 */
    QThread* pThread=new QThread(this);
    pDataBaseReadInterface->moveToThread(pThread);
    pDataBaseProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::recognizerPlugin(RecognizerInterface *pRecognizerInterface, int num)
{
    RecognizerProcessing* pRecognizerProcessing=new RecognizerProcessing (nullptr);
    RecognizerProcessingMqp.insert(num,pRecognizerProcessing);

    if(pSystemSettingWidget!=nullptr){
        /* 设置图片保存路径1 */
        connect(pSystemSettingWidget,&SystemSettingWidget::setSaveImgFormatOneSignal,pRecognizerProcessing,&RecognizerProcessing::setSaveImgFormatOneSlot);
        /* 设置图片保存路径2 */
        connect(pSystemSettingWidget,&SystemSettingWidget::setSaveImgFormatTowSignal,pRecognizerProcessing,&RecognizerProcessing::setSaveImgFormatTowSlot);
        /* 识别图片 */
        connect(pRecognizerProcessing,&RecognizerProcessing::identifyImagesSignal,pRecognizerInterface,&RecognizerInterface::identifyImagesSlot);
        if(pSystemSettingWidget->pSettingValues->SaveImageOne){
            /* 设置图片路径和保存协议1 */
            emit pSystemSettingWidget->setSaveImgFormatOneSignal(pSystemSettingWidget->pSettingValues->ImgPathOne,pSystemSettingWidget->pSettingValues->ImageFormatOne);
        }
        if(pSystemSettingWidget->pSettingValues->SaveImageTow){
            /* 设置图片路径和保存协议2 */
            emit pSystemSettingWidget->setSaveImgFormatTowSignal(pSystemSettingWidget->pSettingValues->ImgPathTow,pSystemSettingWidget->pSettingValues->ImageFormatTow);
        }
    }

    /* 识别结果 */
    connect(pRecognizerInterface,&RecognizerInterface::recognitionResultSignal,pRecognizerProcessing,&RecognizerProcessing::recognitionResultSlot);
    /* 日志信息 */
    connect(pRecognizerInterface,&RecognizerInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 抓拍状态写入日志 */
    connect(pRecognizerProcessing,&RecognizerProcessing::putCommantStateSignal,this,&MainWidget::putCommantStateSlot);

    /* 设置通道号 */
    pRecognizerProcessing->setChannelSlot(num);

    /* 移动到线程运行 */
    QThread* pThread=new QThread(this);
    pRecognizerInterface->moveToThread(pThread);
    pRecognizerProcessing->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::resultsAnalysisPlugin(ResultsAnalysisInterface *pResultsAnalysisInterface, int num)
{
    ResultsAnalysisProcessing*  pResultsAnalysisProcessing=new ResultsAnalysisProcessing (nullptr);
    ResultsAnalysisProcessingMap.insert(num,pResultsAnalysisProcessing);

    /* 保存数据(信号与信号绑定) */
    connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::updateDataBaseSignal,pResultsAnalysisProcessing,&ResultsAnalysisProcessing::updateDataBaseSignal);
    /* 识别结果(信号与信号绑定) */
    connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::containerSignal,pResultsAnalysisProcessing,&ResultsAnalysisProcessing::containerSignal);
    /* 分析识别结果 */
    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::resultsOfAnalysisSignal,pResultsAnalysisInterface,&ResultsAnalysisInterface::resultsOfAnalysisSlot);
    /* 日志信息 */
    connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 设置通道号 */
    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::setChannelSignal,pResultsAnalysisInterface,&ResultsAnalysisInterface::setChannelSlot);
    /* 识别结果写入日志 */
    connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::resultsAnalysisStateSignal,this,&MainWidget::resultsAnalysisStateSlot);
    /* 结果校验模式 */
    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::setCheckTheResultsSignal,pResultsAnalysisInterface,&ResultsAnalysisInterface::setCheckTheResultsSlot);

    /* 设置通道号 */
    pResultsAnalysisProcessing->setChannelSignal(num);

    /* 移动到线程运行 */
    QThread* pThread=new QThread(this);
    pResultsAnalysisProcessing->moveToThread(pThread);
    pResultsAnalysisInterface->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::socketServerPlugin(SocketServerInterface *pSocketServerInterface, int num)
{
    SocketServerProcessing* pSocketServerProcessing=new SocketServerProcessing (nullptr);
    SocketServiceProcessingMap.insert(num,pSocketServerProcessing);

    /* 初始化参数 */
    connect(pSocketServerProcessing,&SocketServerProcessing::InitializationParameterSignal,pSocketServerInterface,&SocketServerInterface::InitializationParameterSlot);
    /* 发送数据 */
    connect(pSocketServerProcessing,&SocketServerProcessing::socketSendDataSignal,pSocketServerInterface,&SocketServerInterface::socketSendDataSlot);
    /* 日志信息 */
    connect(pSocketServerInterface,&SocketServerInterface::messageSignal,this,&MainWidget::messageSlot);

    QThread* pThread=new QThread(this);
    pSocketServerProcessing->moveToThread(pThread);
    pSocketServerInterface->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::publicConnect()
{
    /* 一条通道4台相机的数据流,绑定到一个数据界面 */
    for (auto key:DataWidgetMap.keys()) {
        if(InfraredProcessing* pInfraredProcessing=qobject_cast<InfraredProcessing*>(InfraredProcessingMap[key])){
            if(DataBaseProcessing* pDataBaseProcessing=qobject_cast<DataBaseProcessing*>(DataBaseProcessingMap[key])){
                /* 过车抓拍数据写入数据库(插入数据库) */
                connect(pInfraredProcessing,&InfraredProcessing::insertDataBaseSignal,pDataBaseProcessing,&DataBaseProcessing::insertDataBaseSignal);
                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 保存数据(信号与信号绑定) */
                    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::updateDataBaseSignal,pDataBaseProcessing,&DataBaseProcessing::updateDataBaseSignal);
                }
            }
            if(RecognizerProcessing* pRecognizerProcessing=qobject_cast<RecognizerProcessing*>(RecognizerProcessingMqp[key])){
                /* 逻辑抓拍完成 */
                connect(pInfraredProcessing,&InfraredProcessing::infraredCompleteSignal,pRecognizerProcessing,&RecognizerProcessing::infraredCompleteSlot);
                /* 逻辑抓拍开始 */
                connect(pInfraredProcessing,&InfraredProcessing::InfraredLogicStartSignal,pRecognizerProcessing,&RecognizerProcessing::InfraredLogicStartSlot);
                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 分析识别结果(信号与信号绑定) */
                    connect(pRecognizerProcessing,&RecognizerProcessing::resultsOfAnalysisSignal,pResultsAnalysisProcessing,&ResultsAnalysisProcessing::resultsOfAnalysisSignal);
                }
            }
            if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[key])){
                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 识别结果 */
                    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::containerSignal,pDataWidget,&DataWidget::containerSlot);
                }
                for(auto obj:channelCamerMultiMap.values(key)){
                    if(PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(obj)){
                        /* 绑定(前后左右)相机抓拍图片流到数据界面(显示图片) */
                        connect(pPictureWidget,&PictureWidget::pictureStreamSignal,pDataWidget,&DataWidget::pictureStreamSlot);
                        if(RecognizerProcessing* pRecognizerProcessing=qobject_cast<RecognizerProcessing*>(RecognizerProcessingMqp[key])){
                            /* 相机图片流绑定到识别器处理流程(保存图片) */
                            connect(pPictureWidget,&PictureWidget::pictureStreamSignal,pRecognizerProcessing,&RecognizerProcessing::pictureStreamSlot);
                            /* 保存two图片地址 */
                            connect(pPictureWidget,&PictureWidget::pictureStreamSignal,pRecognizerProcessing,&RecognizerProcessing::saveImageTowSlot);
                        }
                    }
                }
            }
        }
    }
    foreach (auto obj, ChannelSettingWidgetMap.values()) {
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(obj)){
            /* 绑定通道设定日志 */
            connect(pChannelSettingWidget,&ChannelSettingWidget::messageSignal,this,&MainWidget::messageSlot);
        }
    }

    /* 绑定日志信息到服务窗口 */
    connect(this,&MainWidget::messageSignal,pServiceWidget,&ServiceWidget::messageSlot);
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

void MainWidget::setStatusBar()
{
    pStatusBar=new QStatusBar(this);    
    pStatusBarLabel=new QLabel (this);
    pStatusBarLabelPermanet=new QLabel (tr("Program in place").toLocal8Bit(),this);
    pStatusBarLabelPermanet->setStyleSheet("color: rgb(0, 85, 255);");
    pStatusBar->addWidget(pStatusBarLabel);
    pStatusBar->addPermanentWidget(pStatusBarLabelPermanet);
    pStatusBar->setStyleSheet("background-color:rgb(39,39,40);color: red;");

    this->ui->gridLayout_2->addWidget(pStatusBar);
}

void MainWidget::messageSlot(const QString &type, const QString &msg)
{
    emit messageSignal(type,msg);/* 服务窗口显示日志 */

    QFile file(QDir::toNativeSeparators(tr("%1/%2_debug_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd"))));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        return;
    }
    QTextStream stream(&file);
    stream<<tr("[%1]%2%3%4").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(type).arg(msg).arg(QDir::toNativeSeparators("\n"));
    file.close();
//    if(type.indexOf("INFO")){
//        pStatusBar->setStyleSheet("background-color:rgb(39,39,40);color: rgb(85, 255, 127);");
//    }
//    if(type.indexOf("ERROR")){
//        pStatusBar->setStyleSheet("background-color:rgb(39,39,40);color: red;");
//    }
   // this->pStatusBar->showMessage(msg.toLocal8Bit().data(),3000);
}

void MainWidget::putCommantStateSlot(const int& channel, const QString &msg)
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2_%3_Capture_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd")).arg(channel)));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        return;
    }
    QTextStream stream(&file);
    stream<<tr("[%1]%2%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg).arg(QDir::toNativeSeparators("\n"));
    file.close();
}

void MainWidget::resultsAnalysisStateSlot(const int &channel, const QString &msg)
{
    QFile file(QDir::toNativeSeparators(tr("%1/%2_%3_Container_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd")).arg(channel)));
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
        return;
    }
    QTextStream stream(&file);
    stream<<tr("[%1]%2%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg).arg(QDir::toNativeSeparators("\n"));
    file.close();
}
