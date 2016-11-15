#include "myserver.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{

}

void MyServer::startServer()
{
    int port = 8888;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }

}

void MyServer::incomingConnection(qint32 socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}






