#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QLabel>
#include <QFile>

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

private:
    QLabel *m_Address, *m_AddressName;
    QLabel *m_OverwriteMode, *m_OverwriteModeName;
    QLabel *m_Size, *m_SizeName;

private:
    void init();

public slots:
    void setSize(qint64 size);
    void setAddress(qint64 address);

public:
    void setOverwriteMode(QString modeName);
};

#endif // STATUSBAR_H
