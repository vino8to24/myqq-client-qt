#ifndef TOOLBOX1_H
#define TOOLBOX1_H
#include <QToolBox>
#include <QToolButton>
#include <QEvent>

#include <QTcpSocket>
#include <QAbstractSocket>

#include "widget.h"

#define CLIENTCOUNT 256     // ���ͻ�������
#define MSGBODYSIZE 1024

struct msg_t{
    unsigned char head[4];
    char body[MSGBODYSIZE];
};

class toolbox1 : public QToolBox
{
    Q_OBJECT
public:
    explicit toolbox1(QWidget *parent = 0);
    //virtual ~toolbox1(){}
signals:

public slots:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    // socket�����ʱ�򴥷���slot
    void sock_err(QAbstractSocket::SocketError sock_err);
    // socket������Ϣ
    void read_msg();
    // socket�ɹ����ӵ������
    void sock_connect();
private:
    QString username[CLIENTCOUNT];
    QToolButton *toolBtn[CLIENTCOUNT];  // ����256��button
    Widget *child[CLIENTCOUNT];         // Ϊÿ��button����һ��widget������256��widget
    void init_toolBtn();
    void init_username();

    QTcpSocket *client;

    int userid;
    QString pwd;
    QString hostip;
    int hostport;

    void login_msg();

};

#endif // TOOLBOX1_H
