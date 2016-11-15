#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtSql>
#include <QTcpSocket>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void  setRandom();
    void  sendDatabase();
    void  receiveFromDatabase();
    void  receiveFromServer();
private:
    QLineEdit *sayigirisi[10];
    QPushButton *set_butonu;
    QPushButton *tcp_butonu;
    QPushButton *veritabani_butonu;
    QPushButton *cik_butonu;
    long int   sayi[10];
    QTableWidget *table;
    QTcpSocket *server_soket;
    QTextBrowser *x;

};

#endif // MAINWINDOW_H
