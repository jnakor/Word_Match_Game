#pragma once

#include <QWidget>
#include "ui_Online_Window.h"
#include"Connetion.h"
#include <string>
#include<vector>
class Online_Window : public QWidget
{
	Q_OBJECT

public:
	Online_Window(QWidget *parent = Q_NULLPTR);
	~Online_Window();
	void get_sock(Connetion *__sk);
private:
	Ui::Online_Window ui;
	Connetion *sk;
	std::vector<std::string> names_list;
private slots:
	void get_online_people();
	void refresh_clear();
	void display_names();
};
