#include "CheckFileThread.h"
#include <QFileInfo>

CheckFileThread::CheckFileThread(QString filename)
    :file_name(filename)
{

}

void CheckFileThread::run()
{
    while(true)
    {
        msleep(1);
        if(isFileExist(file_name))
        {
            emit fileExist(file_name);
            break;
        }
    }
}

bool CheckFileThread::isFileExist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}
