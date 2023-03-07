#include "RiskerInfoW.h"

RiskerInfoW::RiskerInfoW(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

RiskerInfoW::~RiskerInfoW()
{
}

void RiskerInfoW::refresh() {
	ui.name->setText(QString::fromStdString(info.name));
	ui.level->setText(QString::fromStdString(std::to_string(info.level)));
	ui.exp->setText(QString::fromStdString(std::to_string(else_info.exp)));
	ui.checkpoints->setText(QString::fromStdString(std::to_string(else_info.checkpoints)));
}
void RiskerInfoW::get_info(std::string user_name) {
	info = getplayerinfobyname(user_name);
	else_info = getriskerinfobyname(user_name);
	refresh();
}