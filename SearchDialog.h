#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QGridLayout>
#include <QDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>

#include "qhexedit.h"

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(QHexEdit *hexEdit,QWidget *parent = nullptr);
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

    qint64 findR();
    qint64 findNext();
    qint64 findPre();

    void replace();
    void replaceAll();

    void setHexEdit(QHexEdit *hex_edit);

private:
    void init();

    QGroupBox *findGroup;
    QComboBox *find_ComboBox;
    QComboBox *find_ContentBox;

    QGroupBox *replaceGroup;
    QComboBox *replace_ComboBox;
    QComboBox *replace_ContentBox;

    QGroupBox *optionGroup;
    QCheckBox *pre_Check;
    QCheckBox *tip_Check;

    QGroupBox *tipGroup;
    QLabel *tip_Label;

    QPushButton *findBtn;
    QPushButton *replaceBtn;
    QPushButton *replaceAllBtn;
    QPushButton *closeBtn;

private:
    QByteArray getContent(int comboIndex, const QString &input);
    qint64 replaceOccurrence(qint64 idx, const QByteArray &replaceBa);

    QHexEdit *_hexEdit;
    QByteArray _findBa;
};

#endif // SEARCHDIALOG_H
