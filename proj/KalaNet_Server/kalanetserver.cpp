#include "kalanetserver.h"

KalaNetServer::KalaNetServer(QObject *parent):QTcpServer(parent) {}


void KalaNetServer::startServer(){
    if(this->listen(QHostAddress::Any, 1234)){
        qDebug() << "Server started on port 1234...";
    }else{
        qDebug() << "Could not start server!";
    }
}

void KalaNetServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &KalaNetServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &KalaNetServer::onDisconnected);

    clients << socket;
    qDebug() << "Client connected:" << socketDescriptor;
}

void KalaNetServer::onReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    qDebug() << "Data received:" << data;

    for (QTcpSocket* client : clients) {
        client->write(data);
    }
}

void KalaNetServer::onDisconnected() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    clients.removeOne(socket);
    socket->deleteLater();
    qDebug() << "Client disconnected.";
}
