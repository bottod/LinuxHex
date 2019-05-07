#include <QMenu>
#include <QFile>

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    initTitle();

    this->setStyleSheet("QFrame{background:rgb(102,183,255);\
                        border-top-left-radius:15px;\
                        border-top-right-radius:15px;}");

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
    NameLabel->setText("* - Debug Tool");
    NameLabel->setStyleSheet("QLabel{color:rgb(255,255,255);\
                             font:bold;}");

    setBtn = new QPushButton(this);
    setBtn->setCursor(Qt::PointingHandCursor);
    setBtn->setFixedSize(15,16);
    setBtn->setToolTip("设置");
    setBtn->setStyleSheet("QPushButton{background:transparent;\
                    border-image:url(:/Source/image/set.png);}\
                    QPushButton:hover{border-image:url(:/Source/image/set_hover.png);}");

    lineLabel = new QLabel(this);
    lineLabel->setPixmap(QPixmap(":/Source/image/line.png"));

    minimumBtn = new QPushButton(this);
    minimumBtn->setCursor(Qt::PointingHandCursor);
    minimumBtn->setToolTip("最小化");
    minimumBtn->setFixedSize(14,18);
    minimumBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/Source/image/minimum.png);}\
                              QPushButton:hover{border-image:url(:/Source/image/minimum_hover.png);}");

    maximumBtn = new QPushButton(this);
    maximumBtn->setCursor(Qt::PointingHandCursor);
    maximumBtn->setFixedSize(14,11);
    maximumBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/Source/image/maximum.png);}\
                              QPushButton:hover{border-image:url(:/Source/image/maximum_hover.png);}");
    maximumBtn->setToolTip("最大化");

    closeBtn = new QPushButton(this);
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(12,11);
    closeBtn->setToolTip("关闭");
    closeBtn->setStyleSheet("QPushButton{background:transparent;\
                            border-image:url(:/Source/image/close.png);}\
                            QPushButton:hover{border-image:url(:/Source/image/close_hover.png);}");


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

void TitleBar::setTitle(QString title)
{
    NameLabel->setText(title);
}
