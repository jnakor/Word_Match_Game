#pragma once

#include <QWidget>
#include "ui_RankWindow.h"
#include "Player.h"
#include "Risker.h"
#include "Testmaker.h"
#include<algorithm>

class RankWindow : public QWidget
{
	Q_OBJECT

public:
	RankWindow(QWidget *parent = Q_NULLPTR);
	~RankWindow();
private:
	Ui::RankWindow ui;
	int type_now = Player::type_risker;//初始为闯关者选项
	std::vector<risker_all_info> risker_info;
	std::vector<testmaker_all_info> testmaker_info;
	void show_rank();
	void display_risker_item(int attr_type);
	void display_testmaker_item(int attr_type);
	void refresh_and_clearboard();
private slots:
	void type_combo_change();
	void attr_combo_change();
};
