#include "widget.h"
#include <QApplication>

/*
 * 用于转换ssf，并且把皮肤放置在$HOME/.config/fcitx/skin
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;    
    w.show();

    return a.exec();
}
