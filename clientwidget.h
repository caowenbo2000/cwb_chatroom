#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QHostAddress>

namespace Ui {
class clientwidget;
}

class clientwidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientwidget(QWidget *parent = nullptr);
    ~clientwidget();

private slots:
    void on_pushbutton_connect_clicked();

    void on_pushButton_2_clicked();

    void on_pushbutton_send_clicked();

    void on_pushbutton_close_clicked();

private:
    Ui::clientwidget *ui;
    QTcpSocket *tcpsocket;
};

#endif // CLIENTWIDGET_H
