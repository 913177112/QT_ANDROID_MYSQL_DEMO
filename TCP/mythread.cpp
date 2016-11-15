#include "mythread.h"
#include <QTimer>
#include <QSqlDatabase>

#include <QSqlQuery>
MyThread::MyThread(qint32 ID, QObject *parent) :
    QThread(parent)
{

this->socketDescriptor = ID;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("97309730a-A");

    if(!db.open())
        qDebug() << "hata" ;
    else
        qDebug() << "basari";
}


void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);

    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));



    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";


    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies 
    exec();
}



void MyThread::readyRead()          {

   QByteArray incoming_data = socket->readAll();

   QString veri(incoming_data);
   QString istek = "require";
   int x = QString::compare(veri, istek, Qt::CaseInsensitive);  // if strings are equal x should return 0

   if(x==0) {
       qDebug() << "MYSQLDAN ISTENIYOR";


       QSqlQuery query(db);
       query.prepare(QString("select * from equipment order by equip_id "));

       if(query.exec()) {
           qDebug() << "cekme basari" ;
           while (query.next()) {
                   QString k = query.value(1).toString();
                   qDebug() << "found" << k;
                   sql_sorgu += "/";
                   sql_sorgu += k;

               }
           socket->write(sql_sorgu.toUtf8().data());
           sql_sorgu="";
       }

       else {
           qDebug()<< "cekme hata" ;
       }
   }


   else{
       qDebug() << incoming_data;

       QString x = incoming_data;
       qDebug() << "gonderilen data " << x;
       QSqlQuery query(db);
       query.prepare("INSERT INTO equipment (type) VALUES ( :sayi)");
      // INSERT INTO equipment (type) VALUES ('22');
       query.bindValue(":sayi",x);
       if(query.exec()) {
           qDebug() << "basari" ;
       }

       else {
           qDebug()<< "hata" ;
       }
   }






}



void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}


