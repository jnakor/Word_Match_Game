#pragma once

#include <QtWidgets/QMainWindow>
#include<qmessagebox.h>
#include "ui_TestmakerWindow.h"
#include "Testmaker.h"
#include "SearchWindow.h"

class TestmakerWindow : public QWidget
{
	Q_OBJECT

public:
	TestmakerWindow(QWidget *parent = Q_NULLPTR);
	~TestmakerWindow();
	bool user_login(std::string user_name);
	std::string get_name();
private:
	Ui::TestmakerWindow ui;
	Testmaker *user;
	void refresh_info();
	bool islegal(std::string new_word);
private slots:
	void ClickInputButton();
	void Search_open();
};
