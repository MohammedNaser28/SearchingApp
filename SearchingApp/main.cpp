#include "stdafx.h"
#include "searchingapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/search.ico"));
    SearchingApp w;
    w.show();
    return a.exec();
}
