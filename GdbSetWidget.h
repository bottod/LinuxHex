#ifndef GDBSETWIDGET_H
#define GDBSETWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QRegExp>
#include <QDialog>
#include <QMessageBox>

namespace Ui
{
class GdbSetWidget;
}

class GdbSetWidget : public QDialog
{
    Q_OBJECT

public:
    explicit GdbSetWidget(QWidget *parent = nullptr);
    ~GdbSetWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

signals:
    void send_config(QString gdbpath,QString host,QString port);

private:
    Ui::GdbSetWidget *ui;
    QString GdbPath = "";
    QString hostName = "";
    QString Port = "";

    QString strippedName(const QString &fullFileName);
};

#endif // GDBSETWIDGET_H
