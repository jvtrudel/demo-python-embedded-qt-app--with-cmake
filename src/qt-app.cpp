#include <QtWidgets>
#include <QApplication>

#include "embeddedPy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *w = new QWidget();


    QLineEdit *intEdit = new QLineEdit();
    QLineEdit *strEdit = new QLineEdit();

    QPushButton *funcBut =new QPushButton("using function");
    QPushButton *classBut =new QPushButton("using class");



    QFormLayout *flay = new QFormLayout();
    QVBoxLayout *lay = new QVBoxLayout();
    QHBoxLayout *blay = new QHBoxLayout();

    flay->addRow("int", intEdit);
    flay->addRow("str",strEdit);

    blay->addWidget(funcBut);
    blay->addWidget(classBut);

    lay->addLayout(flay);
    lay->addLayout(blay);

    w->setLayout(lay);


    QObject::connect(funcBut,&QPushButton::clicked,[intEdit,strEdit](){
       embPyFunc(intEdit->text().toInt(),strEdit->text().toStdString());
    });
    QObject::connect(classBut,&QPushButton::clicked,[intEdit,strEdit](){
        embPy pclass;
        pclass.action(intEdit->text().toInt(),strEdit->text().toStdString());
    });


    w->show();



    return a.exec();
}
