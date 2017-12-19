#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QMessageBox>
#include <QDialog>
#include <QGridLayout>
#include <QPixmap>
#include <QTextBrowser>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "caesarcipher.h"
#include "playfaircipher.h"
#include "hillcipher.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    void showMessage(QString title,QString content);
    // 用于弹窗提示操作错误

    CaesarCipher c;
    PlayfairCipher p;
    HillCipher h;

private slots:

    void copyText(); // 复制文本，原文或者密文
    void loadFile(); // 加载文件内容
    void encrypt(); // 加密
    void decrypt(); // 解密
    void about(); // 关于本程序
};

#endif // WIDGET_H
