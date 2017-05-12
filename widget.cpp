#pragma execution_character_set("utf-8")

#include "widget.h"
#include "toolbox1.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(const QIcon icon, int ID, QString name, toolbox1 *w, QWidget *parent)
    : QWidget(parent)
{
    userID = ID;
    username = name;
    main_w = w;

    setWindowTitle(name);
    setWindowIcon(icon);

    // ���������С����Ч
    //setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint&Qt::WindowMinimizeButtonHint);
    // ���ò�������������
    //setWindowFlags(windowFlags() | Qt::Tool);

    // ���ñ�����ɫ
    /*setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::darkCyan));
    setPalette(palette);*/

    init_widget();
}

Widget::~Widget()
{
}

void Widget::init_widget(){
    textBrowser = new QTextBrowser();
    // �������챳����ɫ��ͼƬ
    //textBrowser->setStyleSheet("background-image:url(:/images/1.jpg)");
    //textBrowser->setStyleSheet("border-image:url(:/images/1.jpg)");

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(textBrowser);

    fontCombox = new QFontComboBox();
    fontCombox->setToolTip(tr("����"));

    combox = new QComboBox();
    combox->setToolTip(tr("�ֺ�"));
    combox->setEditable(true);
    combox->addItem(QString::number(8));
    combox->addItem(QString::number(9));
    combox->addItem(QString::number(10));
    combox->addItem(QString::number(11));
    combox->addItem(QString::number(12));
    combox->addItem(QString::number(13));
    combox->addItem(QString::number(14));
    combox->addItem(QString::number(15));
    combox->addItem(QString::number(16));
    combox->addItem(QString::number(17));
    combox->addItem(QString::number(18));
    combox->addItem(QString::number(19));
    combox->addItem(QString::number(20));
    combox->addItem(QString::number(21));
    combox->addItem(QString::number(22));
    combox->setCurrentIndex(4);

    toolbtn_1 = new QToolButton();
    toolbtn_1->setToolTip(tr("�Ӵ�"));
    toolbtn_1->setText(tr("�Ӵ�"));
    toolbtn_1->setCheckable(true);
    toolbtn_1->setAutoRaise(true);
    toolbtn_1->setIcon(QPixmap(":/images/bold.png"));

    toolbtn_2 = new QToolButton();
    toolbtn_2->setToolTip(tr("��б"));
    toolbtn_2->setText(tr("��б"));
    toolbtn_2->setCheckable(true);
    toolbtn_2->setAutoRaise(true);
    toolbtn_2->setIcon(QPixmap(":/images/italic.png"));

    toolbtn_3 = new QToolButton();
    toolbtn_3->setToolTip(tr("�»���"));
    toolbtn_3->setText(tr("�»���"));
    toolbtn_3->setCheckable(true);
    toolbtn_3->setAutoRaise(true);
    toolbtn_3->setIcon(QPixmap(":/images/under.png"));

    toolbtn_4 = new QToolButton();
    toolbtn_4->setToolTip(tr("��ɫ"));
    toolbtn_4->setText(tr("��ɫ"));
    toolbtn_4->setCheckable(true);
    toolbtn_4->setAutoRaise(true);
    toolbtn_4->setIcon(QPixmap(":/images/color.png"));

    toolbtn_5 = new QToolButton();
    toolbtn_5->setText(tr("��ʾ������"));
    toolbtn_5->setAutoRaise(true);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(fontCombox);
    layout2->addWidget(combox);
    layout2->addWidget(toolbtn_1);
    layout2->addWidget(toolbtn_2);
    layout2->addWidget(toolbtn_3);
    layout2->addWidget(toolbtn_4);
    layout2->addWidget(toolbtn_5);

    lineEdit = new QLineEdit();

    pushButton = new QPushButton();
    pushButton->setText(tr("����"));

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(lineEdit);
    layout3->addWidget(pushButton);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(layout1);
    main_layout->addLayout(layout2);
    main_layout->addLayout(layout3);
    // ���ô��ڴ�С���ܸı�
    //main_layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(main_layout);

    // ����textbrowser��Ĭ������
    textBrowser->setCurrentFont(fontCombox->font());
    // ����textbrowser��Ĭ���ֺ�
    textBrowser->setFontPointSize(combox->currentText().toDouble());
    lineEdit->setFocus();


}

