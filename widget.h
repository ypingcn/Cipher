#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QClipboard>
#include <QMessageBox>
#include <QDialog>
#include <QGridLayout>
#include <QPixmap>
#include <QTextBrowser>
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

    CaesarCipher c;
    PlayfairCipher p;
    HillCipher h;

private slots:

    void copyText();
    void encrypt();
    void decrypt();
    void about();
};

#endif // WIDGET_H
