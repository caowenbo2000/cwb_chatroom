#include "clientwidget.h"
#include "ui_clientwidget.h"

clientwidget::clientwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwidget)
{
    ui->setupUi(this);
    tcpsocket = NULL;
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket,&QTcpSocket::connected,
    [=]()
    {
        ui->textedit_in->append("成功连接服务器");
    }
    );
    connect(tcpsocket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array=tcpsocket->readAll();
        ui->textedit_in->append(array);
    }
            );
}

clientwidget::~clientwidget()
{
    delete ui;
}

void clientwidget::on_pushbutton_connect_clicked()
{
    QString ip =ui->lineEdit_ip->text();
    quint16 port =ui->lineEdit_port->text().toUShort();
    qDebug()<<ip<<" " <<port;
    tcpsocket ->connectToHost(QHostAddress(ip),port);
}



void clientwidget::on_pushbutton_send_clicked()
{
    QString str=ui->textEdit_out->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void clientwidget::on_pushbutton_close_clicked()
{
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    ui->textedit_in->append("已断开连接");
}
