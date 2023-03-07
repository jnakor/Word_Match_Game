#include "SearchWindow.h"

SearchWindow::SearchWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	RsInfoW = new RiskerInfoW();
	TsInfoW = new TestmakerInfoW();
	RankW = new RankWindow();
	QObject::connect(ui.search_button, SIGNAL(clicked()), this, SLOT(search_option()));
	QObject::connect(ui.rank_button, SIGNAL(clicked()), this, SLOT(rank_option()));
}

SearchWindow::~SearchWindow()
{
	delete RankW;
	delete TsInfoW;
	delete RsInfoW;
	std::cout << "~SearchWindow" << std::endl;
}

void SearchWindow::search_option() {
	std::string select_name = (ui.username->text()).toStdString();
	if (!exist(select_name)) {
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("此人 不 存 在 呀"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else {
		player_info select_info = getplayerinfobyname(select_name);
		if (select_info.type == Player::type_risker)
		{
			RsInfoW->get_info(select_name);
			RsInfoW->show();
		}
		else {
			TsInfoW->get_info(select_name);
			TsInfoW->show();
		}
	}
}

void SearchWindow::rank_option() {
	RankW->show();
}