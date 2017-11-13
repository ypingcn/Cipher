#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnCopyPlainText,SIGNAL(clicked()),this,SLOT(copyText()));
    connect(ui->btnCopyCipherText,SIGNAL(clicked()),this,SLOT(copyText()));

    connect(ui->btnEncrypt,SIGNAL(clicked()),this,SLOT(encrypt()));
    connect(ui->btnDecrypt,SIGNAL(clicked()),this,SLOT(decrypt()));

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

void Widget::encrypt()
{
    if( !ui->rbtnCaesar->isChecked() && !ui->rbtnHill->isChecked() && !ui->rbtnPlayfair->isChecked())
        showMessage("type error","type error");

    ui->edtCipherText->clear();
    QString str = ui->edtPlainText->toPlainText();
    QStringList sections = str.split('\n');

    if(ui->rbtnCaesar->isChecked())
    {
        for(auto i : sections)
        {
            std::string result;
            c.encrypt(QString(i).toStdString(),result);
            ui->edtCipherText->append(QString::fromStdString(result));
        }
    }
    else if(ui->rbtnPlayfair->isChecked())
    {
        p.setWord(ui->edtPlayfair->text().toStdString());

        for(auto i : sections)
        {
            std::string result;
            p.encrypt(QString(i).toStdString(),result);
            ui->edtCipherText->append((QString::fromStdString(result)));
        }
    }
    else if(ui->rbtnHill->isChecked())
    {
        int k[HillCipher::N][HillCipher::N],cnt = 0;
        bool ok;

        QString key = ui->edtHill->toPlainText();
        QStringList keySections = key.split('\n');

        for(QString i : keySections)
        {
            QString line = i;
            QStringList lineKeySections = line.split(' ');
            for(QString j : lineKeySections)
            {
                if(cnt >= HillCipher::N*HillCipher::N)
                    goto SETKEY;
                int row = cnt / HillCipher::N,column = cnt % HillCipher::N;
                k[row][column] = j.toInt(&ok,10);
                if(ok)
                    cnt++;
            }
        }

SETKEY: if( h.setKey(k) )
        {
            for(auto i : sections)
            {
                std::string result;
                h.encrypt(QString(i).toStdString(),result);
                ui->edtCipherText->append((QString::fromStdString(result)));
            }
        }
        else
            showMessage("Invaild KEY!","Invaild KEY!");
    }
}

void Widget::decrypt()
{
    if( !ui->rbtnCaesar->isChecked() && !ui->rbtnHill->isChecked() && !ui->rbtnPlayfair->isChecked())
        showMessage("type error","type error");

    ui->edtPlainText->clear();
    QString str = ui->edtCipherText->toPlainText();
    QStringList sections = str.split('\n');

    if(ui->rbtnCaesar->isChecked())
    {
        for(auto i : sections)
        {
            std::string result;
            c.decrypt(QString(i).toStdString(),result);
            ui->edtPlainText->append(QString::fromStdString(result));
        }
    }
    else if(ui->rbtnPlayfair->isChecked())
    {
        for(auto i : sections)
        {
            std::string result;
            p.decrypt(QString(i).toStdString(),result);
            ui->edtPlainText->append(QString::fromStdString(result));
        }
    }
    else if(ui->rbtnHill->isChecked())
    {
        int k[HillCipher::N][HillCipher::N],cnt = 0;
        bool ok;

        QString key = ui->edtHill->toPlainText();
        QStringList keySections = key.split('\n');

        for(QString i : keySections)
        {
            QString line = i;
            QStringList lineKeySections = line.split(' ');
            for(QString j : lineKeySections)
            {
                if(cnt >= HillCipher::N*HillCipher::N)
                    goto SETKEY;
                int row = cnt / HillCipher::N,column = cnt % HillCipher::N;
                k[row][column] = j.toInt(&ok,10);
                if(ok)
                    cnt++;
            }
        }

SETKEY: if( h.setKey(k) )
        {
            for(auto i : sections)
            {
                std::string result;
                h.decrypt(QString(i).toStdString(),result);
                ui->edtPlainText->append((QString::fromStdString(result)));
            }
        }
        else
            showMessage("Invaild KEY!","Invaild KEY!");
    }
}

void Widget::showMessage(QString title, QString content)
{
    QMessageBox::information(this,title,content, QMessageBox::Ok);
}
