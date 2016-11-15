#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QSql>
#include <QSqlDatabase>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qint32 ID, QObject *parent = 0);

    void    run();



signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void    readyRead();
    void    disconnected();

private:
    QTcpSocket *socket;
    qint32 socketDescriptor;
    uint32_t m_MyChipID = 1;
    QSqlDatabase db;
    QString sql_sorgu;
};

#endif // MYTHREAD_H
