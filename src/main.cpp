#include <QApplication>
#include "windows.hpp"

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    windows *windows=new windows(argv[1]);
    windows->show();

    return a.exec();
}
