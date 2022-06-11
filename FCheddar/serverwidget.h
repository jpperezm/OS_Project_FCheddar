#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>

#include "database.h"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr, Database* = nullptr);
    ~ServerWidget();


private slots:
    void on_start_clicked();
    void on_quit_clicked();
    void processPendingRequest();
    void readyRead();
    void disconnected();

private:
    void sendText(QString msg);
    void sendImage(QByteArray img);

    QByteArray getImageData(const QPixmap &pixmap);

    Ui::ServerWidget *ui;
    QTcpServer *mServerSocket;
    QTcpSocket *mClientSocket;
    QString ProjectRequest;
    Database* mDatabase;
    int msgCounter;


    QImage *imageObject;
    QPixmap image;
    qint64 totalBytes;
};

#endif // SERVERWIDGET_H
