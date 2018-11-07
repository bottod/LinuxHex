#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>


const QString cancel_maxBtnStyle = "QPushButton{border-image:url(:/Source/image/maximum_cancel.png);} \
                                    QPushButton:hover{border-image:url(:/Source/image/maximum_cancel_hover.png);}";

const QString set_maxBtnStyle = "QPushButton{border-image:url(:/Source/image/maximum.png);} \
                                 QPushButton:hover{border-image:url(:/Source/image/maximum_hover.png);}";

#pragma pack(push)
#pragma pack(1)

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
     void setMaxValue(bool value);
     void setTitle(QString title);

private:
    void initTitle();

    QHBoxLayout *titleLayout;

    bool isMax = true;
};

#pragma pack(pop)


#endif // TITLEBAR_H

