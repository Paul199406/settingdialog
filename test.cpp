#include "test.h"
#include "ui_test.h"
#include "settingdialog.h"
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QStyleOption>
#include <QDebug>


test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);

    this->resize(400,300);

    QHBoxLayout * b = new QHBoxLayout(this);
    QPushButton *p1 = new QPushButton();
    QPushButton *p2 = new QPushButton();
    QPushButton *p3 = new QPushButton();

    b->addWidget(p1);
    b->addWidget(p2);
    b->addWidget(p3);
    b->setContentsMargins(0,0,0,0);
    b->setSpacing(0);
    p2->setVisible(false);

    QRect desktopRect = QApplication::desktop()->availableGeometry();

    qDebug() << desktopRect;
}

test::~test()
{
    delete ui;
}



void test::on_pushButton_clicked()
{
    int result = SettingDialog::showMessageBox(this, QStringLiteral("delete"), QStringLiteral("delete ?"), MESSAGE_WARNNING, BUTTON_OK_AND_CANCEL, false);
}
