#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    QLabel *titleIconLabel;
    QLabel *NameLabel;

    QPushButton *setBtn;
    QLabel *lineLabel;
    QPushButton *minimumBtn;
    QPushButton *maximumBtn;
    QPushButton *closeBtn;


//interface
public:
     void setTitle(QString title);

private:
    void initTitle();

    QHBoxLayout *titleLayout;
};


#endif // TITLEBAR_H

