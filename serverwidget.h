#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QString>
#include <QDebug>
#include <QHostAddress>
#include <QHostInfo>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushbutton_send_clicked();

    void on_pushbutton_quit_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *tcpserver;//监听套接字
    QTcpSocket *tcpsocket;//通信套节字
};

#endif // WIDGET_H
