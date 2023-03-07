#include "RankWindow.h"

RankWindow::RankWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	show_rank();
	QObject::connect(ui.type_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(type_combo_change()));
	QObject::connect(ui.attribute_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(attr_combo_change()));
}

RankWindow::~RankWindow()
{
}

void RankWindow::type_combo_change() {
	if (ui.type_combo->currentIndex() == Player::type_risker) {
		if (type_now == Player::type_testmaker) {
			ui.attribute_combo->removeItem(1);
			ui.attribute_combo->addItem(QStringLiteral("经验值"));
			ui.attribute_combo->addItem(QStringLiteral("闯关数"));
		}
		type_now = Player::type_risker;
	}
	else {
		if (type_now == Player::type_risker)
		{
			ui.attribute_combo->removeItem(2);
			ui.attribute_combo->removeItem(1);
			ui.attribute_combo->addItem(QStringLiteral("出题数"));
		}
		type_now = Player::type_testmaker;
	}
	show_rank();
}

void RankWindow::attr_combo_change() {
	show_rank();
}

bool risker_cmp_level(risker_all_info &A, risker_all_info &B) {
	if (A.info.level != B.info.level)return A.info.level > B.info.level;
	else return A.else_info.exp > B.else_info.exp;
}

bool testmaker_cmp_level(testmaker_all_info &A, testmaker_all_info &B) {
	if (A.info.level != B.info.level)return A.info.level > B.info.level;
	else return A.else_info.problem_num > B.else_info.problem_num;
}

bool cmp_exp(risker_all_info &A, risker_all_info &B) {
	return A.else_info.exp > B.else_info.exp;
}

bool cmp_checkpoints(risker_all_info &A, risker_all_info &B) {
	return A.else_info.checkpoints > B.else_info.checkpoints;
}
bool cmp_problemnum(testmaker_all_info &A, testmaker_all_info &B) {
	return A.else_info.problem_num > B.else_info.problem_num;
}
void RankWindow::refresh_and_clearboard() {
	risker_info.clear();
	testmaker_info.clear();
	get_all_risker(risker_info);
	get_all_testmaker(testmaker_info);
	ui.rank_board->clear();
	ui.attr_board->clear();
}

void RankWindow::display_risker_item(int attr_type) {
	for (int i = 0; i < risker_info.size(); i++) {
		ui.rank_board->addItem(QString::fromStdString(risker_info[i].info.name));
		if (attr_type == 0)ui.attr_board->addItem(QString::fromStdString(std::to_string(risker_info[i].info.level)));
		else if (attr_type == 1)ui.attr_board->addItem(QString::fromStdString(std::to_string(risker_info[i].else_info.exp)));
		else if (attr_type == 2)ui.attr_board->addItem(QString::fromStdString(std::to_string(risker_info[i].else_info.checkpoints)));
	}
}
void RankWindow::display_testmaker_item(int attr_type) {
	for (int i = 0; i < testmaker_info.size(); i++) {
		ui.rank_board->addItem(QString::fromStdString(testmaker_info[i].info.name));
		if (attr_type == 0)ui.attr_board->addItem(QString::fromStdString(std::to_string(testmaker_info[i].info.level)));
		else if (attr_type == 1)ui.attr_board->addItem(QString::fromStdString(std::to_string(testmaker_info[i].else_info.problem_num)));
	}
}

void RankWindow::show_rank() {
	refresh_and_clearboard();
	if (ui.type_combo->currentIndex() == Player::type_risker) {
		switch (ui.attribute_combo->currentIndex())
		{
		case 0:
			std::sort(risker_info.begin(), risker_info.end(), risker_cmp_level);
			break;
		case 1:
			std::sort(risker_info.begin(), risker_info.end(), cmp_exp);
			break;
		case 2:
			std::sort(risker_info.begin(), risker_info.end(), cmp_checkpoints);
			break;
		}
		display_risker_item(ui.attribute_combo->currentIndex());
	}
	else {//出题者
		switch (ui.attribute_combo->currentIndex())
		{
		case 0:
			std::sort(testmaker_info.begin(), testmaker_info.end(), testmaker_cmp_level);
			break;
		case 1:
			std::sort(testmaker_info.begin(), testmaker_info.end(), cmp_problemnum);
			break;
		}
		display_testmaker_item(ui.attribute_combo->currentIndex());
	}
}