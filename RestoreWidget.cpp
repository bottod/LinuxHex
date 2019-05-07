#include "RestoreWidget.h"
#include "ui_RestoreWidget.h"
#include <QtDebug>
#include <QFileDialog>

RestoreWidget::RestoreWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestoreWidget)
{
    setFixedSize(QSize(348,270));
    ui->setupUi(this);
    ui->lineEdit_2->setText("0x20000000");
    ui->lineEdit_3->setReadOnly(true);
}

RestoreWidget::~RestoreWidget()
{
    delete ui;
}

void RestoreWidget::on_pushButton_clicked()
{
    close();
}

void RestoreWidget::on_pushButton_2_clicked()
{
    QString firstadd = ui->lineEdit_2->text();
    QString filename = ui->lineEdit_3->toolTip();

    if(firstadd != "" && filename != "")
    {
        QString cmd = "";
        cmd.sprintf("restore %s binary %s\n",filename.toStdString().c_str(),firstadd.toStdString().c_str());
        qDebug()<<cmd;
        emit WriteRamInfo(cmd);
        close();
    }
    else
    {
       QMessageBox::warning(this, tr("Waring"), tr("检查输入框是否为空!"));
    }
}

void RestoreWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        ui->lineEdit_3->setText(strippedName(fileName));
        ui->lineEdit_3->setCursorPosition(0);
        ui->lineEdit_3->setToolTip(fileName);
    }
}

QString RestoreWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
