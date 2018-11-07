#include "OptionDialog.h"

OptionDialog::OptionDialog(QWidget *parent) : QDialog (parent)
{
    init();
    readSettings();
}

void OptionDialog::show()
{
    readSettings();
    this->showNormal();
}

void OptionDialog::init()
{
    QGridLayout *grid = new QGridLayout(this);

    createFlagGroup();
    createStyleGroup();
    createAddressGroup();
    createHexGroup();
    createButtonBox();

    grid->addWidget(FlagGroup,0,0);
    grid->addWidget(StyleGroup,1,0);
    grid->addWidget(AddressGroup,2,0);
    grid->addWidget(HexGroup,3,0);
    grid->addWidget(buttonBox,4,0);
}



void OptionDialog::createFlagGroup()
{
    FlagGroup = new QGroupBox("参数设置",this);

    OverWriteMode_Check = new QCheckBox("插入/修改",this);
    Address_Check = new QCheckBox("显示地址",this);
    Highlight_Check = new QCheckBox("显示高亮",this);
    ASC_Check = new QCheckBox("显示原文",this);
    ReadMode_Check = new QCheckBox("只读模式",this);

    QGridLayout *flagLayout = new QGridLayout(FlagGroup);
    flagLayout->addWidget(OverWriteMode_Check,0,0);
    flagLayout->addWidget(Address_Check,0,1);
    flagLayout->addWidget(Highlight_Check,1,0);
    flagLayout->addWidget(ASC_Check,1,1);
    flagLayout->addWidget(ReadMode_Check,2,0);
}

void OptionDialog::createStyleGroup()
{
    StyleGroup = new QGroupBox("样式选择",this);

    Highlight_Style = new QPushButton("高亮颜色",this);
    connect(Highlight_Style,&QPushButton::clicked,this,&OptionDialog::Highlight_Func);
    Address_Style = new QPushButton("地址颜色",this);
    connect(Address_Style,&QPushButton::clicked,this,&OptionDialog::Address_Func);
    Selection_Style = new QPushButton("选中颜色",this);
    connect(Selection_Style,&QPushButton::clicked,this,&OptionDialog::Selection_Func);
    Font_Style = new QPushButton("字体样式",this);
    connect(Font_Style,&QPushButton::clicked,this,&OptionDialog::Font_Func);
    Highlight_Label = new QLabel(this);
    Address_Label = new QLabel(this);
    Selection_Label = new QLabel(this);
    Font_Edit = new QLineEdit(this);
    Font_Edit->setText("01 23 45 67 89 ab cd ef");

    QGridLayout *styleLayout = new QGridLayout(StyleGroup);
    styleLayout->addWidget(Highlight_Style,0,0);
    styleLayout->addWidget(Highlight_Label,0,1);
    styleLayout->addWidget(Address_Style,1,0);
    styleLayout->addWidget(Address_Label,1,1);
    styleLayout->addWidget(Selection_Style,2,0);
    styleLayout->addWidget(Selection_Label,2,1);
    styleLayout->addWidget(Font_Style,3,0);
    styleLayout->addWidget(Font_Edit,3,1);
}

void OptionDialog::createAddressGroup()
{
    AddressGroup = new QGroupBox("地址区",this);

    Address_Width_Label = new QLabel("地址长度",this);
    Address_Width_Spin = new QSpinBox(this);
    Address_Width_Spin->setValue(4);

    QGridLayout *addressLayout = new QGridLayout(AddressGroup);
    addressLayout->addWidget(Address_Width_Label,0,0);
    addressLayout->addWidget(Address_Width_Spin,0,1);
}

void OptionDialog::createHexGroup()
{
    HexGroup = new QGroupBox("16进制区",this);

    Hex_Width_Label = new QLabel("每行字符数",this);
    Hex_Width_Spin = new QSpinBox(this);
    Hex_Width_Spin->setValue(16);

    QGridLayout *HexLayout = new QGridLayout(HexGroup);
    HexLayout->addWidget(Hex_Width_Label,0,0);
    HexLayout->addWidget(Hex_Width_Spin,0,1);
}

void OptionDialog::createButtonBox()
{
    buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton("确定",QDialogButtonBox::AcceptRole);
    buttonBox->addButton("取消",QDialogButtonBox::RejectRole);
    connect(buttonBox,&QDialogButtonBox::accepted,this,&OptionDialog::acceptEvent);
    connect(buttonBox,&QDialogButtonBox::rejected,this,&OptionDialog::hide);
}



void OptionDialog::acceptEvent()
{
    writeSettings();
    emit accepted();
    hide();
}

void OptionDialog::setColor(QWidget *widget, QColor color)
{
    QPalette palette = widget->palette();
    palette.setColor(QPalette::Background, color);
    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}

void OptionDialog::readSettings()
{
    QSettings settings;

    Address_Check->setChecked(settings.value("AddressArea", true).toBool());
    ASC_Check->setChecked(settings.value("AsciiArea", true).toBool());
    Highlight_Check->setChecked(settings.value("Highlighting", true).toBool());
    OverWriteMode_Check->setChecked(settings.value("OverwriteMode", true).toBool());
    ReadMode_Check->setChecked(settings.value("ReadOnly").toBool());

    setColor(Highlight_Label, settings.value("HighlightingColor", QColor(0xff, 0xff, 0x99, 0xff)).value<QColor>());
    setColor(Address_Label, settings.value("AddressAreaColor", this->palette().alternateBase().color()).value<QColor>());
    setColor(Selection_Label, settings.value("SelectionColor", this->palette().highlight().color()).value<QColor>());
    Font_Edit->setFont(settings.value("WidgetFont", QFont("Monospace", 10)).value<QFont>());


    Address_Width_Spin->setValue(settings.value("AddressAreaWidth", 4).toInt());
    Hex_Width_Spin->setValue(settings.value("BytesPerLine", 16).toInt());
}

void OptionDialog::writeSettings()
{
    QSettings settings;
    settings.setValue("AddressArea", Address_Check->isChecked());
    settings.setValue("AsciiArea", ASC_Check->isChecked());
    settings.setValue("Highlighting", Highlight_Check->isChecked());
    settings.setValue("OverwriteMode", OverWriteMode_Check->isChecked());
    settings.setValue("ReadOnly", ReadMode_Check->isChecked());

    settings.setValue("HighlightingColor", Highlight_Label->palette().color(QPalette::Background));
    settings.setValue("AddressAreaColor", Address_Label->palette().color(QPalette::Background));
    settings.setValue("SelectionColor", Selection_Label->palette().color(QPalette::Background));
    settings.setValue("WidgetFont",Font_Edit->font());

    settings.setValue("AddressAreaWidth", Address_Width_Spin->value());
    settings.setValue("BytesPerLine", Hex_Width_Spin->value());
}


void OptionDialog::Highlight_Func()
{
    QColor color = QColorDialog::getColor(Highlight_Label->palette().color(QPalette::Background), this);
    if (color.isValid())
        setColor(Highlight_Label, color);
}

void OptionDialog::Address_Func()
{
    QColor color = QColorDialog::getColor(Address_Label->palette().color(QPalette::Background), this);
    if (color.isValid())
        setColor(Address_Label, color);
}

void OptionDialog::Selection_Func()
{
    QColor color = QColorDialog::getColor(Selection_Label->palette().color(QPalette::Background), this);
    if (color.isValid())
        setColor(Selection_Label, color);
}

void OptionDialog::Font_Func()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, Font_Edit->font(), this);
    if (ok)
        Font_Edit->setFont(font);
}
