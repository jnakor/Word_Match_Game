#pragma once

#include <QtWidgets/QMainWindow>
#include<qmessagebox.h>
#include "ui_SearchWindow.h"
#include "Player.h"
#include "Risker.h"
#include "Testmaker.h"
#include "RiskerInfoW.h"
#include "TestmakerInfoW.h"
#include "RankWindow.h"

class SearchWindow : public QWidget
{
	Q_OBJECT

public:
	SearchWindow(QWidget *parent = Q_NULLPTR);
	~SearchWindow();
private:
	Ui::SearchWindow ui;
	RiskerInfoW *RsInfoW;
	TestmakerInfoW *TsInfoW;
	RankWindow *RankW;
private slots:
	void search_option();
	void rank_option();
};
