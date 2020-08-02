#include "settingtitlebar.h"
#include <QHBoxLayout>
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QMouseEvent>

#define BUTTON_HEIGHT 25        // 按钮高度;
#define BUTTON_WIDTH 25         // 按钮宽度;
#define TITLE_HEIGHT 25         // 标题栏高度;

SettingTitleBar::SettingTitleBar(QWidget *parent) : QWidget(parent)
   , m_colorR(200)
   , m_colorG(200)
   , m_colorB(200)
   , m_isPressed(false)
   , m_buttonType(MIN_MAX_BUTTON)
   , m_windowBorderWidth(0)
   , m_isTransparent(false)
{
   // 初始化;
   initControl();
   initConnections();
   // 加载本地样式 MyTitle.css文件;
   loadStyleSheet(":/SettingTitleBar");
}

// 设置标题栏背景色及是否设置标题栏背景色透明;
void SettingTitleBar::setBackgroundColor(int r, int g, int b , bool isTransparent )
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

// 设置标题栏图标;
void SettingTitleBar::setTitleIcon(QString filePath , QSize IconSize )
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(IconSize));
}
// 设置标题内容;
void SettingTitleBar::setTitleContent(QString titleContent , int titleFontSize)
{
    // 设置标题字体大小;
    QFont font = m_pTitleContent->font();
    font.setPointSize(titleFontSize);
    m_pTitleContent->setFont(font);
    // 设置标题内容;
    m_pTitleContent->setText(titleContent);
    m_titleContent = titleContent;
}
// 设置标题栏长度;
void SettingTitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}
// 设置标题栏上按钮类型;
void SettingTitleBar::setButtonType(ButtonType buttonType)
{
    m_buttonType = buttonType;

    switch (buttonType)
    {
    case MIN_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
        break;
    case MIN_MAX_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
    }
        break;
    case ONLY_CLOSE_BUTTON:
    {
        m_pButtonMin->setVisible(false);
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
        break;
    default:
        break;
    }
}

// 设置窗口边框宽度;
void SettingTitleBar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

// 保存/获取 最大化前窗口的位置及大小;
void SettingTitleBar::saveRestoreInfo(const QPoint point, const QSize size)
{
    m_restorePos = point;
    m_restoreSize = size;
}
void SettingTitleBar::getRestoreInfo(QPoint& point, QSize& size)
{
    point = m_restorePos;
    size = m_restoreSize;
}


// 绘制标题栏背景色;
void SettingTitleBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    // 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
    // 这里减去m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框;
    // 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0;
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }
    QWidget::paintEvent(event);
}

void SettingTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 只有存在最大化、还原按钮时双击才有效;
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
        // 或者通过单独设置变量来表示当前窗口状态;
        if (m_pButtonMax->isVisible())
        {
            onButtonMaxClicked();
        }
        else
        {
            onButtonRestoreClicked();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}
void SettingTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 在窗口最大化时禁止拖动窗口;
        if (m_pButtonMax->isVisible())
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
    }
    else
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();//相对于当前显示器的位置
    }

    return QWidget::mousePressEvent(event);
}
void SettingTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }

    return QWidget::mouseMoveEvent(event);
}
void SettingTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

// 初始化控件;
void SettingTitleBar::initControl()
{
    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;

    m_pButtonMin = new QPushButton;
    m_pButtonRestore = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;

    m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    m_pTitleContent->setObjectName("TitleContent");
    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonRestore->setObjectName("ButtonRestore");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");

    m_pButtonMin->setToolTip(QStringLiteral("最小化"));
    m_pButtonRestore->setToolTip(QStringLiteral("还原"));
    m_pButtonMax->setToolTip(QStringLiteral("最大化"));
    m_pButtonClose->setToolTip(QStringLiteral("关闭"));

    QHBoxLayout* titleLayout = new QHBoxLayout(this);
    titleLayout->addWidget(m_pIcon);
    titleLayout->addWidget(m_pTitleContent);

    titleLayout->addWidget(m_pButtonMin);
    titleLayout->addWidget(m_pButtonRestore);
    titleLayout->addWidget(m_pButtonMax);
    titleLayout->addWidget(m_pButtonClose);

    titleLayout->setContentsMargins(5, 0, 0, 0);
    titleLayout->setSpacing(0);

    m_pIcon->setVisible(false);
    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);
}
// 信号槽的绑定;
void SettingTitleBar::initConnections()
{
    connect(m_pButtonMin,SIGNAL(clicked()),this,SLOT(onButtonMinClicked()));
    connect(m_pButtonMax,SIGNAL(clicked()),this,SLOT(onButtonMaxClicked()));
    connect(m_pButtonRestore,SIGNAL(clicked()),this,SLOT(onButtonRestoreClicked()));
    connect(m_pButtonClose,SIGNAL(clicked()),this,SLOT(onButtonCloseClicked()));
}
// 加载样式文件;
void SettingTitleBar::loadStyleSheet(const QString &sheetName)
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


// 按钮触发的槽;
void SettingTitleBar::onButtonMinClicked()
{
    emit signalButtonMinClicked();
}

void SettingTitleBar::onButtonRestoreClicked()
{
    m_pButtonRestore->setVisible(false);
    m_pButtonMax->setVisible(true);
    emit signalButtonRestoreClicked();
}

void SettingTitleBar::onButtonMaxClicked()
{
    m_pButtonRestore->setVisible(true);
    m_pButtonMax->setVisible(false);
    emit signalButtonMaxClicked();
}

void SettingTitleBar::onButtonCloseClicked()
{
    emit signalButtonCloseClicked();
}
