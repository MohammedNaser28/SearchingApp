#include "stdafx.h"
#include "searchingapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/re.ico"));
    SearchingApp w;
    w.show();
    return a.exec();
}
