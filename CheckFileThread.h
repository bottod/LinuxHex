#ifndef CHECKFILETHREAD_H
#define CHECKFILETHREAD_H

#include <QObject>
#include <QThread>


class MainWidget;

class CheckFileThread : public QThread
{
    Q_OBJECT
public:
    CheckFileThread(QString filename);

protected:
    void run() override;

signals:
    void fileExist(QString filename);

private:
    QString file_name = "";

    bool isFileExist(QString fullFileName);
};

#endif // CHECKFILETHREAD_H
