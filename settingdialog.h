﻿#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include <QEventLoop>
#include "basewidget.h"

enum ChosseResult
{
    ID_OK = 0,						// 确定;
    ID_CANCEL						// 取消;
};

enum MessageType
{
    MESSAGE_INFORMATION = 0,		// 提示信息;
    MESSAGE_WARNNING,				// 提示警告;
    MESSAGE_QUESTION,				// 提示询问;
    MESSAGE_INPUT					// 提示输入框;
};

enum MessageButtonType
{
    BUTTON_OK = 0,					// 只有确定按钮;
    BUTTON_OK_AND_CANCEL,			// 确定、取消按钮;
    BUTTON_CLOSE					// 关闭按钮;
};

namespace Ui {
class SettingDialog;
}

class SettingDialog : public BaseWidget
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();


    void setWindowTitle(QString title, int titleFontSize = 10);
    void setContentText(QString contentText);
    void setMessageType(MessageType messageType);
    void setButtonType(MessageButtonType buttonType);

public:
    int static showMessageBox(QWidget* parent, const QString &title,const QString &contentText , MessageType messageType, MessageButtonType messageButtonType , bool isModelWindow = false);


private:
    void initWindow();
    void initTitleBar();
    int exec();

    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    Ui::SettingDialog *ui;
    QEventLoop* m_eventLoop;
    ChosseResult m_chooseResult;
};

#endif // SETTINGDIALOG_H
