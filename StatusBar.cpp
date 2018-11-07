#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar (parent)
{
    init();

    //qss
    QFile mStatusbarQss(":/Source/stylesheet/StatusBar.qss");
    mStatusbarQss.open(QFile::ReadOnly);
    this->setStyleSheet(mStatusbarQss.readAll());
    mStatusbarQss.close();
}

void StatusBar::init()
{
    // Address Label
    m_AddressName = new QLabel(this);
    m_AddressName->setText(tr("地址:"));
    this->addPermanentWidget(m_AddressName);
    m_Address = new QLabel();
    m_Address->setFrameShape(QFrame::Panel);
    m_Address->setMinimumWidth(70);
    this->addPermanentWidget(m_Address);


    // Size Label
    m_SizeName = new QLabel();
    m_SizeName->setText(tr("大小:"));
    this->addPermanentWidget(m_SizeName);
    m_Size = new QLabel();
    m_Size->setFrameShape(QFrame::Panel);
    m_Size->setMinimumWidth(70);
    this->addPermanentWidget(m_Size);


    // Overwrite Mode Label
    m_OverwriteModeName = new QLabel();
    m_OverwriteModeName->setText(tr("模式:"));
    this->addPermanentWidget(m_OverwriteModeName);
    m_OverwriteMode = new QLabel();
    m_OverwriteMode->setFrameShape(QFrame::Panel);
    m_OverwriteMode->setMinimumWidth(70);
    this->addPermanentWidget(m_OverwriteMode);


    this->showMessage(tr("已就绪!"), 2000);
}

void StatusBar::setSize(qint64 size)
{
    m_Size->setText(QString("%1").arg(size));
}

void StatusBar::setAddress(qint64 address)
{
    m_Address->setText(QString("%1").arg(address));
}

void StatusBar::setOverwriteMode(QString modeName)
{
    m_OverwriteMode->setText(modeName);
}
