#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "settingtitlebar.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);

signals:

protected:

    void initTitleBar();
    void paintEvent(QPaintEvent *event);
    void loadStyleSheet(const QString &sheetName);

public slots:

    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();

protected:

    SettingTitleBar * m_titleBar;
};

#endif // BASEWIDGET_H
