#ifndef MIDDLEWIDGET_H
#define MIDDLEWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>

class MiddleWidget : public QWidget
{
public:
    MiddleWidget(QWidget *parent = nullptr);

public:
    QTabWidget *m_Tab;

private:
    void init();
};

#endif // MIDDLEWIDGET_H
