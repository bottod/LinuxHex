#include "MiddleWidget.h"

MiddleWidget::MiddleWidget(QWidget *parent)
    : QWidget (parent)
{
    init();
}


void MiddleWidget::init()
{
    m_Tab = new QTabWidget(this);
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(m_Tab);

//    use qss to hide a blank tab
//    m_Tab->addTab(new QWidget(this), "*");
//    m_Tab->setTabEnabled(0,false);
//    m_Tab->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");

    m_Tab->setTabsClosable(true);//close btn; use default skin;never make our project more difficult

}
