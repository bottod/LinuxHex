#ifndef DUMPWIDGET_H
#define DUMPWIDGET_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DumpWidget;
}

class DumpWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DumpWidget(QWidget *parent = nullptr);
    ~DumpWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void dumpRamInfo(QString &first, QString &final, QString& filename);

private:
    Ui::DumpWidget *ui;
    int i=0;
};

#endif // DUMPWIDGET_H
