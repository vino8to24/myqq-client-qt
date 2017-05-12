#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class login : public QDialog
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = 0);

signals:

private slots:
    void loginOnClick();
    void logoutOnClick();


private:
    QLabel *username;
    QLabel *passwd;
    QLabel *serverIP;
    QLabel *serverPort;

    QLineEdit *userID;
    QLineEdit *passWord;
    QLineEdit *hostIP;
    QLineEdit *hostPort;

    QPushButton *loginButton;
    QPushButton *logoutButton;

public:
    int userid;
    QString pwd;
    QString hostip;
    int hostport;
    bool isLogin;
};

#endif // LOGIN_H
