#include "companiescrudrepositoryapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CompaniesCRUDRepositoryApp w;
    w.show();
    return a.exec();
}
