#pragma execution_character_set("utf-8")

#include "login.h"
#include <QGridLayout>
#include <QMessageBox>

login::login(QWidget *parent):
    QDialog(parent)
{
    username = new QLabel();
    username->setText(tr("用户ID"));
    userID = new QLineEdit();

    passwd = new QLabel();
    passwd->setText(tr("密码"));
    passWord = new QLineEdit();
    passWord->setEchoMode(QLineEdit::Password);

    serverIP = new QLabel();
    serverIP->setText(tr("服务器IP"));
    hostIP = new QLineEdit();

    serverPort = new QLabel();
    serverPort->setText(tr("服务器端口号"));
    hostPort = new QLineEdit();

    loginButton = new QPushButton();
    loginButton->setText(tr("登录"));
    logoutButton = new QPushButton();
    logoutButton->setText(tr("取消"));

    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(username, 0, 0);
    layout1->addWidget(userID, 0, 1);

    layout1->addWidget(passwd, 1, 0);
    layout1->addWidget(passWord, 1, 1);

    layout1->addWidget(serverIP, 2, 0);
    layout1->addWidget(hostIP, 2, 1);

    layout1->addWidget(serverPort, 3, 0);
    layout1->addWidget(hostPort, 3, 1);

    layout1->addWidget(loginButton, 4, 0);
    layout1->addWidget(logoutButton, 4, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 1);

    layout1->setMargin(15);
    layout1->setSpacing(10);
    layout1->setSizeConstraint(QLayout::SetFixedSize);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginOnClick()));
    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logoutOnClick()));

    isLogin = false;
    // 设置窗口图标
    setWindowIcon(QPixmap(":/images/3.png"));
    userID->setFocus();

    // 设置窗口没有边框
    setWindowFlags(Qt::FramelessWindowHint);

    // 设置对话框背景颜色或图片
    /*setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(Qt::blue));
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/1.jpg")));
    setPalette(palette);*/

}

void login::loginOnClick(){
    if(userID->text().isEmpty()){
        QMessageBox::information(this, tr("错误！"), tr("用户ID不能为空！"));
        userID->setFocus();
    }else{
        bool ok;
        userid = userID->text().toInt(&ok);
        if(!ok){
            QMessageBox::information(this, tr("错误！"), tr("用户ID为0-255的数字！"));
            userID->setFocus();
        }else{
            isLogin = true;
            pwd = passWord->text();
            hostip = hostIP->text();
            hostport = hostPort->text().toInt();
            close();
        }
    }
}

void login::logoutOnClick(){
    close();
}
