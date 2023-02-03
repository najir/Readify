#include "bookjournal.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bookjournal w;
    w.show();
    return a.exec();
}
