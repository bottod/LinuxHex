#include <QMenu>
#include <QFile>

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    isMax = true;
    initTitle();

    //qss
    QFile mTitlebarQss(":/Source/stylesheet/TitleBar.qss");
    mTitlebarQss.open(QFile::ReadOnly);
    this->setStyleSheet(mTitlebarQss.readAll());
    mTitlebarQss.close();

}

TitleBar::~TitleBar()
{

}

void TitleBar::initTitle()
{
    setFixedHeight(40); //max height < 40

    titleLayout = new QHBoxLayout(this);

    //aimed at this
    titleIconLabel = new QLabel(this);
    titleIconLabel->setFixedSize(30,30);
    titleIconLabel->setPixmap(QPixmap(":/Source/image/app.png").scaled(30,30));

    NameLabel = new QLabel(this);
    NameLabel->setFixedHeight(20);
    NameLabel->setText("* - LinuxHex");
    NameLabel->setObjectName("NameLabel");

    setBtn = new QPushButton(this);
    setBtn->setCursor(Qt::PointingHandCursor);
    setBtn->setFixedSize(15,16);
    setBtn->setToolTip("设置");
    setBtn->setObjectName("setBtn");

    lineLabel = new QLabel(this);
    lineLabel->setPixmap(QPixmap(":/Source/image/line.png"));

    minimumBtn = new QPushButton(this);
    minimumBtn->setCursor(Qt::PointingHandCursor);
    minimumBtn->setToolTip("最小化");
    minimumBtn->setFixedSize(14,18);
    minimumBtn->setObjectName("minimumBtn");

    maximumBtn = new QPushButton(this);
    maximumBtn->setCursor(Qt::PointingHandCursor);
    maximumBtn->setFixedSize(14,11);
    maximumBtn->setObjectName("maximumBtn");
    maximumBtn->setToolTip("最大化");

    connect(maximumBtn,&QPushButton::clicked,this,&TitleBar::maxiumBtnClickedFun);

    closeBtn = new QPushButton(this);
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(12,11);
    closeBtn->setToolTip("关闭");
    closeBtn->setObjectName("closeBtn");


    titleLayout->addWidget(titleIconLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(NameLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(setBtn);
    titleLayout->addSpacing(10);
    titleLayout->addWidget(lineLabel);
    titleLayout->addSpacing(10);
    titleLayout->addWidget(minimumBtn);
    titleLayout->addSpacing(10);
    titleLayout->addWidget(maximumBtn);
    titleLayout->addSpacing(10);
    titleLayout->addWidget(closeBtn);

}

void TitleBar::setMaxValue(bool value)
{
    isMax = value;
    if(isMax)
    {
        maximumBtn->setStyleSheet(::cancel_maxBtnStyle);
        maximumBtn->setToolTip("取消最大化");
        isMax = false;
    }
    else
    {
        maximumBtn->setStyleSheet(::set_maxBtnStyle);
        maximumBtn->setToolTip("最大化");
        isMax = true;
    }
}

void TitleBar::setTitle(QString title)
{
    NameLabel->setText(title);
}

void TitleBar::maxiumBtnClickedFun()
{
    if(isMax)
    {
        maximumBtn->setStyleSheet(::cancel_maxBtnStyle);
        maximumBtn->setToolTip("取消最大化");
        isMax = false;
    }
    else
    {
        maximumBtn->setStyleSheet(::set_maxBtnStyle);
        maximumBtn->setToolTip("最大化");
        isMax = true;
    }
}
