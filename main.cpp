#include "widget.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator Translator;
    if(QSysInfo::kernelType() == "linux")
        Translator.load("/usr/bin/cipher/i18n/zh-cn.qm");
    else
        Translator.load("zh-cn.qm");
	a.installTranslator(&Translator);

    Widget w;
    w.show();

    return a.exec();
}
