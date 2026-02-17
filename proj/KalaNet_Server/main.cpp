#include <QCoreApplication>
#include "Kalanetserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    KalaNetServer server;
    server.startServer();

    return a.exec();
}
