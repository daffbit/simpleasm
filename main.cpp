#include "startpage.h"
#include <QApplication>
#include "WorkingWindow.h"
#include <QDesktopWidget>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /* creating welcome dialog */
    startPage* welcome = new startPage;
    /* moving welcome dialog to center */
    welcome->move(QApplication::desktop()->screen()->rect().center()
                 - welcome->rect().center());

    /* display welcome dialog */
    welcome->show();


    return a.exec();
}
