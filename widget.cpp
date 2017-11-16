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

    connect(ui->btnAbout,SIGNAL(clicked()),this,SLOT(about()));

    connect(ui->btnLoadFile,SIGNAL(clicked()),this,SLOT(loadFile()));
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

void Widget::loadFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choose File"), ".", tr("All File(*.*)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly |QFile::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:%1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->edtPlainText->clear();
        ui->edtPlainText->setPlainText(in.readAll());
        QApplication::restoreOverrideCursor();
    }
}
void Widget::about()
{
    QDialog * about = new QDialog(this);
    QGridLayout * aboutLayout = new QGridLayout(about);
    QPixmap icon(":cipher.png");
    QLabel * labIco = new QLabel();
    labIco->setPixmap(icon);

    about->setWindowTitle("About");
    about->resize(600,300);

    QTextBrowser * content = new QTextBrowser();
    content->setOpenExternalLinks(true);

    content->append(tr("A Qt-based program for Caesar,Playfair,Hill encryption and decryption."));
    content->append(tr("<a href=\"https://github.com/ypingcn/Cipher\"> %1 </a>").arg(tr("click to know more.")));
    content->append(tr("\nThe program is licensed under version 3 of the GNU General Public License."));
    content->append(tr("Copyright 2017 ypingcn"));

    aboutLayout->addWidget(labIco,0,0,1,1);
    aboutLayout->addWidget(content,0,1,1,1);

    about->exec();

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
