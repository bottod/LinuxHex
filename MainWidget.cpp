#include "MainWidget.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : FramelessWidget(parent)
{
    setMinimumSize(480,320);

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

    helpMenu->addAction(aboutAct);

    mainMenuBar->addMenu(fileMenu);
    mainMenuBar->addMenu(editMenu);
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
    connect(undoAct, &QAction::triggered, hexEdit, &QHexEdit::undo);

    redoAct = new QAction(QIcon(":/Source/image/redo.png"), "&Redo", this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, hexEdit, &QHexEdit::redo);

    saveSelectionReadable = new QAction("导出选中部分", this);
    connect(saveSelectionReadable,&QAction::triggered,this,&MainWidget::saveSelectionToReadableFile);

    aboutAct = new QAction(QIcon(":/Source/image/app.png"),"关于(&P)", this);
    connect(aboutAct,&QAction::triggered,[=]()
    {
        QMessageBox::about(this, "关于 LinuxHex","遵循GPL协议的开源软件");
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
}

void MainWidget::initOtherWidget()
{
    hexEdit = new QHexEdit(this);
    connect(hexEdit,&QHexEdit::dataChanged,this,&MainWidget::dataChanged);

    optionDialog = new OptionDialog(this);
    connect(optionDialog, &OptionDialog::accepted, this, &MainWidget::optionAccept);

    searchDialog = new SearchDialog(hexEdit,this);

    mainTitleBar = new TitleBar(this);
    connect(mainTitleBar->minimumBtn,&QPushButton::clicked,this,&MainWidget::showMinimized);
    connect(mainTitleBar->maximumBtn,&QPushButton::clicked,[&]()
    {
        if(isMaximun)
        {
            isMaximun = false;
            showNormal();
        }
        else
        {
            isMaximun = true;
            showMaximized();
        }
    });
    connect(mainTitleBar->closeBtn,&QPushButton::clicked,this,&MainWidget::close);
    connect(mainTitleBar->setBtn,&QPushButton::clicked,this,&MainWidget::showOptionDialog);

    mainStatusBar = new StatusBar(this);
    mainStatusBar->setAutoFillBackground(true);
    connect(hexEdit,&QHexEdit::currentSizeChanged,mainStatusBar,&StatusBar::setSize);
    connect(hexEdit,&QHexEdit::currentAddressChanged,mainStatusBar,&StatusBar::setAddress);
    connect(hexEdit, &QHexEdit::overwriteModeChanged, this, &MainWidget::setOverwriteMode);

}

void MainWidget::initLayout()
{
    mainLayout = new QVBoxLayout(this);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(mainTitleBar);
    mainLayout->addWidget(mainMenuBar);
    mainLayout->addWidget(hexEdit);
    mainLayout->addWidget(mainStatusBar);

    this->setLayout(mainLayout);
}

//init all
void MainWidget::init()
{
    //enable drag
    setAcceptDrops(true);

    initOtherWidget();
    readSettings();

    initSystemTray();
    initAction();
    initMenu();

    initLayout();
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
            showNormal();
            mainTitleBar->setMaxValue(false);
            isMaximun = false;
        }
        else
        {
            showMaximized();
            mainTitleBar->setMaxValue(true);
            isMaximun = true;
        }
    }
    return QWidget::mouseDoubleClickEvent(event);
}
void MainWidget::closeEvent(QCloseEvent *event)
{
    writeSettings();
    if(!isUntitled && !isSaved)
    {
        QString strippedFileName = strippedName(curFileName);

        QString messageTitle = "在关闭前将更改保存到文档\"" + strippedFileName + "\"吗?";
        QString messageContent = "如果您不保存，之前所做的更改将永久丢失";

        QMessageBox closMessage(QMessageBox::Question, messageTitle, messageContent);
        closMessage.addButton(QMessageBox::No);
        closMessage.setButtonText(QMessageBox::No, QString("不保存退出(&W)"));

        closMessage.addButton(QMessageBox::Cancel);
        closMessage.setButtonText(QMessageBox::Cancel, QString("取消(&C)"));

        closMessage.addButton(QMessageBox::Yes);
        closMessage.setButtonText(QMessageBox::Yes, QString("保存(&S)"));

        int result = closMessage.exec();
        switch (result)
        {
            case (QMessageBox::Yes):
                saveFile(curFileName);
                event->accept();
                break;
            case(QMessageBox::No):
                event->accept();
                break;
            case (QMessageBox::Cancel):
                event->ignore();
                break;
        }
    }
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
        QString filePath = urls.at(0).toLocalFile();
        loadFile(filePath);
        event->accept();
    }
}

//settings
void MainWidget::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
void MainWidget::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(610, 460)).toSize();
    move(pos);
    resize(size);

    hexEdit->setAddressArea(settings.value("AddressArea").toBool());
    hexEdit->setAsciiArea(settings.value("AsciiArea").toBool());
    hexEdit->setHighlighting(settings.value("Highlighting").toBool());
    hexEdit->setOverwriteMode(settings.value("OverwriteMode").toBool());
    hexEdit->setReadOnly(settings.value("ReadOnly").toBool());

    hexEdit->setHighlightingColor(settings.value("HighlightingColor").value<QColor>());
    hexEdit->setAddressAreaColor(settings.value("AddressAreaColor").value<QColor>());
    hexEdit->setSelectionColor(settings.value("SelectionColor").value<QColor>());
    hexEdit->setFont(settings.value("WidgetFont").value<QFont>());

    hexEdit->setAddressWidth(settings.value("AddressAreaWidth").toInt());
    hexEdit->setBytesPerLine(settings.value("BytesPerLine").toInt());
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
    file.setFileName(fileName);
    if (!hexEdit->setData(file))
    {
        QMessageBox::warning(this, tr("LinuxHex"),tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    mainStatusBar->showMessage("文件打开成功!",2000);
    setCurrentFile(fileName);
}

void MainWidget::setCurrentFile(const QString &fileName)
{
    curFileName = QFileInfo(fileName).canonicalFilePath();
    isUntitled = fileName.isEmpty();
    QString strippedFileName = strippedName(curFileName);

    if (fileName.isEmpty())
        mainTitleBar->setTitle("* - LinuxHex");
    else
        mainTitleBar->setTitle(strippedFileName + " - LinuxHex");
}


bool MainWidget::save()
{
    if (isUntitled)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFileName);
    }
}

bool MainWidget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"),curFileName);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MainWidget::saveFile(const QString &fileName)
{
    QString tmpFileName = fileName + ".~tmp";

    this->setCursor(QCursor(Qt::WaitCursor));
    QFile file(tmpFileName);
    bool ok = hexEdit->write(file);
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
        setCurrentFile(fileName);
        mainStatusBar->showMessage(tr("文件已保存!"), 2000);
        return true;
    }
    else
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
        QMessageBox::warning(this, tr("LinuxHex"), tr("保存文件失败 %1.").arg(fileName));
        setCurrentFile(fileName);
        return false;
    }
}

void MainWidget::saveToReadableFile()
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
        file.write(hexEdit->toReadableString().toUtf8());
        this->setCursor(QCursor(Qt::ArrowCursor));

        mainStatusBar->showMessage(tr("文件已保存!"), 2000);
    }
}

void MainWidget::saveSelectionToReadableFile()
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
        file.write(hexEdit->selectionToReadableString().toUtf8());
        this->setCursor(QCursor(Qt::ArrowCursor));

        mainStatusBar->showMessage(tr("文件已保存!"), 2000);
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
    isSaved = !(hexEdit->isModified());
    QString strippedFileName = strippedName(curFileName);

    if(isSaved)
        mainTitleBar->setTitle(strippedFileName + " - LinuxHex");
    else
        mainTitleBar->setTitle("*" + strippedFileName + " - LinuxHex");
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
    searchDialog->show();
}

void MainWidget::findNext()
{
    searchDialog->findNext();
}

void MainWidget::findPre()
{
    searchDialog->findPre();
}

QString MainWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


