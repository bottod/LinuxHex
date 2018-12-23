#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DataFrame : public QFrame
{
    Q_OBJECT
public:
    explicit DataFrame(QWidget *parent = nullptr);

public:
    QPushButton *m_CloseBtn;

    void setContent(QString text);

private:
    void initFrame();

    QLabel *m_titleLabel;
    QLabel *m_infoLabel;
    QVBoxLayout *m_vMainLayout;

};

#endif // DATAFRAME_H
