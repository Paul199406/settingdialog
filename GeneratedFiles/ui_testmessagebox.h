/********************************************************************************
** Form generated from reading UI file 'testmessagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTMESSAGEBOX_H
#define UI_TESTMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestMessageBoxClass
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *TestMessageBoxClass)
    {
        if (TestMessageBoxClass->objectName().isEmpty())
            TestMessageBoxClass->setObjectName(QStringLiteral("TestMessageBoxClass"));
        TestMessageBoxClass->resize(425, 346);
        widget = new QWidget(TestMessageBoxClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 30, 321, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(150, 30));
        pushButton->setMaximumSize(QSize(150, 30));
        pushButton->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	font-family:Microsoft Yahei;\n"
"	color:white;\n"
"	background-color:rgb(14 , 150 , 254);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(14 , 135 , 228);\n"
"	padding-left:3px;\n"
"	padding-top:3px;\n"
"}"));

        horizontalLayout->addWidget(pushButton);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font-size:14px;"));

        horizontalLayout->addWidget(label);


        retranslateUi(TestMessageBoxClass);

        QMetaObject::connectSlotsByName(TestMessageBoxClass);
    } // setupUi

    void retranslateUi(QWidget *TestMessageBoxClass)
    {
        TestMessageBoxClass->setWindowTitle(QApplication::translate("TestMessageBoxClass", "TestMessageBox", 0));
        pushButton->setText(QApplication::translate("TestMessageBoxClass", "\346\211\223\345\274\200\346\210\221\347\232\204\346\217\220\347\244\272\346\241\206", 0));
        label->setText(QApplication::translate("TestMessageBoxClass", "\347\273\223\346\236\234\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class TestMessageBoxClass: public Ui_TestMessageBoxClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTMESSAGEBOX_H
