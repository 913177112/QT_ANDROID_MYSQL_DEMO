#include "mainwindow.h"
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   server_soket = new QTcpSocket();
   server_soket->connectToHost("139.59.138.76",8888);
   server_soket->waitForConnected(30000);
   bool m_connected_state = ( server_soket->state() == QTcpSocket::ConnectedState);

   if(m_connected_state) {
         qDebug() << "TCP/IP Basarili.";
   }

   else {
         qDebug() << "TCP/IP Basarisiz.";
        }

    tcp_butonu = new QPushButton(this);
    set_butonu = new QPushButton(this);
    cik_butonu = new QPushButton(this);
    veritabani_butonu = new QPushButton(this);
    tcp_butonu->setText("DATABASE");
    set_butonu->setText("SET");
    veritabani_butonu->setText("Veritabanindan cek");
    cik_butonu->setText("ÇIKIŞ");
    for (int i=0;i < 10; i++) {
        sayigirisi[i] = new QLineEdit(this);
    }

    QWidget *widget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(widget);
    for(int i = 0; i< 10; i++) {
        layout->addWidget(sayigirisi[i],i,0);
        sayigirisi[i]->setText("Sayi Giriniz...");
    }

    QGridLayout *layout2 = new QGridLayout(widget);
    layout2->addWidget(set_butonu,11,0);
    layout2->addWidget(tcp_butonu,11,1);
    layout2->addWidget(cik_butonu,11,2);
    layout2->addWidget(cik_butonu,11,2);

    setCentralWidget(widget);

    layout->addLayout(layout2,12,0);
    layout->addWidget(veritabani_butonu,13,0,0);

    connect(set_butonu,SIGNAL(clicked(bool)),this,SLOT(setRandom()));
    connect(tcp_butonu,SIGNAL(clicked(bool)),this,SLOT(sendDatabase()));
    connect(cik_butonu,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(veritabani_butonu,SIGNAL(clicked(bool)),this,SLOT(receiveFromDatabase()));
    connect(server_soket,SIGNAL(readyRead()),this,SLOT(receiveFromServer()));
}

void MainWindow::setRandom() {
    for(int i=0; i<10; i++) {
        sayi[i] = qrand()/100;
        sayigirisi[i]->setText(QString::number(sayi[i]));
        qDebug() << sayi[i];
    }
}

void MainWindow::receiveFromServer() {
    QByteArray outByteArray = server_soket->readAll();
    qDebug()  << outByteArray;
    int sorgu[100];
    QString deneme = outByteArray;

    QStringList myStringList = deneme.split("/");


             x = new QTextBrowser();

             QWidget *widget2 = new QWidget();
             QHBoxLayout *layoutx = new QHBoxLayout(widget2);
             layoutx->addWidget( x);
             setLayout(layoutx);
             widget2->show();

             for(int index =0;index < myStringList.length();index++)

             {
                 sorgu[index] = myStringList.at(index).toInt();
                 std::cout<< sorgu[index]<<std::endl;
                 x->append( myStringList[index]);
             }

}

void MainWindow::receiveFromDatabase() {
    server_soket->write("require");
}

void MainWindow::sendDatabase() {
    long int max_sayi;
    max_sayi = sayi[0];
    for(int i = 0 ; i<10; i++) {
     if(sayi[i]>max_sayi)
         max_sayi = sayi[i];

}

QString veri= QString::number(max_sayi);

    bool m_connected_state = ( server_soket->state() == QTcpSocket::ConnectedState);

    if(m_connected_state) {
        server_soket->write(veri.toUtf8().data());
        server_soket->flush();
        QMessageBox msgbox;
        QString x = "En büyük sayi = " + QString::number(max_sayi);
        msgbox.setText(x);
        msgbox.setWindowTitle("GONDERILDI");
        msgbox.exec();
    }
       else {

        QMessageBox msgbox;
        QString x = "En büyük sayi = " + QString::number(max_sayi);
        msgbox.setText(x);
        msgbox.setWindowTitle("GONDERILMEDI");
        msgbox.exec();

    }

}

MainWindow::~MainWindow()
{

}



