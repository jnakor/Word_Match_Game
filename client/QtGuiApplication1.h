#pragma once

#include <QtWidgets/QMainWindow>
#include<qmessagebox.h>
#include<QPushButton>
#include <QPalette>
#include<QStyle>
#include "ui_QtGuiApplication1.h"
#include "RegisterWindow.h"
#include<Windows.h>
#include "Player.h"
#include "Testmaker.h"
#include "Risker.h"
#include "TestmakerWindow.h"
#include "RiskerWindow.h"
#include "Connetion.h"

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	~QtGuiApplication1();
private:
	Ui::QtGuiApplication1Class ui;

	RegisterWindow *RgsW;
	Player *user_for_check;
	TestmakerWindow *TesmW;
	RiskerWindow *RskW;
private slots:
	void ClickLogin();
	void ClickRegister();
	void ForceLogin();
};
