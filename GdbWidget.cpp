#include "GdbWidget.h"
#include "ui_GdbWidget.h"

#include <QDebug>
#include<QTextLayout>
#include <QTextEdit>
#include <QScrollBar>
#include <QVector>
#include <QTimer>
#include <QSettings>
#include <string.h>
#define qout qDebug()

GdbWidget::GdbWidget(QString path, QWidget *parent) :
    QDialog (parent),
    ui(new Ui::GdbWidget)
{
    minTextCurse = 0;
    ui->setupUi(this);
    ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Checked);
    caseSensitive = Qt::CaseSensitive;
    ui->tEdit_shell->installEventFilter(this);
    ui->tEdit_shell->setHtml("<body bgcolor=\"#000000\"></body>");
    ui->tEdit_shell->setTextColor("green");
    ui->tEdit_shell->insertPlainText("Bottod Shell V0.1\n");
    ui->tEdit_shell->setFocus();
    quickComplets.append("@CMD.clean");
    loadseting();

    gdb_path = path;
    autoDebugPs.start(gdb_path);
    autoDebugPs.waitForStarted();
    connect(&autoDebugPs,&QProcess::readyReadStandardOutput,this,&GdbWidget::ReadProcessStandardOutput);
    connect(&autoDebugPs,&QProcess::readyReadStandardError,this,&GdbWidget::ReadProcessStandardOutput);

    minTextCurse = ui->tEdit_shell->textCursor().position();

    dumpWidget = new DumpWidget(this);
    connect(dumpWidget,&DumpWidget::dumpRamInfo,this,&GdbWidget::excuDumpInfo);

    restoreWidget = new RestoreWidget(this);
    connect(restoreWidget,&RestoreWidget::WriteRamInfo,this, &GdbWidget::excuWriteInfo);

}

void GdbWidget::setGdbPath(QString & path)
{
    gdb_path = path;
    autoDebugPs.close();
    autoDebugPs.start(gdb_path);
    autoDebugPs.waitForStarted();
}

GdbWidget::~GdbWidget()
{
    saveseting();
    autoDebugPs.close();
    delete ui;
}

bool  GdbWidget:: eventFilter(QObject* target,QEvent * event)
{

    if(target == ui->tEdit_shell)
    {
        QTextCursor txtcur = ui->tEdit_shell->textCursor();
        if(event->type()==QEvent::KeyPress)
        {
            if(ui->tEdit_shell->textCursor().position()< minTextCurse)
                return true ;

            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter)
            {
                txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                txtcur.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                QString msg = txtcur.selectedText();
                if(history.isEmpty() || QString::compare(msg,history.back()) != 0)
                    history.append(msg);
                if(msg.compare("@CMD.clean") == 0)
                {
                    ui->tEdit_shell->setText("");
                    ui->tEdit_shell->setTextColor(ui->cBox_ColorList->currentText());
                    ui->tEdit_shell->setHtml("<body bgcolor=\"#000000\"></body>");

                    ui->tEdit_shell->append("clean");
                    minTextCurse = ui->tEdit_shell->textCursor().position();
//                    ui->tEdit_shell->setFocus();
                }
                else
                {
                    sendText(msg);
                }

                historyNum = history.size();
                ui->tEdit_shell->append("");
                txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                ui->tEdit_shell->setTextCursor(txtcur);
                minTextCurse = ui->tEdit_shell->textCursor().position();
                return true;
            }
            else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Up)
            {
                QTextCursor tc =  ui->tEdit_shell->textCursor();

                if(history.size() == 0) return true;//如果没有历史记录,则不操作


                    tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                    tc.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                    tc.removeSelectedText();
                if(historyNum == 0)
                    historyNum = history.size();
                if(historyNum > history.size())
                    historyNum = 1;
                ui->tEdit_shell->insertPlainText(history[historyNum-1]); //插入上一个输入的历史记录
                lastTextCurse = ui->tEdit_shell->textCursor().position();
                qout<<history[historyNum-1]<<"history size "<< history.length();
                historyNum--;
                qout<<"使用上一个记录"<<endl;

                return true;
            }
            else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Down)
            {
                QTextCursor tc =  ui->tEdit_shell->textCursor();

                if(history.size() == 0) return true;//如果没有历史记录,则不操作
                tc.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
                tc.setPosition(minTextCurse,QTextCursor::KeepAnchor);
                tc.removeSelectedText();
                if(historyNum > history.size())
                    historyNum = 1;
                if(historyNum == 0)
                    historyNum = history.size();
                ui->tEdit_shell->insertPlainText(history[historyNum-1]); //插入上一个输入的历史记录
                lastTextCurse = ui->tEdit_shell->textCursor().position();
                qout<<history[historyNum-1]<<"history size "<< history.length();
                historyNum++;
                qout<<"使用下一个记录"<<endl;

                return true;
            }
            else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Tab)
            {
                qout<<"tab"<<endl;
                //得到最后一行的字符
                QTextCursor txtcur = ui->tEdit_shell->textCursor();
                txtcur.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
                QString msg = txtcur.selectedText();
                int index = msg.lastIndexOf(' ');
                if(index == -1)
                    index = 0;
                else
                    index++;
                QString ins = msg.mid(index);
                const QString insertStr = findQuickCompletString( ins);
                if(insertStr != "")
                {
                    txtcur = ui->tEdit_shell->textCursor();
                    txtcur.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,ins.length());
                    txtcur.removeSelectedText();
                    ui->tEdit_shell->insertPlainText(findQuickCompletString( msg.mid( msg.lastIndexOf(' ')+1)));
                }
                qout<<"ins :" <<ins <<endl;


                return true;
            }
            else if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Backspace)
            {
                QTextCursor tc = ui->tEdit_shell->textCursor();
                qout<<"back";
                if(tc.position()<=minTextCurse)
                {
                    qout << "delete over";
                    return true;
                }


            }
            else if(static_cast<QKeyEvent *>(event)->key() == Qt::Key_Left)
            {
                if(minTextCurse == ui->tEdit_shell->textCursor().position())
                {
                    return  true;
                }

            }
        }
    }
    return QWidget::eventFilter(target,event);
}

void GdbWidget::sendText(QString & text)
{
    for(int i = 0;i<text.length();i++)
    {
        if(text.at(i) == '\\' && (i+1)<text.length())
        {
            if(text.at(i+1) == '\\')
            {
                text.remove(i+1,1);
            }
            else if(text.at(i+1) == 't')
            {
                text.replace(i,1,'\t');
                text.remove(i+1,1);
            }
            else if (text.at(i+1) == 'n')
            {
                text.replace(i,1,'\n');
                text.remove(i+1,1);
            }
        }
    }
    text.append("\n");qout<<text<<endl;
    qout<<"send has be called,will send string:"<<text<<endl;
    autoDebugPs.write(text.toStdString().c_str());

}

void GdbWidget::ReadProcessStandardOutput()
{
    QString ret = autoDebugPs.readAllStandardOutput();
    QString ret_err = autoDebugPs.readAllStandardError();
    if(ret.isEmpty())
        ret = ret_err;

    ui->tEdit_shell->append(ret); //get gdb msg
    //reset cursor make readonly
    QTextCursor txtcur = ui->tEdit_shell->textCursor();
    txtcur.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
    ui->tEdit_shell->setTextCursor(txtcur);
    minTextCurse = ui->tEdit_shell->textCursor().position();
}


void GdbWidget::on_tEdit_shell_cursorPositionChanged()
{
    //do nothing;
    if(ui->tEdit_shell->textCursor().position()<minTextCurse)
        ui->tEdit_shell->setReadOnly(true);
    else
    {
        ui->tEdit_shell->setReadOnly(false);
    }
}

void GdbWidget::on_tEdit_shell_textChanged()
{
    QScrollBar *qbar =  ui->tEdit_shell->verticalScrollBar();
    qbar->setValue(qbar->maximum());
}

const QString & GdbWidget::findQuickCompletString(const QString & str)
{
    int retindex = -1;
    for(int i = 0;i<quickComplets.size();i++)
    {

            qout<<"find quitck index :" << i<<"quickComplets[i].indexOf("<<str<<") == "<<quickComplets[i].indexOf(str,0,caseSensitive) <<endl;
            
            if(quickComplets[i].indexOf(str,0,caseSensitive) == 0)
            {
                if(retindex == -1)
                    retindex = i;
                else
                {
                    retindex = -1;
                    break;
                 }
            }

    }
    if(retindex == -1)
        return  emptyStr;
    else
        return quickComplets[retindex];
}

void GdbWidget::on_cBox_ColorList_currentTextChanged(const QString &arg1)
{
    qout<<"change str"<<arg1<<endl;

    ui->tEdit_shell->setTextColor(arg1);
    QTextCursor tc = ui->tEdit_shell->textCursor();
    tc.movePosition(QTextCursor::End);
//    ui->tEdit_shell->setTextCursor(tc);
    ui->tEdit_shell->insertPlainText("text color change :"+arg1+"\n");
    minTextCurse = ui->tEdit_shell->textCursor().position();
}

void GdbWidget::on_pButton_AddquickCompelat_clicked()
{
    QString plaintext = ui->plaintEdit_quickCompleat->toPlainText();
    plaintext.remove('\n');
    plaintext.remove(' ');
    qout<<"plaintext"<<plaintext;
    QStringList sliplist = plaintext.split(',');

    //插入到快捷补全的数组中去.
    for(int i = 0;i<sliplist.size();i++)
    {
        bool is_exist = false;
        if(sliplist[i].size() == 0) continue;
        for(int j = 0;j<quickComplets.size();j++)
        {
            if(QString::compare(sliplist[i],quickComplets[j],caseSensitive) == 0)
            {
                qout<<"检测到"<<sliplist[i]<<"重复"<<endl;
                is_exist = true;
                break;
            }
        }
        if(is_exist == true)
            continue;
        else
        {
            quickComplets.append(sliplist[i]);
        }
    }
}

void GdbWidget::on_GdbWidget_destroyed()
{
    qout<<"关闭"<<endl;
}

void GdbWidget::saveseting(void)
{
    QSettings setting("BottodGdbShell","BottodGdbShell");
    setting.setValue("isAutosive",1);
    setting.setValue("iscaseSensitive",caseSensitive);
    setting.setValue("textcolor",ui->cBox_ColorList->currentText());
    setting.sync();
}

void GdbWidget::loadseting(void)
{
    QSettings setting("BottodGdbShell","BottodGdbShell");
    if(setting.value("isAutosive").toInt() == 0)
        return ;
    if(setting.value("iscaseSensitive").toInt() == 1)
    {
        caseSensitive = Qt::CaseSensitive;
        ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Checked);
    }
    else
    {
        caseSensitive = Qt::CaseInsensitive;
        ui->checkBox_caseSensitive->setCheckState(Qt::CheckState::Unchecked);
    }

    ui->tEdit_shell->setTextColor(setting.value("textcolor").toString());
    ui->cBox_ColorList->setCurrentText(setting.value("textcolor").toString());
    ui->tEdit_shell->setTextColor(ui->cBox_ColorList->currentText());
    setting.setValue("isAutosive",1);
    setting.sync();
}


void GdbWidget::on_tabWidget_currentChanged(int index)
{
    qout<<"index"<<index;
    if(index == 1)
    {
        //reflash quick complet list
        QString listStr = "";
        for(int i = 0;i<quickComplets.size();i++)
        {
            listStr.append(quickComplets[i]+",\n");
        }
        listStr.remove( listStr.lastIndexOf(','),1);
        ui->plaintEdit_quickCompleat->clear();
        ui->plaintEdit_quickCompleat->setPlainText(listStr);
        //reflash over
    }
}

void GdbWidget::on_pButton_delquickCompelat_clicked()
{
    QString selecttext =  ui->plaintEdit_quickCompleat->textCursor().selectedText() ;
    selecttext.remove(' ');
    selecttext.remove(',');
    selecttext.remove('\n');
    quickComplets.remove( quickComplets.indexOf(selecttext),1);
    ui->plaintEdit_quickCompleat->textCursor().removeSelectedText();
}

void GdbWidget::on_checkBox_caseSensitive_stateChanged(int arg1)
{
    if(arg1== 0)
        caseSensitive = Qt::CaseInsensitive;
    else
    {
        caseSensitive = Qt::CaseSensitive;
    }
}

void GdbWidget::on_pushButton_clicked()
{
    QString cmd;
    cmd.sprintf("target remote %s:%s\n",host.toStdString().c_str(),port.toStdString().c_str());
    autoDebugPs.write(cmd.toStdString().c_str());
}

void GdbWidget::setInfo(QString & m_host, QString & m_port)
{
    host = m_host;
    port = m_port;
}

void GdbWidget::on_pushButton_4_clicked()
{
    autoDebugPs.close();
    autoDebugPs.start(gdb_path);
    autoDebugPs.waitForStarted();
}

void GdbWidget::on_pushButton_2_clicked()
{
    dumpWidget->show();
}

 void GdbWidget::excuDumpInfo(QString str1,QString str2, QString str3)
 {
     first_address = str1;
     last_address = str2;
     filename = str3;
     QString cmd = "";
     cmd.sprintf("dump binary memory %s %s %s\n",filename.toStdString().c_str(),first_address.toStdString().c_str(),last_address.toStdString().c_str());
     autoDebugPs.write(cmd.toStdString().c_str());

     emit dumpingNow(filename);
 }

 void GdbWidget::excuWriteInfo(QString cmd)
 {
     autoDebugPs.write(cmd.toStdString().c_str());
 }

void GdbWidget::on_pushButton_3_clicked()
{
    restoreWidget->show();
}
