#include "MainWidget.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : FramelessWidget(parent)
{
    setMinimumSize(610,610);

    init();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initSystemTray()
{
    m_SystemTray = new QSystemTrayIcon(this);
    m_TrayMenu = new TrayIconMenu(this);

    m_SystemTray->setContextMenu(m_TrayMenu);
    m_SystemTray->setToolTip("LinuxHex");
    m_SystemTray->setIcon(QIcon(":/Source/image/app.png"));

    m_SystemTray->show();
    connect(m_SystemTray ,&QSystemTrayIcon::activated, this, &MainWidget::TrayActivated);

    connect(m_TrayMenu->setAction,&QAction::triggered,this,&MainWidget::showOptionDialog);
    connect(m_TrayMenu->quitAction,&QAction::triggered,this,&MainWidget::close);
}

void MainWidget::initMenu()
{
    mainMenuBar = new QMenuBar(this);
    mainMenuBar->setFixedHeight(30);
    mainMenuBar->setStyleSheet("background:rgb(204, 204, 204);");

    fileMenu = new QMenu("文件(&F)",this);
    editMenu = new QMenu("编辑(&E)",this);
    watchMenu = new QMenu("查看(&W)",this);
    helpMenu = new QMenu("帮助(&H)",this);

    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveReadable);
    fileMenu->addAction(saveSelectionReadable);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(findAct);
    editMenu->addAction(findPreAct);
    editMenu->addAction(findNextAct);
    editMenu->addSeparator();
    editMenu->addAction(optionsAct);

    watchMenu->addAction(infoAct);
    watchMenu->addAction(dataAct);

    helpMenu->addAction(aboutAct);

    mainMenuBar->addMenu(fileMenu);
    mainMenuBar->addMenu(editMenu);
    mainMenuBar->addMenu(watchMenu);
    mainMenuBar->addMenu(helpMenu);

}

void MainWidget::initAction()
{
    openAct = new QAction(QIcon(":/Source/image/open.png"), "打开文件(&O)", this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct,&QAction::triggered,this,&MainWidget::openFile);

    saveAct = new QAction(QIcon(":/Source/image/save.png"), "保存(&S)", this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct,&QAction::triggered,this,&MainWidget::save);

    saveAsAct = new QAction("另存为(&A)", this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct,&QAction::triggered,this,&MainWidget::saveAs);

    saveReadable = new QAction("导出(&E)", this);
    connect(saveReadable,&QAction::triggered,this,&MainWidget::saveToReadableFile);

    exitAct = new QAction("退出(&Q)", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct,&QAction::triggered,this,&MainWidget::close);

    undoAct = new QAction(QIcon(":/Source/image/undo.png"), "&Undo", this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, [=]()
    {
        if(mainMiddleWidget->m_Tab->count() >= 1)
            reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->undo();
        else
            mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    });

    redoAct = new QAction(QIcon(":/Source/image/redo.png"), "&Redo", this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, [=]()
    {
        if(mainMiddleWidget->m_Tab->count() >= 1)
            reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->redo();
        else
            mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    });

    saveSelectionReadable = new QAction("导出选中部分", this);
    connect(saveSelectionReadable,&QAction::triggered,this,&MainWidget::saveSelectionToReadableFile);

    aboutAct = new QAction(QIcon(":/Source/image/app.png"),"关于(&P)", this);
    connect(aboutAct,&QAction::triggered,[=]()
    {
        QMessageBox::about(this, "关于 LinuxHex","遵循GPL协议的开源软件\n\n作者: Bottod");
    });

    findAct = new QAction(QIcon(":/Source/image/find.png"), "&查找/替换", this);
    findAct->setShortcuts(QKeySequence::Find);
    connect(findAct, &QAction::triggered, this, &MainWidget::showSearchDialog);

    findNextAct = new QAction("&向后查找", this);
    findNextAct->setShortcuts(QKeySequence::FindNext);
    connect(findNextAct, &QAction::triggered, this, &MainWidget::findNext);

    findPreAct = new QAction("&向前查找",this);
    findPreAct->setShortcuts(QKeySequence::FindPrevious);
    connect(findPreAct,&QAction::triggered,this,&MainWidget::findPre);

    optionsAct = new QAction("选项(&O)", this);
    connect(optionsAct,&QAction::triggered, this, &MainWidget::showOptionDialog);

    infoAct = new QAction("信息面板",this);
    infoAct->setCheckable(true);
    infoAct->setChecked(true);
    connect(infoAct,&QAction::triggered,this,[=]()
    {
        if(infoWidget->isVisible())
        {
            infoAct->setChecked(false);
            infoWidget->hide();
            if(!dataWidget->isVisible())
                leftFrame->hide();
        }
        else
        {
            infoAct->setChecked(true);
            infoWidget->show();
            leftFrame->show();
        }
    });

    dataAct = new QAction("数据注释器",this);
    dataAct->setCheckable(true);
    dataAct->setChecked(true);
    connect(dataAct,&QAction::triggered,[=]()
    {
        if(dataWidget->isVisible())
        {
            dataAct->setChecked(false);
            dataWidget->hide();
            if(!infoWidget->isVisible())
                leftFrame->hide();
        }
        else
        {
            dataAct->setChecked(true);
            dataWidget->show();
            leftFrame->show();
        }
    });
}

void MainWidget::initOtherWidget()
{
    optionDialog = new OptionDialog(this);
    connect(optionDialog, &OptionDialog::accepted, this, &MainWidget::optionAccept);

    searchDialog = new SearchDialog(this);

    mainTitleBar = new TitleBar(this);
    connect(mainTitleBar->minimumBtn,&QPushButton::clicked,this,&MainWidget::showMinimized);
    connect(mainTitleBar->maximumBtn,&QPushButton::clicked,[&]()
    {
        if(isMaximun)
        {
            isMaximun = false;
            mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum.png);} \
                                                    QPushButton:hover{border-image:url(:/Source/image/maximum_hover.png);}");
            mainTitleBar->maximumBtn->setToolTip("最大化");
            showNormal();
        }
        else
        {
            isMaximun = true;

            mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum_cancel.png);} \
                                                    QPushButton:hover{border-image:url(:/Source/image/maximum_cancel_hover.png);}");

            mainTitleBar->maximumBtn->setToolTip("向下还原");
            showMaximized();
        }
    });
    connect(mainTitleBar->closeBtn,&QPushButton::clicked,this,&MainWidget::close);
    connect(mainTitleBar->setBtn,&QPushButton::clicked,this,&MainWidget::showOptionDialog);

    leftFrame = new QFrame(this);
    leftFrame->setAutoFillBackground(true);
    leftFrame->setFixedWidth(200);
    infoWidget = new InfoFrame(this);
    connect(infoWidget->m_CloseBtn,&QPushButton::clicked,[=]()
    {
        infoWidget->hide();
        infoAct->setChecked(false);
        if(!dataWidget->isVisible())
        {
            leftFrame->hide();
        }
    });
    dataWidget = new DataFrame(this);
    connect(dataWidget->m_CloseBtn,&QPushButton::clicked,[=]()
    {
        dataWidget->hide();
        dataAct->setChecked(false);
        if(!infoWidget->isVisible())
        {
            leftFrame->hide();
        }
    });


    mainMiddleWidget = new MiddleWidget(this);
    connect(mainMiddleWidget->m_Tab,&QTabWidget::tabCloseRequested,this,&MainWidget::removeSubTab);
    connect(mainMiddleWidget->m_Tab,&QTabWidget::currentChanged,[=]()
    {
        searchDialog->setHexEdit(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget()));
        bool isSaved = !(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->isModified());
        int index = mainMiddleWidget->m_Tab->currentIndex();

        if(isSaved)
            mainTitleBar->setTitle(mainMiddleWidget->m_Tab->tabText(index) + " - LinuxHex");
        else
            mainTitleBar->setTitle("*" + mainMiddleWidget->m_Tab->tabText(index) + " - LinuxHex");

        mainStatusBar->setSize(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->getLastEventSize());
        mainStatusBar->setAddress(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->getPosCurrent());

        //different widget can have differnt write mode
        //this->setOverwriteMode(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->getOverWriteMode());

        //first open a file have tabtext but don't have tabtooltip;
        getFileInfo();

        QSettings settings;
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressArea(settings.value("AddressArea",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAsciiArea(settings.value("AsciiArea",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setHighlighting(settings.value("Highlighting",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setOverwriteMode(settings.value("OverwriteMode",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setReadOnly(settings.value("ReadOnly",false).toBool());

        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setHighlightingColor(settings.value("HighlightingColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressAreaColor(settings.value("AddressAreaColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setSelectionColor(settings.value("SelectionColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setFont(settings.value("WidgetFont",QFont("Monospace", 10)).value<QFont>());

        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressWidth(settings.value("AddressAreaWidth",4).toInt());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setBytesPerLine(settings.value("BytesPerLine",16).toInt());
    });

    mainStatusBar = new StatusBar(this);
    mainStatusBar->setAutoFillBackground(true);

}

void MainWidget::initLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(mainTitleBar);
    mainLayout->addWidget(mainMenuBar);

    QVBoxLayout *middleLeftLayout = new QVBoxLayout(leftFrame);
    middleLeftLayout->setSpacing(0);
    middleLeftLayout->setMargin(0);
    middleLeftLayout->addWidget(infoWidget);
    middleLeftLayout->addWidget(dataWidget);
    middleLeftLayout->addStretch();
    QHBoxLayout *middleLayout = new QHBoxLayout();
    middleLayout->setSpacing(0);
    middleLayout->setMargin(0);
    middleLayout->addWidget(leftFrame);
    middleLayout->addWidget(mainMiddleWidget);
    mainLayout->addLayout(middleLayout);

    mainLayout->addWidget(mainStatusBar);
    this->setLayout(mainLayout);
}

//init all
void MainWidget::init()
{
    //enable drag
    setAcceptDrops(true);

    initOtherWidget();

    initSystemTray();
    initAction();
    initMenu();

    initLayout();

    readSettings();
}

void MainWidget::TrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
        {
            showNormal();
            raise();
            activateWindow();
            break;
        }
        case QSystemTrayIcon::MiddleClick:
        {
            break;
        }
        case QSystemTrayIcon::DoubleClick:
        {
            break;
        }
        default:
            break;
    }
}

//protected
void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(QRect(0,0,mainTitleBar->width(),mainTitleBar->height()).contains(event->pos()) ||
       QRect(width()-20,height()-20,20,20).contains(event->pos()))
    {
        FramelessWidget::mousePressEvent(event);
    }
    return QWidget::mousePressEvent(event);
}
void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(QRect(0,0,mainTitleBar->width(),mainTitleBar->height()).contains(event->pos()))
    {
        if(isMaximun)
        {
            isMaximun = false;
            mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum.png);} \
                                                    QPushButton:hover{border-image:url(:/Source/image/maximum_hover.png);}");
            mainTitleBar->maximumBtn->setToolTip("最大化");
            showNormal();
        }
        else
        {
            isMaximun = true;
            mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum_cancel.png);} \
                                                    QPushButton:hover{border-image:url(:/Source/image/maximum_cancel_hover.png);}");
            mainTitleBar->maximumBtn->setToolTip("向下还原");
            showMaximized();
        }
    }
    return QWidget::mouseDoubleClickEvent(event);
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    if(quitTips)
    {
        QString messageTitle = "确认关闭";
        QString messageContent = "关闭所有文档并退出程序?";

        QMessageBox closMessage(QMessageBox::Question, messageTitle, messageContent);
        closMessage.addButton(QMessageBox::No);
        closMessage.setButtonText(QMessageBox::No, QString("退出(&Q)"));

        closMessage.addButton(QMessageBox::Cancel);
        closMessage.setButtonText(QMessageBox::Cancel, QString("取消(&C)"));

        closMessage.addButton(QMessageBox::Yes);
        closMessage.setButtonText(QMessageBox::Yes, QString("不再提醒(&O)"));

        int result = closMessage.exec();
        switch (result)
        {
            case (QMessageBox::Yes):
                quitTips = false;
                event->accept();
                writeSettings();
                break;
            case(QMessageBox::No):
                event->accept();
                writeSettings();
                break;
            case (QMessageBox::Cancel):
                event->ignore();
                break;
        }
    }
    //no tip windows write
    writeSettings();
}
void MainWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->accept();
}
void MainWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        QList<QUrl> urls = event->mimeData()->urls();
        for(int i = 0; i < urls.count(); ++i)
        {
            QString filePath = urls.at(i).toLocalFile();
            loadFile(filePath);
        }
        event->accept();
    }
}

//settings
void MainWidget::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("ismax",isMaximun);
    settings.setValue("quit_tips",quitTips);
}
void MainWidget::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(610, 460)).toSize();
    move(pos);
    resize(size);

    isMaximun = settings.value("ismax",false).toBool();
    if(!isMaximun)
    {
        mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum.png);} \
                                                QPushButton:hover{border-image:url(:/Source/image/maximum_hover.png);}");
        mainTitleBar->maximumBtn->setToolTip("最大化");
    }
    else
    {
        mainTitleBar->maximumBtn->setStyleSheet("QPushButton{border-image:url(:/Source/image/maximum_cancel.png);} \
                                                QPushButton:hover{border-image:url(:/Source/image/maximum_cancel_hover.png);}");
        mainTitleBar->maximumBtn->setToolTip("向下还原");
    }

    quitTips = settings.value("quit_tips",true).toBool();

    if(mainMiddleWidget->m_Tab->count() > 0)
    {
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressArea(settings.value("AddressArea",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAsciiArea(settings.value("AsciiArea",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setHighlighting(settings.value("Highlighting",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setOverwriteMode(settings.value("OverwriteMode",true).toBool());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setReadOnly(settings.value("ReadOnly",false).toBool());

        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setHighlightingColor(settings.value("HighlightingColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressAreaColor(settings.value("AddressAreaColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setSelectionColor(settings.value("SelectionColor",QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setFont(settings.value("WidgetFont",QFont("Monospace", 10)).value<QFont>());

        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setAddressWidth(settings.value("AddressAreaWidth",4).toInt());
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setBytesPerLine(settings.value("BytesPerLine",16).toInt());
    }
}

//function part
void MainWidget::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        loadFile(fileName);
    }
}

void MainWidget::loadFile(const QString &fileName)
{
    if(!file_list.contains(fileName))
    {
        QFile *file = new QFile(this);
        file->setFileName(fileName);
        QHexEdit *hexEdit = new QHexEdit();
        if (!hexEdit->setData(*file))
        {
            QMessageBox::warning(this, tr("LinuxHex"),tr("Cannot read file %1:\n%2.").arg(fileName).arg(file->errorString()));
            return;
        }
        mainStatusBar->showMessage("文件打开成功!",2000);
        setTitleFileName(fileName);
        connect(hexEdit,&QHexEdit::dataChanged,this,&MainWidget::dataChanged);
        connect(hexEdit,&QHexEdit::currentSizeChanged,mainStatusBar,&StatusBar::setSize);
        connect(hexEdit,&QHexEdit::currentAddressChanged,mainStatusBar,&StatusBar::setAddress);
        connect(hexEdit, &QHexEdit::overwriteModeChanged, this, &MainWidget::setOverwriteMode);

        QString strippedFileName = strippedName(fileName);
        mainMiddleWidget->m_Tab->insertTab(mainMiddleWidget->m_Tab->count(), hexEdit,strippedFileName);
        //first open a file will final go here
        mainMiddleWidget->m_Tab->setTabToolTip(mainMiddleWidget->m_Tab->count()-1,fileName);
        mainMiddleWidget->m_Tab->setCurrentIndex(mainMiddleWidget->m_Tab->count()-1);
        file_list.append(fileName);
        getFileInfo();
    }
    else
    {
        for(int i = 0; i < mainMiddleWidget->m_Tab->count(); ++i)
        {
            if(fileName == mainMiddleWidget->m_Tab->tabToolTip(i))
            {
                mainMiddleWidget->m_Tab->setCurrentIndex(i);
                break;
            }
        }
    }
}

void MainWidget::setTitleFileName(const QString fileName)
{
    QString strippedFileName = strippedName(fileName);

    if (fileName.isEmpty())
        mainTitleBar->setTitle("* - LinuxHex");
    else
        mainTitleBar->setTitle(strippedFileName + " - LinuxHex");
}

bool MainWidget::save()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        return saveFile(mainMiddleWidget->m_Tab->tabToolTip(mainMiddleWidget->m_Tab->currentIndex()));
    }
    mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    return false;
}

bool MainWidget::saveAs()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"));
        if (fileName.isEmpty())
            return false;

        return saveFile(fileName);
    }
    mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    return false;
}

bool MainWidget::saveFile(const QString &fileName)
{
    QString tmpFileName = fileName + ".~tmp";

    this->setCursor(QCursor(Qt::WaitCursor));
    QFile file(tmpFileName);
    bool ok = reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->write(file);
    //write tmp
    if(ok)
    {
        if (QFile::exists(fileName))
        {
            //remove raw
            ok = QFile::remove(fileName);
            if(!ok)
            {
                this->setCursor(QCursor(Qt::ArrowCursor));
                QMessageBox::warning(this, tr("LinuxHex"), tr("保存文件失败 %1.").arg(fileName));
                return false;
            }
        }
        ok = file.copy(fileName);
        //copy new from tmp
        if (ok)
        {
            ok = QFile::remove(tmpFileName);
            //remove tmp
            if(!ok)
            {
                this->setCursor(QCursor(Qt::ArrowCursor));
                QMessageBox::warning(this, tr("LinuxHex"), tr("保存文件失败 %1.").arg(fileName));
                return false;
            }
        }
        else
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
            QMessageBox::warning(this, tr("LinuxHex"), tr("保存文件失败 %1.").arg(fileName));
            return false;
        }

        this->setCursor(QCursor(Qt::ArrowCursor));
        mainStatusBar->showMessage(tr("文件已保存!"), 2000);
        reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->setModified(false);
        int index = mainMiddleWidget->m_Tab->currentIndex();
        mainTitleBar->setTitle(mainMiddleWidget->m_Tab->tabText(index) + " - LinuxHex");
        return true;
    }
    else
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
        QMessageBox::warning(this, tr("LinuxHex"), tr("保存文件失败 %1.").arg(fileName));
        return false;
    }
}

void MainWidget::saveToReadableFile()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "导出文件");
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QFile::WriteOnly | QFile::Text))
            {
                QMessageBox::warning(this, "LinuxHex", tr("导出文件失败 %1:\n%2.").arg(fileName).arg(file.errorString()));
                return;
            }
            this->setCursor(Qt::WaitCursor);
            file.write(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->toReadableString().toUtf8());
            this->setCursor(QCursor(Qt::ArrowCursor));

            mainStatusBar->showMessage(tr("文件已保存!"), 2000);
        }
    }
    else
    {
        mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    }
}

void MainWidget::saveSelectionToReadableFile()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("导出选中部分"));
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QFile::WriteOnly | QFile::Text)) {
                QMessageBox::warning(this, "LinuxHex", tr("导出选中部分失败 %1:\n%2.").arg(fileName).arg(file.errorString()));
                return;
            }
            this->setCursor(Qt::WaitCursor);
            file.write(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->selectionToReadableString().toUtf8());
            this->setCursor(QCursor(Qt::ArrowCursor));

            mainStatusBar->showMessage(tr("文件已保存!"), 2000);
        }
    }
    else
    {
        mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
    }
}


void MainWidget::setOverwriteMode(bool mode)
{
    QSettings settings;
    settings.setValue("OverwriteMode", mode);
    if (mode)
        mainStatusBar->setOverwriteMode("Overwrite");
    else
        mainStatusBar->setOverwriteMode("Insert");
}

void MainWidget::dataChanged()
{
    bool isSaved = !(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget())->isModified());
    int index = mainMiddleWidget->m_Tab->currentIndex();

    if(isSaved)
        mainTitleBar->setTitle(mainMiddleWidget->m_Tab->tabText(index) + " - LinuxHex");
    else
        mainTitleBar->setTitle("*" + mainMiddleWidget->m_Tab->tabText(index) + " - LinuxHex");
}

void MainWidget::optionAccept()
{
    writeSettings();
    readSettings();
}

void MainWidget::showOptionDialog()
{
    optionDialog->show();
}

void MainWidget::showSearchDialog()
{
    searchDialog->setHexEdit(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget()));
    searchDialog->show();
}

void MainWidget::findNext()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        searchDialog->setHexEdit(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget()));
        searchDialog->findNext();
    }
    else
        mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
}

void MainWidget::findPre()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        searchDialog->setHexEdit(reinterpret_cast<QHexEdit*>(mainMiddleWidget->m_Tab->currentWidget()));
        searchDialog->findPre();
    }
    else
        mainStatusBar->showMessage(tr("请至少打开一个文件!"), 2000);
}

void MainWidget::removeSubTab(int index)
{
    if(mainMiddleWidget->m_Tab->count() > 1)
    {
        file_list.removeOne(mainMiddleWidget->m_Tab->tabToolTip(index));
        mainMiddleWidget->m_Tab->removeTab(index);
    }
}

QString MainWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


QString MainWidget::humanReadableSize(const qint64 &size, int precision)
{
    double sizeAsDouble = size;
    static QStringList measures;
    if (measures.isEmpty())
        measures << QCoreApplication::translate("QInstaller", "bytes")
                 << QCoreApplication::translate("QInstaller", "KB")
                 << QCoreApplication::translate("QInstaller", "MB")
                 << QCoreApplication::translate("QInstaller", "GB")
                 << QCoreApplication::translate("QInstaller", "TB")
                 << QCoreApplication::translate("QInstaller", "PB")
                 << QCoreApplication::translate("QInstaller", "EB")
                 << QCoreApplication::translate("QInstaller", "ZB")
                 << QCoreApplication::translate("QInstaller", "YB");
    QStringListIterator it(measures);
    QString measure(it.next());
    while (sizeAsDouble >= 1024.0 && it.hasNext()) {
        measure = it.next();
        sizeAsDouble /= 1024.0;
    }
    return QString::fromLatin1("%1 %2").arg(sizeAsDouble, 0, 'f', precision).arg(measure);
}

void MainWidget::getFileInfo()
{
    if(mainMiddleWidget->m_Tab->count() >= 1)
    {
        QFileInfo fileinfo;
        fileinfo.setFile(mainMiddleWidget->m_Tab->tabToolTip(mainMiddleWidget->m_Tab->currentIndex()));

        QString fileinfo_str = "";
        fileinfo_str += "名称: <font color='red'>";
        fileinfo_str += strippedName(mainMiddleWidget->m_Tab->tabToolTip(mainMiddleWidget->m_Tab->currentIndex()));
        fileinfo_str += "</font><br/>";
        fileinfo_str += "大小: <font color='red'>";
        fileinfo_str += humanReadableSize(fileinfo.size(),3);
        fileinfo_str += "</font><br/>";
        fileinfo_str += "创建时间: <br/><font color='red'>";
        fileinfo_str += fileinfo.metadataChangeTime().toString("yyyy-MM-dd hh:mm:ss");
        fileinfo_str += "</font><br/>";
        fileinfo_str += "最后读时间: <br/><font color='red'>";
        fileinfo_str += fileinfo.lastRead().toString("yyyy-MM-dd hh:mm:ss");
        fileinfo_str += "</font><br/>";
        fileinfo_str += "最后写时间: <br/><font color='red'>";
        fileinfo_str += fileinfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
        fileinfo_str += "</font><br/>";
        fileinfo_str += "是否为符号链接: <font color='red'>";
        if(fileinfo.isSymLink())
            fileinfo_str += "是";
        else
            fileinfo_str += "否";
        fileinfo_str += "</font><br/>";
        fileinfo_str += "是否可读: <font color='red'>";
        if(fileinfo.isReadable())
            fileinfo_str += "是";
        else
            fileinfo_str += "否";
        fileinfo_str += "</font><br/>";
        fileinfo_str += "是否可写: <font color='red'>";
        if(fileinfo.isWritable())
            fileinfo_str += "是";
        else
            fileinfo_str += "否";
        fileinfo_str += "</font><br/>";
        fileinfo_str += "是否可执行: <font color='red'>";
        if(fileinfo.isExecutable())
            fileinfo_str += "是";
        else
            fileinfo_str += "否";
        fileinfo_str += "</font><br/>";
        fileinfo_str += "拥有者: <font color='red'>";
        fileinfo_str += fileinfo.owner();
        fileinfo_str += "</font><br/>";
        fileinfo_str += "用户组: <font color='red'>";
        fileinfo_str += fileinfo.group();
        fileinfo_str += "</font><br/>";

        infoWidget->setContent(fileinfo_str);
    }
}
