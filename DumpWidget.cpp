#include "DumpWidget.h"
#include "ui_DumpWidget.h"
#include <QtDebug>

DumpWidget::DumpWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DumpWidget)
{
    setFixedSize(QSize(348,270));
    ui->setupUi(this);
    ui->lineEdit_2->setText("0x20000000");
    ui->lineEdit->setText("0x20000100");
    ui->lineEdit_3->setText("dump0.bin");
}

DumpWidget::~DumpWidget()
{
    delete ui;
}

void DumpWidget::on_pushButton_clicked()
{
    close();
}

void DumpWidget::on_pushButton_2_clicked()
{
    QString firstadd = ui->lineEdit_2->text();
    QString finaladd = ui->lineEdit->text();
    QString filename = ui->lineEdit_3->text();

    if(firstadd != "" && finaladd != "" && filename != "")
    {
        emit dumpRamInfo(firstadd,finaladd,filename);
        i+=1;
        QString cmd;
        cmd.sprintf("dump%d.bin",i);
        ui->lineEdit_3->setText(cmd);
        close();
    }
    else
    {
       QMessageBox::warning(this, tr("Waring"), tr("检查输入框是否为空!"));
    }
}
