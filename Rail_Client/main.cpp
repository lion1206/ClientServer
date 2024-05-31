#include <QApplication>
#include "authdialog.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthDialog w;
    w.show();
    Client::instance(); // Создаем экземпляр Client с использованием статического метода
    return a.exec();
}
