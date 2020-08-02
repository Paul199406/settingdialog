#include "settingdialog.h"
#include <QApplication>
#include <test.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test t;
    t.show();

    return a.exec();
}
