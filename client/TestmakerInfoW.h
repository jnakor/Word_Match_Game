#pragma once

#include <QWidget>
#include "ui_TestmakerInfoW.h"
#include "Testmaker.h"
class TestmakerInfoW : public QWidget
{
	Q_OBJECT

public:
	TestmakerInfoW(QWidget *parent = Q_NULLPTR);
	~TestmakerInfoW();
	void get_info(std::string user_name);
private:
	Ui::TestmakerInfoW ui;
	player_info info;
	testmaker_info else_info;
	void refresh();
};
