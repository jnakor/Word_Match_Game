#include "TestmakerInfoW.h"

TestmakerInfoW::TestmakerInfoW(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

TestmakerInfoW::~TestmakerInfoW()
{
}

void TestmakerInfoW::refresh() {
	ui.name->setText(QString::fromStdString(info.name));
	ui.level->setText(QString::fromStdString(std::to_string(info.level)));
	ui.problem_num->setText(QString::fromStdString(std::to_string(else_info.problem_num)));
}

void TestmakerInfoW::get_info(std::string user_name) {
	info = getplayerinfobyname(user_name);
	else_info = gettestmakerinfobyname(user_name);
	refresh();
}