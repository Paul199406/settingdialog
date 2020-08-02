#include "basewidget.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QStyleOption>

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{
    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    //初始化标题栏
    initTitleBar();
}


void BaseWidget::initTitleBar()
{
    m_titleBar = new SettingTitleBar(this);
    m_titleBar->move(0,0);

    connect(m_titleBar,SIGNAL(signalButtonCloseClicked()),this,SLOT(onButtonCloseClicked()));
    connect(m_titleBar,SIGNAL(signalButtonMaxClicked()),this,SLOT(onButtonMaxClicked()));
    connect(m_titleBar,SIGNAL(signalButtonMinClicked()),this,SLOT(onButtonMinClicked()));
    connect(m_titleBar,SIGNAL(signalButtonRestoreClicked()),this,SLOT(onButtonRestoreClicked()));
}
void BaseWidget::paintEvent(QPaintEvent *event)
{
    //如果从QWidget子类化一个Widget，为了能够使用样式表则需要为自定义Widget提供paintEvent事件
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    //设置背景色
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(236, 241, 245)));

//	return QWidget::paintEvent(event);
}
void BaseWidget::loadStyleSheet(const QString &sheetName)
{
    QFile file(sheetName);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void BaseWidget::onButtonMinClicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        hide();    //设置了Qt::Tool 如果调用showMinimized()则窗口就销毁了？？？
    }
    else
    {
        showMinimized();
    }
}
void BaseWidget::onButtonRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}
void BaseWidget::onButtonMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(FactRect);
}
void BaseWidget::onButtonCloseClicked()
{
    close();
}
