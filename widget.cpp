#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnCopyPlainText,SIGNAL(clicked()),this,SLOT(copyText()));
    connect(ui->btnCopyCipherText,SIGNAL(clicked()),this,SLOT(copyText()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::copyText()
{
    QClipboard * clipborad = QApplication::clipboard();
    if(QObject::sender() == ui->btnCopyPlainText)
    {
        clipborad->setText(ui->edtPlainText->toPlainText());
    }
    else if(QObject::sender() == ui->btnCopyCipherText)
    {
        clipborad->setText(ui->edtCipherText->toPlainText());
    }
}
