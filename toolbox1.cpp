#pragma execution_character_set("utf-8")

#include "toolbox1.h"
#include "login.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHostAddress>
toolbox1::toolbox1(QWidget *parent):
    QToolBox(parent)
{
    setWindowIcon(QPixmap(":/images/3.png"));   // ����������ͼ��
    init_username();
    init_toolBtn();

    login log_in;
    // ����ģʽ�Ի��򣬳�������
    log_in.exec();

    if(log_in.isLogin){
        if((log_in.userid <0) || (log_in.userid > 255)){
            QMessageBox::information(this, tr("����"), tr("��Ч�û�ID"));
            exit(0);
        }
        setWindowTitle(username[log_in.userid]);

        userid = log_in.userid;
        pwd = log_in.pwd;
        hostip = log_in.hostip;
        hostport = log_in.hostport;

        client = new QTcpSocket(this);
        connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this,
                SLOT(sock_err(QAbstractSocket::SocketError)));
        connect(client, SIGNAL(readyRead()), this, SLOT(read_msg()));
        connect(client, SIGNAL(connected()), this, SLOT(sock_connect()));

        QHostAddress host_addr(hostip);
        client->connectToHost(host_addr, hostport);
    }else{
        exit(0);
    }
}

bool toolbox1::eventFilter(QObject *watched, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        int i = watched->objectName().toInt();
        child[i]->hide();
        // ��toolbtn�¶�Ӧ��child��ʾ����Ļ
        child[i]->showNormal();
    }
    // �����źŽ����������Ĭ�ϴ���
    return QToolBox::eventFilter(watched, event);
}

void toolbox1::init_toolBtn(){
    QString imagename;
    for(int i=0;i<CLIENTCOUNT;++i){
        toolBtn[i] = new QToolButton();
        toolBtn[i]->setObjectName(QString::number(i));// ����ObjectName����
        toolBtn[i]->installEventFilter(this);   //toolbtn�ĵ���¼���toolbox1������
        toolBtn[i]->setText(username[i]); //����toolbtn����
        imagename.sprintf(":/images/%d.png", i);
        toolBtn[i]->setIcon(QPixmap(imagename));    // ����toolbtnͼ��
        toolBtn[i]->setIconSize(QPixmap(imagename).size());
        toolBtn[i]->setAutoRaise(true); // �����Զ����������
        toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//����toolBtn������ͼ���Ա�
        toolBtn[i]->setToolTip(tr("δ֪"));//����toolBtn �����ʾΪ��δ֪��
        child[i] = new Widget(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
    }

    QGroupBox *groupBox[8];
    QVBoxLayout *layout[8];
    static int index = 0;
    for(int i=0;i<8;++i){
        groupBox[i] = new QGroupBox();
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);       // ���ò����и��������ʾ���
        layout[i]->setAlignment(Qt::AlignLeft);  // ���ò����и������λ��
        for(int j=0;j<32;j++){
            layout[i]->addWidget(toolBtn[index++]);  // ����һ��layout�м���32��toolbtn
        }
        layout[i]->addStretch();    // ����һ��ռλ��
    }

    addItem((QWidget *)groupBox[0], tr("����"));
    addItem((QWidget *)groupBox[1], tr("����"));
    addItem((QWidget *)groupBox[2], tr("ͬѧ"));
    addItem((QWidget *)groupBox[3], tr("ͬ��"));
    addItem((QWidget *)groupBox[4], tr("����"));
    addItem((QWidget *)groupBox[5], tr("¿��"));
    addItem((QWidget *)groupBox[6], tr("����"));
    addItem((QWidget *)groupBox[7], tr("İ����"));

}

void toolbox1::init_username(){
    for(int i=0;i<CLIENTCOUNT;++i){
        username[i] = tr("�û�") + QString::number(i);
    }
}

void toolbox1::sock_err(QAbstractSocket::SocketError sock_err){
    switch (sock_err) {
    // �����Զ�̷����������ر�socket��ֱ��break
    case QAbstractSocket::RemoteHostClosedError:
        break;
    default:
        QMessageBox::information(this, tr("����"), client->errorString());
    }
}

// ���͵�¼��Ϣ
void toolbox1::login_msg(){
    const char *pw = pwd.toStdString().data();
    if(client->isOpen()){       // �ж�socket�Ƿ��Ѿ����ӵ�Զ��server
        if(client->state() == QAbstractSocket::ConnectedState){
            struct msg_t msg;
            memset(&msg, 0, sizeof(msg));
            msg.head[0] = 1;    // ������ϢΪ��¼��Ϣ
            msg.head[1] = userid;       // ���õ�¼�û�ID
            msg.head[2] = 0;    // ����
            msg.head[3] = 0;    // ����

            strncpy(msg.body, pw, strlen(pw));      // ��¼��Ϣ����
            client->write((const char *)&msg, strlen(msg.body)+sizeof(msg.head));
        }
    }
}

void toolbox1::read_msg(){

}

// socket���ӵ�server���Ժ���õĲۺ���
void toolbox1::sock_connect(){
    // ��server�˷��͵�¼��Ϣ
    login_msg();
}
