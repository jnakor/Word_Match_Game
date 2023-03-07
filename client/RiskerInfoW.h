#pragma once

#include <QWidget>
#include "ui_RiskerInfoW.h"
#include "Risker.h"

class RiskerInfoW : public QWidget
{
	Q_OBJECT

public:
	RiskerInfoW(QWidget *parent = Q_NULLPTR);
	~RiskerInfoW();
	void get_info(std::string user_name);
private:
	Ui::RiskerInfoW ui;
	player_info info;
	risker_info else_info;
	void refresh();
};
