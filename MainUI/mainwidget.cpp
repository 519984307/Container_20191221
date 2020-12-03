#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    initalizeMenubar();
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
    for(auto obj:RecognizerProcessingMap.values()){
        delete obj;
    }
    for(auto obj:ResultsAnalysisProcessingMap.values()){
        delete obj;
    }
    for(auto obj:SocketServiceProcessingMap.values()){
        delete obj;
    }
    for(auto obj:underlyingGetimagesProcessingMap.values()){
        delete  obj;
    }
    for(auto obj:UploadDataProcessingMap.values()){
        delete  obj;
    }
    for(auto obj:ElectronicLicensePlateProcessingMap.values()){
        delete  obj;
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
    RecognizerProcessingMap.clear();
    ResultsAnalysisProcessingMap.clear();
    SocketServiceProcessingMap.clear();
    UploadDataProcessingMap.clear();
    ElectronicLicensePlateProcessingMap.clear();

//    delete pDataBaseWidget;
//    delete pSystemSettingWidget;
//    delete pStatusBarLabel;
//    delete pStatusBarLabelPermanet;
//    delete pStatusBar;

    delete ui;
}

void MainWidget::initalizeMenubar()
{
    ui->Navigation->setHidden(true);/* 不显示导航栏 */
    pMenBar=new QMenuBar (this);

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style=file.readAll();

    setStyleSheet(style);

    pMenBar->setGeometry(0,80,this->width(),30);
    ui->gridLayout_3->addWidget(pMenBar);
}

void MainWidget::loadingParameters()
{
    int var=1;
    for (int channel = 1; channel <= channelCounnt; ++channel) {
        /* 相机参数初始化 */
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){

            if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[channel])){
                /*****************************
                * @brief:设置通道号,车牌使用
                ******************************/
                pDataWidget->setDataWidgetPar(pChannelSettingWidget->Channel_number);
            }

            QStringList FrontCamer=pChannelSettingWidget->FrontCamer.trimmed().split(";");
            QStringList AfterCamer=pChannelSettingWidget->AfterCamer.trimmed().split(";");
            QStringList LeftCamer=pChannelSettingWidget->LeftCamer.trimmed().split(";");
            QStringList RgihtCamer=pChannelSettingWidget->RgihtCamer.trimmed().split(";");

            int num=1;
            for (;var <=channel*4 ; ++var) {
                /*****************************
                * @brief:底层链接相机
                ******************************/
//                if(UnderlyingGetimagesProcessing* pImageProcessing=qobject_cast<UnderlyingGetimagesProcessing*>(underlyingGetimagesProcessingMap[var])){
//                    emit pImageProcessing->InitializationSignal();/* 初始化链接相机 */
//                    if(FrontCamer.count()>=3&&num==1){
//                        emit pImageProcessing->initCamerSignal(FrontCamer[0],23001,FrontCamer[1],FrontCamer[2],"Front");
//                    }
//                    else if(AfterCamer.count()>=3&&num==2){
//                        emit pImageProcessing->initCamerSignal(AfterCamer[0],23001,AfterCamer[1],AfterCamer[2],"After");
//                    }
//                    else if(LeftCamer.count()>=3&&num==3){
//                        emit pImageProcessing->initCamerSignal(LeftCamer[0],23001,LeftCamer[1],LeftCamer[2],"Left");
//                    }
//                    else if(RgihtCamer.count()>=3&&num==4){
//                        emit pImageProcessing->initCamerSignal(RgihtCamer[0],23001,RgihtCamer[1],RgihtCamer[2],"Right");
//                    }


                /*****************************
                * @brief:SDK链接相机
                ******************************/
                if(ImageProcessing* pImageProcessing=qobject_cast<ImageProcessing*>(ImageProcessingMap[var])){
                    /*emit pImageProcessing->InitializationSignal();*//* 初始化相机动态库,异步会导致动态库初始化没完成. */
                    if(FrontCamer.count()>=3&&num==1){
                        emit pImageProcessing->initCamerSignal(FrontCamer[0],8000,FrontCamer[1],FrontCamer[2],"Front");
                    }
                    else if(AfterCamer.count()>=3&&num==2){
                        emit pImageProcessing->initCamerSignal(AfterCamer[0],8000,AfterCamer[1],AfterCamer[2],"After");
                    }
                    else if(LeftCamer.count()>=3&&num==3){
                        emit pImageProcessing->initCamerSignal(LeftCamer[0],8000,LeftCamer[1],LeftCamer[2],"Left");
                    }
                    else if(RgihtCamer.count()>=3&&num==4){
                        emit pImageProcessing->initCamerSignal(RgihtCamer[0],8000,RgihtCamer[1],RgihtCamer[2],"Right");
                    }
                }
                ++num;
            }
            /* 车牌相机初始化 */
            if(ElectronicLicensePlateProcessing *pElectronicLicensePlateProcessing=qobject_cast<ElectronicLicensePlateProcessing*>(ElectronicLicensePlateProcessingMap[channel])){
                if(!pChannelSettingWidget->PlateCamer.isEmpty()){/* if WTY port 8080 else if HCNET port 8000 */
                    if(ChannelSettingWidget *pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){
                        pElectronicLicensePlateProcessing->initCameraSignal(pChannelSettingWidget->LocalAddr,pChannelSettingWidget->PlateCamer,8000,pSystemSettingWidget->pSettingValues->ImgPathOne,pSystemSettingWidget->pSettingValues->ImageFormatOne,pChannelSettingWidget->Channel_number);
                    }
                    //多通道
                    //pElectronicLicensePlateProcessing->initCameraSignal("192.168.1.100",pChannelSettingWidget->PlateCamer,8080,pSystemSettingWidget->pSettingValues->ImgPathOne,pSystemSettingWidget->pSettingValues->ImageFormatOne,channel);
                }
            }
        }

        /* 红外参数初始化 */
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){
            QString com1=QString("\\\\.\\COM%1").arg(pChannelSettingWidget->SerialPortOne);
            QString com2=QString("\\\\.\\COM%1").arg(pChannelSettingWidget->SerialPortTow);
            if(InfraredProcessing* pInfraredProcessing=qobject_cast<InfraredProcessing*>(InfraredProcessingMap[channel])){
                /* 设置红外模式 */
                emit pInfraredProcessing->setAlarmModeSignal(pChannelSettingWidget->infraredStatus);
                /* 启动串口 */
                emit pInfraredProcessing->startSlaveSignal(com1,com2);

                /*  绑定相机组抓到逻辑处理 */
                if(ChannelSettingWidget *pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[channel])){
                    pInfraredProcessing->setCamerMultiMap(channelCamerMultiMap.values(channel),pChannelSettingWidget->Channel_number);/* 单通道 */
                }
                //pInfraredProcessing->setCamerMultiMap(channelCamerMultiMap.values(channel),channel);/* 多通道 */
            }
        }

        if(pSystemSettingWidget!=nullptr){
            /* 识别器设置 */
            if(ResultsAnalysisProcessing*  pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[channel])){
                /* 设置校验结果  */
                emit pResultsAnalysisProcessing->setCheckTheResultsSignal(pSystemSettingWidget->pSettingValues->CheckResult);
                /* 是否发送中间结果 */
                emit pResultsAnalysisProcessing->sendMidResultSignal(pSystemSettingWidget->pSettingValues->Resultting);
            }
        }

        if(UploadDataProcessing* pUploadDataProcessing=qobject_cast<UploadDataProcessing*>(UploadDataProcessingMap[channel])){
            /* 上传数据(FTP设置参数) */
            pUploadDataProcessing->InitializationParameterSignal("test","cheng870888","./img/","192.168.0.125");
        }
    }

    if(pSystemSettingWidget!=nullptr){
        /* 服务设置 */
        switch (pSystemSettingWidget->pSettingValues->Service_Type) {
        case 0:/* 单例模式 */
            if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[1])){
                QStringList addr=pSystemSettingWidget->pSettingValues->SingletonAddress.split(":");
                if(addr.count()==2){
                    pSocketServerProcessing->InitializationParameterSignal(addr[0],addr[1].toUShort(),pSystemSettingWidget->pSettingValues->Service_Type,pSystemSettingWidget->pSettingValues->ServiceModel);
                    /* 心跳包状态 */
                    pSocketServerProcessing->sendHeartPacketSignal(pSystemSettingWidget->pSettingValues->Heartbeat);
                }
            }
            break;
        case 1:/* 多例模式 */
            QStringList addrList=pSystemSettingWidget->pSettingValues->ManyCasesAddress.split(",");
            for (int var = 0; var < addrList.count(); ++var) {
                QStringList addr=addrList[var].split(":");
                if((var+1)>channelCounnt){
                    break;
                }
                if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[var+1])){/* 通道号以1开始 */
                    if(addr.count()==2){
                        pSocketServerProcessing->InitializationParameterSignal(addr[0],addr[1].toUShort(),pSystemSettingWidget->pSettingValues->Service_Type,pSystemSettingWidget->pSettingValues->ServiceModel);
                        /* 心跳包状态 */
                        pSocketServerProcessing->sendHeartPacketSignal(pSystemSettingWidget->pSettingValues->Heartbeat);
                    }
                }
            }
            break;
        }       
    }

    foreach (auto action, QActionMap.keys()) {/* 绑定菜单按钮事件 */
        connect(action,SIGNAL(triggered()),this,SLOT(avtionMapTiggered()));
    }
    if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap.value(1)) ){
        QActionMap.key(pDataWidget)->triggered(); /* 显示地一个页面 */
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

    pEncryptionProcessing=nullptr;/* 初始化加密处理类 */
    pServiceWidget=nullptr;
    pLogWidget=nullptr;
    pDataBaseWidget=nullptr;
}

void MainWidget::InitializeDataWindow()
{
    QMenu* pMenuData=new QMenu (tr("&Channel To View"),this);
    pMenBar->addMenu(pMenuData);

    for(int i=1;i<=channelCounnt;i++){
        DataWidget* dataWidow=new DataWidget(this);
        QAction* pAction=new QAction(tr("%1 # Channel").arg(i),this);

        QActionMap.insert(pAction,dataWidow);
        DataWidgetMap.insert(i,dataWidow);

        pMenuData->addAction(pAction);
    }

//    QTreeWidgetItemIterator it(ui->Navigation);
//    while(*it){
//        if((*it)->text(0)==tr("Data")){
//            /*  获取数据根   */
//            for(int i=1;i<=channelCounnt;i++){
//                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
//                /*  添加子项    */
//                (*it)->addChild(childImte);

//                DataWidget* data=new DataWidget(this);
//                DataWidgetMap.insert(i,data);
//                ItemWidgetMap.insert(childImte,data);

//                if(i==1){
//                    /*  显示第一个窗口 */
//                    on_Navigation_itemActivated(childImte);
//                }
//            }
//        }
//        ++it;
//    }
}

void MainWidget::InitializeCamerWindow()
{
    QMenu* pMenuCamera=new QMenu (tr("&Camera Test"),this);
    pMenBar->addMenu(pMenuCamera);

    int j=1;
    for(int i=1;i<=channelCounnt;i++){
        QMenu* pMenu_=new QMenu (tr("%1 # Channel").arg(i),this);
        pMenuCamera->addMenu(pMenu_);
        CameraMenuMap.insert(i,pMenu_);

        for(auto name:CamerNameList){
            PictureWidget *picutreWindow= new PictureWidget (this);

            /* 通道对应的几个相机 */
            channelCamerMultiMap.insert(i,picutreWindow);

            if(name!="Plate"){
                PictureWidgetMap.insert(j,picutreWindow);
                j++;
            }
            QAction* pAction=new QAction(name,this);
            QActionMap.insert(pAction,picutreWindow);
            pMenu_->addAction(pAction);
        }
    }

//    QTreeWidgetItemIterator it(ui->Navigation);
//    while(*it){
//        if((*it)->text(0)==tr("Camera")){
//            /*  获取相机根   */
//            int j=1;
//            for(int i=1;i<=channelCounnt;i++){
//                auto childImte=new QTreeWidgetItem ((*it),QStringList(tr("%1 # Channel").arg(i)));
//                /*  添加子项    */
//                (*it)->addChild(childImte);
//                for(auto name:CamerNameList){
//                    auto sunItem=new QTreeWidgetItem (childImte,QStringList(name));
//                    childImte->addChild(sunItem);
//                    PictureWidget *picutre= new PictureWidget (this);
//                    /* 通道对应的几个相机 */
//                    channelCamerMultiMap.insert(i,picutre);

//                    /*  过滤车牌界面,车牌暂时不用海康SDK  */
//                    if(name!="Plate"){
//                        PictureWidgetMap.insert(j,picutre);
//                        j++;
//                    }
//                    ItemWidgetMap.insert(sunItem,picutre);
//                }
//            }
//        }
//        ++it;
//    }
}

void MainWidget::InitializeOtherWindow()
{
    /* service */
    pServiceWidget=new ServiceWidget (this);
    QAction* pActionService=new QAction (tr("&Service Status"),this);
    QActionMap.insert(pActionService,pServiceWidget);
    pMenBar->addAction(pActionService);

    /* database */
//    QMenu* pMenuDataBase=new QMenu (tr("Da&tabase"),this);
//    pMenBar->addMenu(pMenuDataBase);

    pDataBaseWidget=new DataBaseWidget (this);
    QAction* pActionHistory=new QAction(tr("Da&tabase"),this);
    QActionMap.insert(pActionHistory,pDataBaseWidget);
    //pMenuDataBase->addAction(pActionHistory);
    pMenBar->addAction(pActionHistory);

    /* Setting */
    QMenu* pMenuSetting=new QMenu (tr("&Parameter Setting"),this);
    pMenBar->addMenu(pMenuSetting);

    QAction* pActionSystem=new QAction(tr("System Settings"),this);
    QActionMap.insert(pActionSystem,pSystemSettingWidget);
    pMenuSetting->addAction(pActionSystem);

    for(int i=1;i<=channelCounnt;i++){
        ChannelSettingWidget* pChannelSettingWidget=new ChannelSettingWidget (i,this);/* 构造参数通道编号 */
        ChannelSettingWidgetMap.insert(i,pChannelSettingWidget);

        QAction* pAction=new QAction(tr("%1 # Channel Settings").arg(i),this);
        QActionMap.insert(pAction,pChannelSettingWidget);
        pMenuSetting->addAction(pAction);
    }

    /* Log */
    pLogWidget=new LogWidget (this);
    QAction* pActionLog=new QAction (tr("Log"),this);
    QActionMap.insert(pActionLog,pLogWidget);
    pMenBar->addAction(pActionLog);

    /* Help */
//    QAction* pActionHelp=new QAction(tr("Help"),this);
//    pMenBar->addAction(pActionHelp);

//    QTreeWidgetItemIterator it(ui->Navigation);
//    while(*it){
//        if((*it)->text(0)==tr("Setting")){
//            /*  获取设置根   */
//            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("System")));
//            (*it)->addChild(childImte);

//           // ItemWidgetMap.insert(childImte,new SystemSettingWidget(this) );
//            ItemWidgetMap.insert(childImte,pSystemSettingWidget);
//            for(int i=1;i<=channelCounnt;i++){
//                auto sunItem=new QTreeWidgetItem (childImte,QStringList(tr("%1 # Channel").arg(i)));
//                /*  添加子项    */
//                (*it)->addChild(sunItem);
//                ChannelSettingWidget* pChannelSettingWidget=new ChannelSettingWidget (i,this);/* 构造参数通道编号 */
//                ChannelSettingWidgetMap.insert(i,pChannelSettingWidget);
//                ItemWidgetMap.insert(sunItem,pChannelSettingWidget);
//            }
//        }
//        if((*it)->text(0)==tr("Service")){
//            /*  获取服务根   */
//            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("Log")));
//            (*it)->addChild(childImte);
//            pServiceWidget=new ServiceWidget (this);
//            ItemWidgetMap.insert(childImte,pServiceWidget);
//        }
//        if((*it)->text(0)==tr("Database")){
//            /*  获取数据库根  */
//            auto childImte=new QTreeWidgetItem((*it),QStringList(tr("History")));
//            (*it)->addChild(childImte);
//            pDataBaseWidget=new DataBaseWidget (this);
//            ItemWidgetMap.insert(childImte,pDataBaseWidget);
//        }
//        ++it;
//    }
}

void MainWidget::InitializeChannelSet()
{
    /* 设置通道别名 */
    for (int i=1;i<=channelCounnt;i++) {
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
            if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[i])){
                if(!pChannelSettingWidget->Alias.isEmpty()){
                    QActionMap.key(pDataWidget)->setText(pChannelSettingWidget->Alias);
                }
            }

            if(!pChannelSettingWidget->Alias.isEmpty()){
                CameraMenuMap.value(i)->setTitle(pChannelSettingWidget->Alias);
            }

            if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
                if(!pChannelSettingWidget->Alias.isEmpty()){
                    QActionMap.key(pChannelSettingWidget)->setText(pChannelSettingWidget->Alias);
                }
            }
        }
    }

//    /* 设置通道别名 */
//    QTreeWidgetItemIterator it(ui->Navigation);
//    while(*it){
//        if((*it)->text(0)==tr("Data") && (*it)->childCount()==channelCounnt){
//            for (int i=1;i<=channelCounnt;i++) {
//                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
//                    if(!pChannelSettingWidget->Alias.isEmpty()){
//                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);
//                    }
//                }
//            }
//        }
//        if((*it)->text(0)==tr("Camera") && (*it)->childCount()==channelCounnt){
//            for (int i=1;i<=channelCounnt;i++) {
//                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
//                    if(!pChannelSettingWidget->Alias.isEmpty()){
//                        (*it)->child(i-1)->setText(0,pChannelSettingWidget->Alias);
//                    }
//                }
//            }
//        }
//        if((*it)->text(0)==tr("System") && (*it)->childCount()==channelCounnt){
//            for (int i=1;i<=channelCounnt;i++) {
//                if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[i])){
//                    if(!pChannelSettingWidget->Alias.isEmpty()){
//                        (*it)->child(i-1) ->setText(0,pChannelSettingWidget->Alias);
//                    }
//                }
//            }
//        }
//        ++it;
//    }
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
            qDebug()<<fileName;
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
            }else if (MiddlewareInterface* pMiddlewareInterface=qobject_cast<MiddlewareInterface*>(plugin)) {
                delete pMiddlewareInterface;
                pMiddlewareInterface=nullptr;
                num=1;
            }
            else if(ICaptureUnderlying* pICaptureUnderlying=qobject_cast<ICaptureUnderlying*>(plugin)) {
                delete  pICaptureUnderlying;
                pICaptureUnderlying=nullptr;
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
            else if (ToUploadDataInterface* pToUploadDataInterface=qobject_cast<ToUploadDataInterface*>(plugin)) {
                delete  pToUploadDataInterface;
                pToUploadDataInterface=nullptr;
                num=channelCounnt;
            }
            else if (LicensePlateInterface* pLicensePlateInterface=qobject_cast<LicensePlateInterface*>(plugin)) {
                delete pLicensePlateInterface;
                pLicensePlateInterface=nullptr;
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
            else if (EncryptionInterface* pEncryptionInterface=qobject_cast<EncryptionInterface*>(plugin)) {
                delete pEncryptionInterface;
                pEncryptionInterface=nullptr;
                num=1;
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
            else if (MiddlewareInterface* pMiddlewareInterface=qobject_cast<MiddlewareInterface*>(plugin)) {
                middlewareHCNETPlugin(pMiddlewareInterface,num--);
            }
            else if (ICaptureUnderlying* pICaptureUnderlying=qobject_cast<ICaptureUnderlying*>(plugin)) {
                //captureUnderlyingPlugin(pICaptureUnderlying,num--);
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
            else if (EncryptionInterface* pEncryptionInterface=qobject_cast<EncryptionInterface*>(plugin)) {
                encryptionInterPlugin(pEncryptionInterface);
            }
            else if (ToUploadDataInterface* pToUploadDataInterface=qobject_cast<ToUploadDataInterface*>(plugin)) {
                uploadDataPlugin(pToUploadDataInterface,num--);
            }
            else if (LicensePlateInterface* pLicensePlateInterface=qobject_cast<LicensePlateInterface*>(plugin)) {
                ElectronicLicensePlatePlugin(pLicensePlateInterface,num--);
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
    GetImageInterfaceMap.insert(num,pGetimagesInterface);

    ImageProcessing* pImageProcessing=new ImageProcessing (this);
    ImageProcessingMap.insert(num,pImageProcessing);

    /* 初始化动态库 */
/*    connect(pImageProcessing,&ImageProcessing::InitializationSignal,pGetimagesInterface,&GetImagesInterface::InitializationSlot);*/
    /* 初始化相机 */
    connect(pImageProcessing,&ImageProcessing::initCamerSignal,pGetimagesInterface,&GetImagesInterface::initCamerSlot);
    /* 日志信息 */
    connect(pGetimagesInterface,&GetImagesInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 释放动态库资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pGetimagesInterface,&GetImagesInterface::releaseResourcesSlot);//,Qt::BlockingQueuedConnection);

    if(PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(PictureWidgetMap[num])){
        /* 抓取图片 */
        connect(pPictureWidget,&PictureWidget::putCommandSignal,pGetimagesInterface,&GetImagesInterface::putCommandSlot);
        /* 调整窗口 */
        connect(pPictureWidget,&PictureWidget::resizeEventSignal,pGetimagesInterface,&GetImagesInterface::resizeEventSlot);
        /* 播放视频流 */
        connect(pPictureWidget, &PictureWidget::playStreamSignal,pGetimagesInterface,&GetImagesInterface::playStreamSlot);
        /* 接收图片流 */
        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSlot);
        /* 相机状态(信号与信号绑定) */
        connect(pGetimagesInterface,&GetImagesInterface::camerStateSingal,pPictureWidget, &PictureWidget::camerIDstatesSignal);
        /* 转发图片流信号,分流到数据界面(信号与信号绑定) */
        connect(pGetimagesInterface,&GetImagesInterface::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSignal);
    }

//    /* 线程运行 */
//    QThread* pThread=new QThread(this);
//    pGetimagesInterface->moveToThread(pThread);
//    pImageProcessing->moveToThread(pThread);
//    ThreadList.append(pThread);
//    pThread->start();
}

void MainWidget::captureUnderlyingPlugin(ICaptureUnderlying *pUnderlyingCapture, int num)
{
    UnderlyingGetimagesProcessing* pUnderlyingGetimagesProcessing=new UnderlyingGetimagesProcessing(nullptr);
    underlyingGetimagesProcessingMap.insert(num,pUnderlyingGetimagesProcessing);

    /* 初始化动态库 */
    connect(pUnderlyingGetimagesProcessing,&UnderlyingGetimagesProcessing::InitializationSignal,pUnderlyingCapture,&ICaptureUnderlying::InitializationSlot);
    /* 初始化相机 */
    connect(pUnderlyingGetimagesProcessing,&UnderlyingGetimagesProcessing::initCamerSignal,pUnderlyingCapture,&ICaptureUnderlying::initCamerSlot);
    /* 日志信息 */
    connect(pUnderlyingCapture,&ICaptureUnderlying::messageSignal,this,&MainWidget::messageSlot);
    /* 释放动态库资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pUnderlyingCapture,&ICaptureUnderlying::releaseResourcesSlot,Qt::BlockingQueuedConnection);

    if(PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(PictureWidgetMap[num])){
        /* 抓取图片 */
        connect(pPictureWidget,&PictureWidget::putCommandSignal,pUnderlyingCapture,&ICaptureUnderlying::putCommandSlot);
        /* 接收图片流 */
        connect(pUnderlyingCapture,&ICaptureUnderlying::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSlot);
        /* 相机状态(信号与信号绑定) */
        connect(pUnderlyingCapture,&ICaptureUnderlying::camerStateSingal,pPictureWidget, &PictureWidget::camerIDstatesSignal);
        /* 转发图片流信号,分流到数据界面(信号与信号绑定) */
        connect(pUnderlyingCapture,&ICaptureUnderlying::pictureStreamSignal,pPictureWidget,&PictureWidget::pictureStreamSignal);
    }

    /* 线程运行 */
    QThread* pThread=new QThread(this);
    pUnderlyingCapture->moveToThread(pThread);
    pUnderlyingGetimagesProcessing->moveToThread(pThread);
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
    /* 日志信息 */
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
    RecognizerProcessingMap.insert(num,pRecognizerProcessing);

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
    //pRecognizerProcessing->setChannelSlot(num);/* 多通道 */
    if(ChannelSettingWidget *pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[num])){
        pRecognizerProcessing->setChannelSlot(pChannelSettingWidget->Channel_number);/* 单通道 */
    }

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
    /* 发送识别结果 */
    connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::sendResultSignal,pResultsAnalysisProcessing,&ResultsAnalysisProcessing::sendResultSignal);
    /* 发送中间结果接 */
    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::sendMidResultSignal,pResultsAnalysisInterface,&ResultsAnalysisInterface::sendMidResultSlot);
    if(pServiceWidget!=nullptr){
            /* 绑定识别结果到服务窗口 */
         connect(pResultsAnalysisInterface,&ResultsAnalysisInterface::resultsAnalysisStateSignal,pServiceWidget,&ServiceWidget::resultsAnalysisStateSlot);
    }

    /* 设置通道号 */
    //pResultsAnalysisProcessing->setChannelSignal(num);/* 多通道版本 */
    if(ChannelSettingWidget *pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(ChannelSettingWidgetMap[num])){
        pResultsAnalysisProcessing->setChannelSignal(pChannelSettingWidget->Channel_number);/* 单通道版本 */
    }

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
    /* 绑定SOCKET数量到服务界面 */
    connect(pSocketServerInterface,&SocketServerInterface::socketConnectCountSignal,pSocketServerProcessing,&SocketServerProcessing::socketConnectCountSignal);
    /* 日志信息 */
    connect(pSocketServerInterface,&SocketServerInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 释放资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pSocketServerInterface,&SocketServerInterface::releaseResourcesSlot);
    /* 发送识别结果 */
    connect(pSocketServerProcessing,&SocketServerProcessing::sendResultSignal,pSocketServerInterface,&SocketServerInterface::sendResultSignal);
    /* 心跳包状态 */
    connect(pSocketServerProcessing,&SocketServerProcessing::sendHeartPacketSignal,pSocketServerInterface,&SocketServerInterface::sendHeartPacketSignal);

    QThread* pThread=new QThread(this);
    pSocketServerProcessing->moveToThread(pThread);
    pSocketServerInterface->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::encryptionInterPlugin(EncryptionInterface *pEncryptionInterface)
{
    pEncryptionProcessing=new EncryptionProcessing (this) ;

    /* 日志信息 */
    connect(pEncryptionInterface,&EncryptionInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 释放资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pEncryptionInterface,&EncryptionInterface::releaseResourcesSlot);
    /* 获取加密状态 */
    connect(pEncryptionInterface,&EncryptionInterface::GetTheEncryptedStateSignal,pEncryptionProcessing,&EncryptionProcessing::GetTheEncryptedStateSignal);
    /* 获取加密信息 */
    connect(pEncryptionInterface,&EncryptionInterface::GetEncryptedInformationSignal,pEncryptionProcessing,&EncryptionProcessing::GetEncryptedInformationSignal);
}

void MainWidget::uploadDataPlugin(ToUploadDataInterface *pToUploadDataInterface,int num)
{
    /* 异步 */
    UploadDataProcessing* pUploadDataProcessing=new UploadDataProcessing (this) ;
    UploadDataProcessingMap.insert(num,pUploadDataProcessing);

    /* 初始化参数 */
    connect(pUploadDataProcessing,&UploadDataProcessing::InitializationParameterSignal,pToUploadDataInterface,&ToUploadDataInterface::InitializationParameterSlot);
    /* 上传数据 */
    connect(pUploadDataProcessing,&UploadDataProcessing::uploadDataSignal,pToUploadDataInterface,&ToUploadDataInterface::uploadDataSlot);
    connect(pToUploadDataInterface,&ToUploadDataInterface::messageSignal,this,&MainWidget::messageSlot);

//    QThread* pThread=new QThread(this);
//    pUploadDataProcessing->moveToThread(pThread);
//    pToUploadDataInterface->moveToThread(pThread);
//    ThreadList.append(pThread);
    //    pThread->start();
}

void MainWidget::ElectronicLicensePlatePlugin(LicensePlateInterface *pLicensePlateInterface, int num)
{
    /*****************************
    * @brief:供海康车牌使用
    ******************************/
    LicenseInterfaceMap.insert(num,pLicensePlateInterface);

    ElectronicLicensePlateProcessing* pElectronicLicensePlateProcessing=new ElectronicLicensePlateProcessing (nullptr);
    ElectronicLicensePlateProcessingMap.insert(num,pElectronicLicensePlateProcessing);

    if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[num])){
        /* 初始化相机 */
        connect(pElectronicLicensePlateProcessing,&ElectronicLicensePlateProcessing::initCameraSignal,pLicensePlateInterface,&LicensePlateInterface::initCameraSlot);
        /* 模拟抓拍 */
        connect(pDataWidget,&DataWidget::simulationCaptureSignal,pLicensePlateInterface,&LicensePlateInterface::simulationCaptureSlot);
        /* 识别结果 */
        connect(pLicensePlateInterface,&LicensePlateInterface::resultsTheLicensePlateSignal,pDataWidget,&DataWidget::resultsTheLicensePlateSlot);
        /* 图片流 */
        connect(pLicensePlateInterface,&LicensePlateInterface::imageFlowSignal,pDataWidget,&DataWidget::imageFlowSlot);
        /* 打开关闭车牌视频 */
        connect(pDataWidget,&DataWidget::openTheVideoSignal,pLicensePlateInterface,&LicensePlateInterface::openTheVideoSlot);
        /* 视频流 */
        connect(pLicensePlateInterface,&LicensePlateInterface::theVideoStreamSignal,pDataWidget,&DataWidget::theVideoStreamSlot);
        /* 相机状态 */
        connect(pLicensePlateInterface,&LicensePlateInterface::equipmentStateSignal,pDataWidget,&DataWidget::equipmentStateSlot);
    }
    /* 日志信息 */
    connect(pLicensePlateInterface,&LicensePlateInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 释放资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pLicensePlateInterface,&LicensePlateInterface::releaseResourcesSlot);

    QThread* pThread=new QThread(this);
    pElectronicLicensePlateProcessing->moveToThread(pThread);
    pLicensePlateInterface->moveToThread(pThread);
    ThreadList.append(pThread);
    pThread->start();
}

void MainWidget::middlewareHCNETPlugin(MiddlewareInterface *pMiddlewareInterface, int num)
{
    MiddlewareHCNETProcessingMap.insert(num,pMiddlewareInterface);

    /* 日志信息 */
    connect(pMiddlewareInterface,&MiddlewareInterface::messageSignal,this,&MainWidget::messageSlot);
    /* 释放资源 */
    connect(this,&MainWidget::releaseResourcesSignal,pMiddlewareInterface,&MiddlewareInterface::releaseResourcesSlot);

    QThread* pThread=new QThread(this);
    pMiddlewareInterface->moveToThread(pThread);
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

                if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[key])){
                    /*****************************
                    * @brief:车牌数据写入数据库
                    ******************************/
                    connect(pDataWidget,&DataWidget::insertDataBaseSignal,pDataBaseProcessing,&DataBaseProcessing::insertDataBaseSignal);
                    /*****************************
                    * @brief:车牌数据更新数据库
                    ******************************/
                    connect(pDataWidget,&DataWidget::updateDataBaseSignal,pDataBaseProcessing,&DataBaseProcessing::updateDataBaseSignal);
                }

                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 保存数据(信号与信号绑定) */
                    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::updateDataBaseSignal,pDataBaseProcessing,&DataBaseProcessing::updateDataBaseSignal);
                }
            }
            if(pServiceWidget!=nullptr){
                /* 开始抓拍写入服务界面 */
                connect(pInfraredProcessing,&InfraredProcessing::rInfraredLogicStarttateSignal,pServiceWidget,&ServiceWidget::resultsAnalysisStateSlot);
            }
            if(RecognizerProcessing* pRecognizerProcessing=qobject_cast<RecognizerProcessing*>(RecognizerProcessingMap[key])){
                /* 逻辑抓拍完成 */
                connect(pInfraredProcessing,&InfraredProcessing::infraredCompleteSignal,pRecognizerProcessing,&RecognizerProcessing::infraredCompleteSlot);
                /* 逻辑抓拍开始 */
                connect(pInfraredProcessing,&InfraredProcessing::InfraredLogicStartSignal,pRecognizerProcessing,&RecognizerProcessing::InfraredLogicStartSlot);
                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 分析识别结果(信号与信号绑定) */
                    connect(pRecognizerProcessing,&RecognizerProcessing::resultsOfAnalysisSignal,pResultsAnalysisProcessing,&ResultsAnalysisProcessing::resultsOfAnalysisSignal);
                }
                /* 判断加密状态 */
                if(pEncryptionProcessing!=nullptr){
                    connect(pEncryptionProcessing,&EncryptionProcessing::GetTheEncryptedStateSignal,pRecognizerProcessing,&RecognizerProcessing::GetTheEncryptedStateSlot);
                }

                if(UploadDataProcessing* pUploadDataProcessing=qobject_cast<UploadDataProcessing*>(UploadDataProcessingMap[key])){
                    /* 上传图片(FTP信号与信号) */
                    connect(pRecognizerProcessing,&RecognizerProcessing::uploadDataSignal,pUploadDataProcessing,&UploadDataProcessing::uploadDataSignal);
                }
            }

            if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[key])){
                if(ResultsAnalysisProcessing* pResultsAnalysisProcessing=qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                    /* 识别结果到数据界面 */
                    connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::containerSignal,pDataWidget,&DataWidget::containerSlot);
                }
                for(auto obj:channelCamerMultiMap.values(key)){
                    if(PictureWidget* pPictureWidget=qobject_cast<PictureWidget*>(obj)){
                        /* 绑定(前后左右)相机抓拍图片流,到数据界面(显示图片) */
                        connect(pPictureWidget,&PictureWidget::pictureStreamSignal,pDataWidget,&DataWidget::pictureStreamSlot);
                        /* 绑定(前后左右)相机状态,到数据界面(状态显示) */
                        connect(pPictureWidget,&PictureWidget::camerIDstatesSignal,pDataWidget,&DataWidget::camerIDstatesSlot);

                        if(RecognizerProcessing* pRecognizerProcessing=qobject_cast<RecognizerProcessing*>(RecognizerProcessingMap[key])){
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
    /*****************************
    * @brief:海康相机中间件，处理程序(一个DLL注册所有相机),改动注意！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    ******************************/
    if(MiddlewareInterface* pMiddlewareInterface=qobject_cast<MiddlewareInterface*>(MiddlewareHCNETProcessingMap.value(1))){
        foreach (auto obj, GetImageInterfaceMap.values()) {
            if(GetImagesInterface* pGetImagesInterface=qobject_cast<GetImagesInterface*>(obj)){
                connect(pGetImagesInterface,&GetImagesInterface::signal_initCamera,pMiddlewareInterface,&MiddlewareInterface::initCameraSlot);
                connect(pGetImagesInterface,&GetImagesInterface::signal_openTheVideo,pMiddlewareInterface,&MiddlewareInterface::openTheVideoSlot);
                connect(pGetImagesInterface,&GetImagesInterface::signal_simulationCapture,pMiddlewareInterface,&MiddlewareInterface::simulationCaptureSlot);
                connect(pGetImagesInterface,&GetImagesInterface::signal_liftingElectronicRailing,pMiddlewareInterface,&MiddlewareInterface::liftingElectronicRailingSlot);
                connect(pGetImagesInterface,&GetImagesInterface::signal_transparentTransmission485,pMiddlewareInterface,&MiddlewareInterface::transparentTransmission485Slot);

                //connect(pMiddlewareInterface,&MiddlewareInterface::signal_message,pGetImagesInterface,&GetImagesInterface::initCameraSlot);
                connect(pMiddlewareInterface,&MiddlewareInterface::signal_pictureStream,pGetImagesInterface,&GetImagesInterface::slot_pictureStream);
                connect(pMiddlewareInterface,&MiddlewareInterface::signal_setCameraID,pGetImagesInterface,&GetImagesInterface::slot_setCameraID);
                connect(pMiddlewareInterface,&MiddlewareInterface::equipmentStateSignal,pGetImagesInterface,&GetImagesInterface::slot_equipmentState);
                connect(pMiddlewareInterface,&MiddlewareInterface::resultsTheLicensePlateSignal,pGetImagesInterface,&GetImagesInterface::slot_resultsTheLicensePlate);
            }
        }
        /*****************************
        * @brief:海康车牌
        ******************************/
        if(LicensePlateInterface* pLicensePlateInterface=qobject_cast<LicensePlateInterface*>(LicenseInterfaceMap[1])){
            connect(pLicensePlateInterface,&LicensePlateInterface::signal_initCamera,pMiddlewareInterface,&MiddlewareInterface::initCameraSlot);
            connect(pLicensePlateInterface,&LicensePlateInterface::signal_openTheVideo,pMiddlewareInterface,&MiddlewareInterface::openTheVideoSlot);
            connect(pLicensePlateInterface,&LicensePlateInterface::signal_simulationCapture,pMiddlewareInterface,&MiddlewareInterface::simulationCaptureSlot);
            connect(pLicensePlateInterface,&LicensePlateInterface::signal_liftingElectronicRailing,pMiddlewareInterface,&MiddlewareInterface::liftingElectronicRailingSlot);
            connect(pLicensePlateInterface,&LicensePlateInterface::signal_transparentTransmission485,pMiddlewareInterface,&MiddlewareInterface::transparentTransmission485Slot);

            //connect(pMiddlewareInterface,&MiddlewareInterface::signal_message,pGetImagesInterface,&GetImagesInterface::initCameraSlot);
            connect(pMiddlewareInterface,&MiddlewareInterface::signal_pictureStream,pLicensePlateInterface,&LicensePlateInterface::slot_pictureStream);
            connect(pMiddlewareInterface,&MiddlewareInterface::signal_setCameraID,pLicensePlateInterface,&LicensePlateInterface::slot_setCameraID);
            connect(pMiddlewareInterface,&MiddlewareInterface::equipmentStateSignal,pLicensePlateInterface,&LicensePlateInterface::slot_equipmentState);
            connect(pMiddlewareInterface,&MiddlewareInterface::resultsTheLicensePlateSignal,pLicensePlateInterface,&LicensePlateInterface::slot_resultsTheLicensePlate);
        }
    }


    foreach (auto obj, ChannelSettingWidgetMap.values()) {
        if(ChannelSettingWidget* pChannelSettingWidget=qobject_cast<ChannelSettingWidget*>(obj)){
            /* 绑定通道设定日志 */
            connect(pChannelSettingWidget,&ChannelSettingWidget::messageSignal,this,&MainWidget::messageSlot);
        }
    }
    if(pServiceWidget!=nullptr){/* 暂时处理单模 */
        switch (pSystemSettingWidget->pSettingValues->Service_Type) {
        case 0:/* 单例模式 */
            if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[1])){
                /* 客户端数量到是服务界面 */
                connect(pSocketServerProcessing,&SocketServerProcessing::socketConnectCountSignal,pServiceWidget,&ServiceWidget::socketConnectCountSlot);
                foreach (auto key, ResultsAnalysisProcessingMap.keys()) {
                    if(ResultsAnalysisProcessing* pResultsAnalysisProcessing =qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                        /* 发送识别结果到socket */
                        connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::sendResultSignal,pSocketServerProcessing,&SocketServerProcessing::sendResultSignal);

                        if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[key])){
                            /* 发送车牌结果到socket */
                            connect(pDataWidget,&DataWidget::sendResultSignal,pSocketServerProcessing,&SocketServerProcessing::sendResultSignal);
                        }
                    }
                }                     
            }
            break;
        case 1:/* 多例模式 */
            foreach (auto key, SocketServiceProcessingMap.keys()) {
                if(SocketServerProcessing* pSocketServerProcessing=qobject_cast<SocketServerProcessing*>(SocketServiceProcessingMap[key])){
                    /* 客户端数量到是服务界面 */
                    connect(pSocketServerProcessing,&SocketServerProcessing::socketConnectCountSignal,pServiceWidget,&ServiceWidget::socketConnectCountSlot);
                    if(ResultsAnalysisProcessing* pResultsAnalysisProcessing =qobject_cast<ResultsAnalysisProcessing*>(ResultsAnalysisProcessingMap[key])){
                        /* 发送识别结果到socket */
                        connect(pResultsAnalysisProcessing,&ResultsAnalysisProcessing::sendResultSignal,pSocketServerProcessing,&SocketServerProcessing::sendResultSignal);

                        if(DataWidget* pDataWidget=qobject_cast<DataWidget*>(DataWidgetMap[key])){
                            /* 发送车牌结果到socket */
                            connect(pDataWidget,&DataWidget::sendResultSignal,pSocketServerProcessing,&SocketServerProcessing::sendResultSignal);
                        }
                    }
                }
            }
            break;
        }
    }

    /* 绑定日志信息到日志窗口 */
    if(pLogWidget!=nullptr){
         connect(this,&MainWidget::messageSignal,pLogWidget,&LogWidget::messageSlot);
    }
}

void MainWidget::hideWindows()
{
    //for(auto key:ItemWidgetMap.keys()){
    for(auto value:QActionMap.values()){
        //auto value=ItemWidgetMap[key];
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
         if(LogWidget* tmp=qobject_cast<LogWidget*>(value)){
             tmp->setVisible(false);
         }
    }
}

void MainWidget::on_Navigation_itemActivated(QTreeWidgetItem *item)
{
//    if(ItemWidgetMap.find(item)==ItemWidgetMap.end()){
//        return;
//    }

//    hideWindows();

//    auto value=ItemWidgetMap[item];
//    if(value){
//        if(DataWidget* tmp=qobject_cast<DataWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//        if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//        if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(value)){
//            //tmp->move(168,80);
//            tmp->move(0,110);
//            tmp->setVisible(true);
//        }
//    }
}

void MainWidget::avtionMapTiggered()
{
    QAction* pAction=qobject_cast<QAction*> (sender());
    if(QActionMap.find(pAction)==QActionMap.end()){
        return;
    }

    hideWindows();

    auto value=QActionMap[pAction];
    int channel=-1;
    QString text="";

    if(value){
        if(DataWidget* tmp=qobject_cast<DataWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            channel=DataWidgetMap.key(tmp);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            channel=PictureWidgetMap.key(tmp);
            int ret=channel/4;
            int mod=channel%4;
            if(mod==0){
                mod+=4;
            }
            else {
                ret+=1;
            }
            text=tr("Preview %1 channel %2 Camera").arg(ret).arg(mod);
        }
        if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            channel=ChannelSettingWidgetMap.key(tmp);
            text=tr("Preview %1 channel Setting Page").arg(channel);
        }
        if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            text=tr("Preview System Settings Page");
        }
        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            text=tr("Preview Service Page");
        }
        if(LogWidget* tmp=qobject_cast<LogWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            text=tr("Preview Log Page");
        }
        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(value)){
            //tmp->move(168,80);
            tmp->move(0,112);
            tmp->setVisible(true);
            tmp->resize(tmp->size()+QSize(1,1));
            tmp->resize(tmp->size()-QSize(1,1));
            text=tr("Preview Database Page");
        }
        if(pStatusBarLabelPermanet==nullptr){
            return;
        }
        if(text!=""){
            pStatusBarLabelPermanet->setText(text);
        }
        else {
            pStatusBarLabelPermanet->setText(tr("Preview %1 channel").arg(channel));
        }
    }
}

void MainWidget::resizeEvent(QResizeEvent *size)
{
    for(auto pWidget:QActionMap.values()){
        if(DataWidget* tmp=qobject_cast<DataWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(PictureWidget* tmp=qobject_cast<PictureWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(ChannelSettingWidget* tmp=qobject_cast<ChannelSettingWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(SystemSettingWidget* tmp=qobject_cast<SystemSettingWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(ServiceWidget* tmp=qobject_cast<ServiceWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(DataBaseWidget* tmp=qobject_cast<DataBaseWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
        }
        if(LogWidget* tmp=qobject_cast<LogWidget*>(pWidget)){
            //tmp->resize( size->size().width()-168,size->size().height()-105);
            tmp->resize( size->size().width(),size->size().height()-135);
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
    emit messageSignal(type,msg);/* 日志窗口显示日志 */

    if(pSystemSettingWidget->pSettingValues->DebugLog){
        QFile file(QDir::toNativeSeparators(tr("%1/%2_debug_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd"))));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            return;
        }
        QTextStream stream(&file);
        stream<<QString("[%1]%2%3%4").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(type).arg(msg).arg(QDir::toNativeSeparators("\n"));
        file.close();
    }
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
    if(pSystemSettingWidget->pSettingValues->DebugLog && pSystemSettingWidget->pSettingValues->SaveLog){
        QFile file(QDir::toNativeSeparators(tr("%1/%2_%3_Capture_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd")).arg(channel)));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            return;
        }
        QTextStream stream(&file);
        stream<<tr("[%1]%2%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg).arg(QDir::toNativeSeparators("\n"));
        file.close();
    }
}

void MainWidget::resultsAnalysisStateSlot(const int &channel, const QString &msg)
{
    if(pSystemSettingWidget->pSettingValues->InfoLog && pSystemSettingWidget->pSettingValues->SaveLog){
        QFile file(QDir::toNativeSeparators(tr("%1/%2_%3_Container_log.txt").arg(logPath).arg(QDateTime::currentDateTime().toString("yyyyMMdd")).arg(channel)));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            return;
        }
        QTextStream stream(&file);
        stream<<tr("[%1]%2%3").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")).arg(msg).arg(QDir::toNativeSeparators("\n"));
        file.close();
    }
}
