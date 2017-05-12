#include "toolbox1.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    toolbox1 t;
    t.resize(300, 600);
    t.show();

    return a.exec();
}
