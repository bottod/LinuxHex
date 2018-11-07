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
#include "StatusBar.h"
#include "OptionDialog.h"
#include "SearchDialog.h"
#include "qhexedit.h"

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
    bool isMaximun = false;

    //sys tray
    QSystemTrayIcon *m_SystemTray;
    TrayIconMenu *m_TrayMenu;

    //main menuBar
    QMenuBar *mainMenuBar;

    //list menu
    QMenu *fileMenu;
    QMenu *editMenu;
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

    //for helpMenu
    QAction *aboutAct;

    //TitleBar
    TitleBar *mainTitleBar;

    //StatusBar
    StatusBar *mainStatusBar;

    //Layout
    QVBoxLayout *mainLayout;

    //set dialog
    OptionDialog *optionDialog;
    SearchDialog *searchDialog;

    QString curFileName = "";
    QFile file;
    bool isUntitled = true;            //if there has a file; first open untitled
    bool isSaved = false;              //if this file has been saved
    QHexEdit *hexEdit;


    void initSystemTray();
    void initOtherWidget();
    void initMenu();
    void initAction();
    void initLayout();
    //init all;
    void init();

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
    void setCurrentFile(const QString& fileName);

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

private:
    QString strippedName(const QString &fullFileName);

};

#endif // MAINWIDGET_H
