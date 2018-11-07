#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFontDialog>
#include <QColorDialog>
#include <QSpinBox>
#include <QSettings>

class OptionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OptionDialog(QWidget *parent = nullptr);

    void show();

private:
    void init();

    QCheckBox *OverWriteMode_Check;
    QCheckBox *Address_Check;
    QCheckBox *Highlight_Check;
    QCheckBox *ASC_Check;
    QCheckBox *ReadMode_Check;
    QGroupBox *FlagGroup;
    void createFlagGroup();

    QPushButton *Highlight_Style;
    QPushButton *Address_Style;
    QPushButton *Selection_Style;
    QPushButton *Font_Style;
    QLabel *Highlight_Label;
    QLabel *Address_Label;
    QLabel *Selection_Label;
    QLineEdit *Font_Edit;
    QGroupBox *StyleGroup;
    void createStyleGroup();

    QSpinBox *Address_Width_Spin;
    QLabel *Address_Width_Label;
    QGroupBox *AddressGroup;
    void createAddressGroup();


    QSpinBox *Hex_Width_Spin;
    QLabel *Hex_Width_Label;
    QGroupBox *HexGroup;
    void createHexGroup();


    QDialogButtonBox *buttonBox;
    void createButtonBox();

signals:
    void accepted();

private:
    void setColor(QWidget *widget, QColor color);
    void acceptEvent();

    void readSettings();
    void writeSettings();

private slots:
    void Highlight_Func();
    void Address_Func();
    void Selection_Func();
    void Font_Func();

};

#endif // OPTIONDIALOG_H
