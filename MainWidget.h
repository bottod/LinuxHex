#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>

#include "FramelessWidget.h"
#include "TrayIconMenu.h"
#include "TitleBar.h"
#include "MiddleWidget.h"
#include "StatusBar.h"
#include "OptionDialog.h"
#include "SearchDialog.h"
#include "qhexedit.h"
#include "InfoFrame.h"
#include "DataFrame.h"

//Bug List:
//1. the frameless window can't move out the real screen window {[Windows(N)   Linux(Y)]    system bug?(seem yes)}
//2. QFileDialog bug; [Error Msg](GtkDialog mapped without a transient parent. This is discouraged.) {[Windows(N)   Linux(Y)]    system bug?(seem yes)}

class MainWidget : public FramelessWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:

    //app window is max or normal
    bool isMaximun;
    bool quitTips;

    //sys tray
    QSystemTrayIcon *m_SystemTray;
    TrayIconMenu *m_TrayMenu;

    //main menuBar
    QMenuBar *mainMenuBar;

    //list menu
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *watchMenu;
    QMenu *helpMenu;

    //for fileMenu
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *saveReadable;
    QAction *exitAct;

    //for editMenu
    QAction *undoAct;
    QAction *redoAct;
    QAction *saveSelectionReadable;
    QAction *findNextAct;
    QAction *findPreAct;
    QAction *findAct;
    QAction *optionsAct;

    //for watchMenu
    QAction *infoAct;
    QAction *dataAct;

    //bytes to kb...
    QString humanReadableSize(const qint64 &size, int precision);//change byte kb mb

    //for helpMenu
    QAction *aboutAct;

    //TitleBar
    TitleBar *mainTitleBar;

    InfoFrame *infoWidget;
    DataFrame *dataWidget;
    QFrame *leftFrame;

    //middleWidget
    MiddleWidget *mainMiddleWidget;

    //StatusBar
    StatusBar *mainStatusBar;

    //set dialog
    OptionDialog *optionDialog;
    SearchDialog *searchDialog;

    void initSystemTray();
    void initOtherWidget();
    void initMenu();
    void initAction();
    void initLayout();
    //init all;
    void init();

    void getFileInfo();//get current file info;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void writeSettings();
    void readSettings();

private:
    void openFile();
    void loadFile(const QString& fileName);
    void setTitleFileName(const QString fileName);

    bool save();
    bool saveAs();
    bool saveFile(const QString& filename);
    void saveToReadableFile();
    void saveSelectionToReadableFile();

    void setOverwriteMode(bool mode);
    void dataChanged();

    void showOptionDialog();
    void showSearchDialog();

private slots:
    void findNext();
    void findPre();
    void TrayActivated(QSystemTrayIcon::ActivationReason);

public slots:
    void optionAccept();
    void removeSubTab(int index);

private:
    QString strippedName(const QString &fullFileName);

    QStringList file_list;

};

#endif // MAINWIDGET_H
