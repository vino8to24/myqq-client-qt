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
    setWindowIcon(QPixmap(":/images/3.png"));   // 设置主窗口图标
    init_username();
    init_toolBtn();

    login log_in;
    // 弹出模式对话框，程序阻塞
    log_in.exec();

    if(log_in.isLogin){
        if((log_in.userid <0) || (log_in.userid > 255)){
            QMessageBox::information(this, tr("错误"), tr("无效用户ID"));
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
        // 将toolbtn下对应的child显示到屏幕
        child[i]->showNormal();
    }
    // 其他信号交给父类进行默认处理
    return QToolBox::eventFilter(watched, event);
}

void toolbox1::init_toolBtn(){
    QString imagename;
    for(int i=0;i<CLIENTCOUNT;++i){
        toolBtn[i] = new QToolButton();
        toolBtn[i]->setObjectName(QString::number(i));// 设置ObjectName属性
        toolBtn[i]->installEventFilter(this);   //toolbtn的点击事件由toolbox1来处理
        toolBtn[i]->setText(username[i]); //设置toolbtn标题
        imagename.sprintf(":/images/%d.png", i);
        toolBtn[i]->setIcon(QPixmap(imagename));    // 设置toolbtn图像
        toolBtn[i]->setIconSize(QPixmap(imagename).size());
        toolBtn[i]->setAutoRaise(true); // 设置自动浮起界面风格
        toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置toolBtn文字在图像旁边
        toolBtn[i]->setToolTip(tr("未知"));//设置toolBtn 鼠标提示为“未知”
        child[i] = new Widget(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
    }

    QGroupBox *groupBox[8];
    QVBoxLayout *layout[8];
    static int index = 0;
    for(int i=0;i<8;++i){
        groupBox[i] = new QGroupBox();
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);       // 设置布局中个窗体的显示间距
        layout[i]->setAlignment(Qt::AlignLeft);  // 设置布局中各窗体的位置
        for(int j=0;j<32;j++){
            layout[i]->addWidget(toolBtn[index++]);  // 代表一个layout中加入32个toolbtn
        }
        layout[i]->addStretch();    // 插入一个占位符
    }

    addItem((QWidget *)groupBox[0], tr("好友"));
    addItem((QWidget *)groupBox[1], tr("家人"));
    addItem((QWidget *)groupBox[2], tr("同学"));
    addItem((QWidget *)groupBox[3], tr("同事"));
    addItem((QWidget *)groupBox[4], tr("网友"));
    addItem((QWidget *)groupBox[5], tr("驴友"));
    addItem((QWidget *)groupBox[6], tr("社区"));
    addItem((QWidget *)groupBox[7], tr("陌生人"));

}

void toolbox1::init_username(){
    for(int i=0;i<CLIENTCOUNT;++i){
        username[i] = tr("用户") + QString::number(i);
    }
}

void toolbox1::sock_err(QAbstractSocket::SocketError sock_err){
    switch (sock_err) {
    // 如果是远程服务器正常关闭socket，直接break
    case QAbstractSocket::RemoteHostClosedError:
        break;
    default:
        QMessageBox::information(this, tr("错误"), client->errorString());
    }
}

// 发送登录消息
void toolbox1::login_msg(){
    const char *pw = pwd.toStdString().data();
    if(client->isOpen()){       // 判断socket是否已经连接到远程server
        if(client->state() == QAbstractSocket::ConnectedState){
            struct msg_t msg;
            memset(&msg, 0, sizeof(msg));
            msg.head[0] = 1;    // 设置消息为登录消息
            msg.head[1] = userid;       // 设置登录用户ID
            msg.head[2] = 0;    // 保留
            msg.head[3] = 0;    // 保留

            strncpy(msg.body, pw, strlen(pw));      // 登录消息密码
            client->write((const char *)&msg, strlen(msg.body)+sizeof(msg.head));
        }
    }
}

void toolbox1::read_msg(){

}

// socket连接到server端以后调用的槽函数
void toolbox1::sock_connect(){
    // 向server端发送登录消息
    login_msg();
}
