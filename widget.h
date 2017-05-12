#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QToolButton>
#include <QLineEdit>
#include <QColor>


class toolbox1;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(const QIcon icon, int ID, QString name, toolbox1 * t, QWidget *parent = 0);
    virtual ~Widget();
    QPushButton *pushButton;


private:
    void init_widget();

    QTextBrowser *textBrowser;
    QFontComboBox *fontCombox;
    QComboBox *combox;
    QToolButton *toolbtn_1;
    QToolButton *toolbtn_2;
    QToolButton *toolbtn_3;
    QToolButton *toolbtn_4;
    QToolButton *toolbtn_5;
    QLineEdit *lineEdit;

    int userID;
    QString username;
    QColor color;
    toolbox1 *main_w;



};

#endif // WIDGET_H
