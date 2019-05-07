#ifndef RESTOREWIDGET_H
#define RESTOREWIDGET_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RestoreWidget;
}

class RestoreWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RestoreWidget(QWidget *parent = nullptr);
    ~RestoreWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void WriteRamInfo(QString &str);

private:
    Ui::RestoreWidget *ui;

    QString strippedName(const QString &fullFileName);
};

#endif // RESTOREWIDGET_H
