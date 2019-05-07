#include "GdbSetWidget.h"
#include "ui_GdbSetWidget.h"
#include <QtDebug>

GdbSetWidget::GdbSetWidget(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::GdbSetWidget)
{
    setFixedSize(QSize(385,303));
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    setFocus();

    QRegExp regExpIP(R"((2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})(\.(2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})){3})");//正则表达式，ip
    ui->lineEdit_2->setValidator(new QRegExpValidator(regExpIP,(this)));
    ui->lineEdit_2->setText("127.0.0.1");

    QRegExp regExpPort(R"(/^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)/)");//正则表达式，1-65535
    ui->lineEdit_3->setValidator(new QRegExpValidator(regExpPort,(this)));
    ui->lineEdit_3->setText("2331");
}

GdbSetWidget::~GdbSetWidget()
{
    delete ui;
}

void GdbSetWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        GdbPath = fileName;
        ui->lineEdit->setText(strippedName(fileName));
        ui->lineEdit->setCursorPosition(0);
        ui->lineEdit->setToolTip(fileName);
    }
}

QString GdbSetWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void GdbSetWidget::on_pushButton_3_clicked()
{
    hostName = ui->lineEdit_2->text();
    Port = ui->lineEdit_3->text();
    if(GdbPath != "" && hostName != "" && Port != "")
    {
        emit send_config(GdbPath,hostName,Port);
        this->close();
    }
    else
    {
       QMessageBox::warning(this, tr("Waring"), tr("检查输入框是否为空!"));
    }
}

void GdbSetWidget::on_pushButton_2_clicked()
{
    this->close();
}
