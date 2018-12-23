#include "DataFrame.h"

DataFrame::DataFrame(QWidget *parent) : QFrame(parent)
{
    setFixedWidth(200);
    initFrame();
    setAutoFillBackground(true);
}

void DataFrame::initFrame()
{
    QFrame *top_frame = new QFrame(this);
    top_frame->setStyleSheet("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgb(140, 140, 140),stop:1 rgb(204, 204, 204))");

    QHBoxLayout *titleHLayout = new QHBoxLayout(top_frame);
    m_CloseBtn = new QPushButton(top_frame);
    m_CloseBtn->setFixedSize(15,15);
    m_CloseBtn->setToolTip("关闭");
    m_CloseBtn->setCursor(Qt::PointingHandCursor);
    m_CloseBtn->setStyleSheet("QPushButton{background:transparent;\
                              border-image:url(:/Source/image/child_close.png);}\
                              QPushButton:hover{border-image:url(:/Source/image/child_close_hover.png);}");

    m_titleLabel = new QLabel("数据注释器",top_frame);
    m_titleLabel->setStyleSheet("background-color:transparent");
    titleHLayout->addWidget(m_titleLabel);
    titleHLayout->addStretch();
    titleHLayout->addWidget(m_CloseBtn);
    titleHLayout->addSpacing(10);

    m_infoLabel = new QLabel(this);
    m_infoLabel->setStyleSheet("background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 rgb(204, 204, 204),stop:1 rgb(140, 140, 140))");
    m_infoLabel->setText(
R"(名称:
大小:
路径:
创建时间:
最后读时间:
最后写时间:
是否为符号链接:
是否可读:
是否可写:
是否可执行:
拥有者:
用户组:
)");


    m_vMainLayout = new QVBoxLayout(this);
    m_vMainLayout->setSpacing(0);
    m_vMainLayout->setMargin(0);
    m_vMainLayout->addWidget(top_frame);
    m_vMainLayout->addWidget(m_infoLabel);
    m_vMainLayout->addStretch();
}

void DataFrame::setContent(QString text)
{
    m_infoLabel->setText(text);
}

