#ifndef INFOFRAME_H
#define INFOFRAME_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class InfoFrame : public QFrame
{
    Q_OBJECT
public:
    explicit InfoFrame(QWidget *parent = nullptr);

public:
    QPushButton *m_CloseBtn;

    void setContent(QString text);

private:
    void initFrame();

    QLabel *m_titleLabel;
    QLabel *m_infoLabel;
    QVBoxLayout *m_vMainLayout;

};

#endif // INFOFRAME_H
