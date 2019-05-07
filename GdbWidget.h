#ifndef GDBWIDGET_H
#define GDBWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QList>
#include <QVector>
#include <QSettings>
#include <QProcess>
#include "DumpWidget.h"
#include "RestoreWidget.h"

namespace Ui
{
class GdbWidget;
}

class GdbWidget : public QDialog
{
    Q_OBJECT

public:
    explicit GdbWidget(QString path, QWidget *parent = nullptr);

    void saveseting(void);
    void loadseting(void);

    void sendText(QString & text);

    void setGdbPath(QString & path);
    void setInfo(QString & host, QString & port);

    ~GdbWidget();

private slots:
    void on_tEdit_shell_cursorPositionChanged();

    void on_tEdit_shell_textChanged();

    void on_cBox_ColorList_currentTextChanged(const QString &arg1);

    void on_pButton_AddquickCompelat_clicked();

    void on_GdbWidget_destroyed();

    void on_tabWidget_currentChanged(int index);

    void on_pButton_delquickCompelat_clicked();

    void on_checkBox_caseSensitive_stateChanged(int arg1);

    void ReadProcessStandardOutput();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void excuDumpInfo(QString str1,QString str2,QString str3);
    void excuWriteInfo(QString cmd);

    void on_pushButton_3_clicked();

signals:
    void dumpingNow(QString dumpfile);

private:

    bool  eventFilter(QObject* target,QEvent * event);
    const QString emptyStr = "";
    QVector<QString> history;
    QVector<QString> quickComplets;
    int historyNum;
    int minTextCurse;
    int lastTextCurse;
    Ui::GdbWidget *ui;
    Qt::CaseSensitivity caseSensitive;

    QProcess autoDebugPs;

    const QString & findQuickCompletString(const QString & str);

    QString gdb_path = "";
    QString host = "";
    QString port = "";

    DumpWidget *dumpWidget;
    QString first_address = "";
    QString last_address = "";
    QString filename = "";

    RestoreWidget *restoreWidget;

};

#endif // GDBWIDGET_H
