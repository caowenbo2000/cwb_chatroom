#include "serverwidget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //查看自己的ip地址
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
    QHostAddress address=info.addresses().first(); //info.addresses() 返回一个地址表，我们取第一个
    QString str1=address.toString();
    qDebug()<<str1;
    //结束


    ui->setupUi(this);
    tcpserver=new QTcpServer(this);
    tcpsocket=NULL;
    tcpserver->listen(QHostAddress::Any,quint16(8888));
    connect(tcpserver,&QTcpServer::newConnection,

            [=]()
    {
        tcpsocket=tcpserver->nextPendingConnection();
        QString ip = tcpsocket->peerAddress().toString();
        quint16 port = tcpsocket->peerPort();
        QString temp=QString("[ip地址：%1:%2]：已连接服务器").arg(ip).arg(port);
        ui->textedit_in->append(temp);
        connect(tcpsocket,&QTcpSocket::readyRead,
        [=]()
        {
            QByteArray array=tcpsocket->readAll();
            ui->textedit_in->append(array);
        }
                );
    }
    );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushbutton_send_clicked()
{
    if(NULL==tcpsocket)
    {
        ui->textedit_in->append("未连接客户端！");
        return;
    }
    QString str= ui->textedit_out->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void Widget::on_pushbutton_quit_clicked()
{
    if(tcpsocket==NULL)
    {
        return ;
    }
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    tcpsocket=NULL;
    ui->textedit_in->append("断开连接");
}
