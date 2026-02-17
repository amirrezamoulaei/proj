#ifndef KALANETSERVER_H
#define KALANETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class KalaNetServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit KalaNetServer(QObject *parent = nullptr);
    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor)override;
private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QList<QTcpSocket*> clients;

};

#endif // KALANETSERVER_H
