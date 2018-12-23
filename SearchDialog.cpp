#include "SearchDialog.h"

SearchDialog::SearchDialog(QHexEdit *hexEdit, QWidget *parent) :
    QDialog (parent)
{
    _hexEdit = hexEdit;
    init();
}

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog (parent)
{
    init();
}

SearchDialog::~SearchDialog()
{
}

void SearchDialog::init()
{
    QGridLayout *grid = new QGridLayout(this);

    QVBoxLayout *findMainLayout = new QVBoxLayout;

    findGroup = new QGroupBox("查找",this);
    QHBoxLayout * h_findLayout = new QHBoxLayout(findGroup);
    find_ComboBox = new QComboBox(this);
    find_ComboBox->addItem("Hex");
    find_ComboBox->addItem("UTF8");
    find_ComboBox->setCurrentIndex(0);
    find_ComboBox->setEditable(false);
    find_ContentBox = new QComboBox(this);
    find_ContentBox->setEditable(true);
    h_findLayout->addWidget(find_ComboBox);
    h_findLayout->addWidget(find_ContentBox);

    replaceGroup = new QGroupBox("替换",this);
    QHBoxLayout * h_replaceLayout = new QHBoxLayout(replaceGroup);
    replace_ComboBox = new QComboBox(this);
    replace_ComboBox->addItem("Hex");
    replace_ComboBox->addItem("UTF8");
    replace_ComboBox->setCurrentIndex(0);
    replace_ComboBox->setEditable(false);
    replace_ContentBox = new QComboBox(this);
    replace_ContentBox->setEditable(true);
    h_replaceLayout->addWidget(replace_ComboBox);
    h_replaceLayout->addWidget(replace_ContentBox);
    replaceGroup->setLayout(h_replaceLayout);

    optionGroup = new QGroupBox("参数",this);
    QVBoxLayout * v_optionLayout = new QVBoxLayout(optionGroup);
    pre_Check = new QCheckBox("向前查找",this);
    tip_Check = new QCheckBox("替换前弹窗",this);
    v_optionLayout->addWidget(pre_Check);
    v_optionLayout->addWidget(tip_Check);
    optionGroup->setLayout(v_optionLayout);

    tipGroup = new QGroupBox("提示",this);
    QVBoxLayout * v_tipLayout = new QVBoxLayout(tipGroup);
    tip_Label = new QLabel(R"**(请明确 "目标位置" 以及 "光标位置" !!)**",this);
    v_tipLayout->addWidget(tip_Label);

    findMainLayout->addWidget(findGroup);
    findMainLayout->addWidget(replaceGroup);
    findMainLayout->addWidget(optionGroup);
    findMainLayout->addWidget(tipGroup);



    QVBoxLayout *findSndLayout = new QVBoxLayout;
    findBtn = new QPushButton("查找",this);
    connect(findBtn,&QPushButton::clicked,this,&SearchDialog::findR);
    replaceBtn = new QPushButton("替换",this);
    connect(replaceBtn,&QPushButton::clicked,this,&SearchDialog::replace);
    replaceAllBtn = new QPushButton("替换全部",this);
    connect(replaceAllBtn,&QPushButton::clicked,this,&SearchDialog::replaceAll);
    closeBtn = new QPushButton("关闭",this);
    connect(closeBtn,&QPushButton::clicked,this,&SearchDialog::close);

    findSndLayout->addWidget(findBtn);
    findSndLayout->addWidget(replaceBtn);
    findSndLayout->addWidget(replaceAllBtn);
    findSndLayout->addWidget(closeBtn);

    grid->addLayout(findMainLayout,0,0,1,3);
    grid->addLayout(findSndLayout,0,3,1,1);
    this->setLayout(grid);
}

qint64 SearchDialog::findR()
{
    if(_hexEdit != nullptr)
    {
        qint64 from = _hexEdit->cursorPosition() / 2;
        _findBa = getContent(find_ComboBox->currentIndex(), find_ContentBox->currentText());
        qint64 idx = -1;

        if (_findBa.length() > 0)
        {
            if (pre_Check->isChecked())
                idx = _hexEdit->lastIndexOf(_findBa, from);
            else
                idx = _hexEdit->indexOf(_findBa, from);
        }
        return idx;
    }
    return -1; //no hexedit
}

qint64 SearchDialog::findNext()
{
    qint64 from = _hexEdit->cursorPosition() / 2;
    _findBa = getContent(find_ComboBox->currentIndex(), find_ContentBox->currentText());
    qint64 idx = -1;

    if (_findBa.length() > 0)
    {
        idx = _hexEdit->indexOf(_findBa, from);
    }
    return idx;
}

qint64 SearchDialog::findPre()
{
    qint64 from = _hexEdit->cursorPosition() / 2;
    _findBa = getContent(find_ComboBox->currentIndex(), find_ContentBox->currentText());
    qint64 idx = -1;

    if (_findBa.length() > 0)
    {
        idx = _hexEdit->lastIndexOf(_findBa, from);
    }
    return idx;
}

void SearchDialog::replace()
{
    if(_hexEdit != nullptr)
    {
        qint64 idx = findNext();
        if (idx >= 0)
        {
            QByteArray replaceBa = getContent(replace_ComboBox->currentIndex(), replace_ContentBox->currentText());
            replaceOccurrence(idx, replaceBa);
        }
    }
}

void SearchDialog::replaceAll()
{
    if(_hexEdit != nullptr)
    {
        qint64 replaceCounter = 0;
        qint64 idx = 0;
        qint64 goOn = QMessageBox::Yes;

        while ((idx >= 0) && (goOn == QMessageBox::Yes))
        {
            idx = findNext();
            if (idx >= 0)
            {
                QByteArray replaceBa = getContent(replace_ComboBox->currentIndex(), replace_ContentBox->currentText());
                qint64 result = replaceOccurrence(idx, replaceBa);

                if (result == QMessageBox::Yes)
                    replaceCounter += 1;

                if (result == QMessageBox::Cancel)
                    goOn = result;
            }
        }
        if (replaceCounter > 0)
            QMessageBox::information(this, tr("LinuxHex"), QString(tr("替换了 %1 处")).arg(replaceCounter));
    }
}

void SearchDialog::setHexEdit(QHexEdit *hex_edit)
{
    _hexEdit = hex_edit;
}

QByteArray SearchDialog::getContent(int comboIndex, const QString &input)
{
    QByteArray findBa;
    switch (comboIndex)
    {
        case 0:     // hex
            findBa = QByteArray::fromHex(input.toLatin1());
            break;
        case 1:     // text
            findBa = input.toUtf8();
            break;
    }
    return findBa;
}

qint64 SearchDialog::replaceOccurrence(qint64 idx, const QByteArray &replaceBa)
{
    int result = QMessageBox::Yes;
    if (replaceBa.length() >= 0)
    {
        if (tip_Check->isChecked())
        {
            QMessageBox closMessage(QMessageBox::Question, "确认替换?","确认替换?");
            closMessage.addButton(QMessageBox::No);
            closMessage.setButtonText(QMessageBox::No, QString("不替换(&W)"));

            closMessage.addButton(QMessageBox::Yes);
            closMessage.setButtonText(QMessageBox::Yes, QString("替换(&S)"));

            int result = closMessage.exec();
            if (result == QMessageBox::Yes)
            {
                _hexEdit->replace(idx, replaceBa.length(), replaceBa);
                _hexEdit->update();
            }
        }
        else
        {
            _hexEdit->replace(idx, _findBa.length(), replaceBa);
        }
    }
    return result;
}
