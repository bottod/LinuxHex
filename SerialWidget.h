#ifndef SERIALWIDGET_H
#define SERIALWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>
#include <QVector>
#include <QTimer>
#include <QSettings>
namespace Ui
{
class SerialWidget;
}

class SerialWidget : public QDialog
{
    Q_OBJECT

public:
    explicit SerialWidget(QWidget *parent = nullptr);
    void scanport(void);
    QString reciver(void);
    void sendText(QString& text);
    void openprot(void);
    void saveseting(void);
    void loadseting(void);
    void openprot(const QString & portname,const int baud);
    ~SerialWidget();

private slots:
    void on_tEdit_shell_cursorPositionChanged();

    void on_pButton_send_clicked();

    void on_pushButton_2_clicked();

    void receiveInfo();

    void on_pushButton_clicked();

    void on_tEdit_shell_textChanged();

    void on_timerOver();

    void on_cBox_ColorList_currentTextChanged(const QString &arg1);

    void on_pButton_AddquickCompelat_clicked();

    void on_serialErrorOccured();

    void on_SerialWidget_destroyed();

    void on_tabWidget_currentChanged(int index);

    void on_pButton_delquickCompelat_clicked();

    void on_checkBox_caseSensitive_stateChanged(int arg1);

private:

    bool  eventFilter(QObject* target,QEvent * event);
    const QString emptyStr = "";
    QVector<QString> history;
    QVector<QString> quickComplets;
    int historyNum;
    int minTextCurse;
    int lastTextCurse;
    QTimer overTimer;                   //串口是否发送完成定时器
    Ui::SerialWidget *ui;
    bool isopen;
    Qt::CaseSensitivity caseSensitive;
    QSerialPort* activePort;
    char receiverBuff [2048];
    int baud;
    const QString & findQuickCompletString(const QString & str);

};

#endif // SERWIDGET_H
