#include "RiskerWindow.h"
#include<thread>
RiskerWindow::RiskerWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	user = new Risker();
	timer_example = new QTimer(this);
	timer_input = new QTimer(this);
	timer_correct = new QTimer(this);
	timer_before_start = new QTimer(this);
	timer_pk_example = new QTimer();
	timer_pkinput = new QTimer();
	greenBrush = QBrush(Qt::green, Qt::DiagCrossPattern);
	blackBrush = QBrush(Qt::black, Qt::DiagCrossPattern);
	QObject::connect(ui.search_button, SIGNAL(clicked()), this, SLOT(Search_open_pro()));

	QObject::connect(ui.start_button, SIGNAL(clicked()), this, SLOT(Start_click_pro()));

	QObject::connect(ui.online_button, SIGNAL(clicked()), this, SLOT(Online_open_pro()));

	QObject::connect(ui.continue_button, SIGNAL(clicked()), this, SLOT(Continue_click_pro()));

	QObject::connect(ui.challege_button, SIGNAL(clicked()), this, SLOT(click_challege_pro()));

	QObject::connect(ui.acc_button, SIGNAL(clicked()), this, SLOT(Click_acc_pro()));

	QObject::connect(ui.refuse_button, SIGNAL(clicked()), this, SLOT(Click_refuse_pro()));

	QObject::connect(this, SIGNAL(start_ck_sig()), this, SLOT(start_ck_pro()));

	QObject::connect(timer_example, SIGNAL(timeout()), this, SLOT(example_one_pro()));

	QObject::connect(this, SIGNAL(example_over_sig()), this, SLOT(start_input_pro()));

	QObject::connect(timer_input, SIGNAL(timeout()), this, SLOT(input_one_pro()));

	QObject::connect(this, SIGNAL(pass_round_sig()), this, SLOT(pass_round_pro()));

	QObject::connect(this, SIGNAL(correct_show_sig()), this, SLOT(correct_show_pro()));

	QObject::connect(timer_correct, SIGNAL(timeout()), this, SLOT(correct_over_pro()));

	QObject::connect(this, SIGNAL(pass_ck_sig()), this, SLOT(pass_ck_pro()));

	QObject::connect(this, SIGNAL(game_fail_sig()), this, SLOT(game_fail_pro()));

	QObject::connect(timer_before_start, SIGNAL(timeout()), this, SLOT(before_start_pro()));

	QObject::connect(this, SIGNAL(start_pk_sig()), this, SLOT(start_pk_pro()));

	QObject::connect(timer_pk_example, SIGNAL(timeout()), this, SLOT(pk_example_one_pro()));

	QObject::connect(this, SIGNAL(pk_example_over_sig()), this, SLOT(start_pkinput_pro()));

	QObject::connect(timer_pkinput, SIGNAL(timeout()), this, SLOT(pkinput_one_pro()));

	QObject::connect(this, SIGNAL(pk_round_pass_sig()), this, SLOT(pk_round_pass_pro()));

	QObject::connect(this, SIGNAL(pk_round_fail_sig()), this, SLOT(pk_round_fail_pro()));

	QObject::connect(this, SIGNAL(pk_all_over_sig()), this, SLOT(pk_all_over_pro()));

	QObject::connect(ui.back_button, SIGNAL(clicked()), this, SLOT(Click_back_pro()));

	QObject::connect(ui.refresh_button, SIGNAL(clicked()), this, SLOT(Click_refresh_pro()));
	switch_to_info();

}

RiskerWindow::~RiskerWindow()
{
	printf("del risk win\n");
	delete user;
}

void RiskerWindow::refresh_info() {
	int this_need = user->this_level_need() - user->last_level_need();
	int this_acc = user->get_exp() - user->last_level_need();
	ui.exp_display->setText(QString::fromStdString(std::to_string(this_acc)));
	ui.need_display->setText(QString::fromStdString("/" + std::to_string(this_need)));
	ui.exp_bar->setMaximum(this_need);
	ui.name->setText(QString::fromStdString(user->get_name()));
	ui.level->setText(QString::fromStdString(std::to_string(user->get_level())));
	ui.exp_bar->setValue(this_acc);
	ui.checkpoints->setText(QString::fromStdString(std::to_string(user->get_checkpoints())));
}

void RiskerWindow::refresh_play() {
	ui.current_checkpoint->setText(QString::fromStdString(std::to_string(gk.ck_now)));
}

bool RiskerWindow::user_login(std::string user_name) {
	if (user->risker_login(user_name));
	else {
		std::cout << "RiskerWindow::user_login:failed" << std::endl;
		return false;
	}
	refresh_info();
	return true;
}

void RiskerWindow::switch_to_info() {
	refresh_info();
	ui.timeleft->hide();
	ui.input->hide();
	ui.input_tip->hide();
	ui.current_checkpoint_label->hide();
	ui.current_checkpoint->hide();
	ui.exp_add_label->hide();
	ui.add_val_label->hide();
	ui.correct_label->hide();
	ui.acc_button->hide();
	ui.refuse_button->hide();
	ui.challeger_name->hide();
	ui.be_challeged_label->hide();
	ui.reply_label->hide();
	ui.result_label->hide();
	ui.he_time->hide();
	ui.your_time->hide();
	ui.he_time_label->hide();
	ui.your_time->hide();
	ui.your_time_label->hide();
	ui.back_button->hide();
	ui.refresh_button->show();
	ui.name_label->show();
	ui.name->show();
	ui.checkpoints_label->show();
	ui.checkpoints->show();
	ui.exp_label->show();
	ui.exp_bar->show();
	ui.level_label->show();
	ui.level->show();
	ui.search_button->show();
	ui.start_button->show();
	ui.continue_button->show();
	ui.exp_display->show();
	ui.need_display->show();
	ui.online_button->show();
	ui.challege_button->show();
	ui.challege_name->show();
}

void RiskerWindow::Start_click_pro() {
	gk.restart();
	switch_to_play();
}

void RiskerWindow::Continue_click_pro() {
	gk.ck_now=user->get_checkpoints() + 1;
	switch_to_play();
}

void RiskerWindow::switch_to_play() {
	ui.refresh_button->hide();
	refresh_play();
	ui.name_label->hide();
	ui.name->hide();
	ui.checkpoints_label->hide();
	ui.checkpoints->hide();
	ui.exp_label->hide();
	ui.exp_bar->hide();
	ui.level_label->hide();
	ui.level->hide();
	ui.search_button->hide();
	ui.input_tip->hide();
	ui.continue_button->hide();
	ui.start_button->hide();
	ui.exp_display->hide();
	ui.need_display->hide();
	ui.online_button->hide();
	ui.challege_button->hide();
	ui.refuse_button->hide();
	ui.challege_name->hide();
	ui.be_challeged_label->hide();
	ui.challeger_name->hide();
	ui.acc_button->hide();
	ui.reply_label->hide();
	ui.timeleft->show();
	ui.input->show();
	ui.current_checkpoint_label->show();
	ui.current_checkpoint->show();
	emit start_ck_sig();
}

void RiskerWindow::start_ck_pro() {
	gk.ck_start();
	wordpool.clear();
	window_add_word(wordlenofck() + 1);
	window_add_word(wordlenofck());
	window_add_word(wordlenofck() - 1);
	start_round_pro();
}

void RiskerWindow::start_round_pro() {
	recover_time();
	to_black();
	ui.correct_label->hide();
	ui.exp_add_label->hide();
	ui.add_val_label->hide();
	exampleword_show();
	ui.input->setFocusPolicy(Qt::NoFocus);//不允许获得焦点
	timer_example->start(speed());
}

void RiskerWindow::exampleword_show() {
	ui.input_tip->hide();
	srand(time(NULL));
	example_word = wordpool[rand() % wordpool.size()];
	ui.input->clearFocus();
	ui.input->setText(QString::fromStdString(example_word));
}

void RiskerWindow::example_one_pro() {
	ui.timeleft->setValue(ui.timeleft->value() - 1);
	if (ui.timeleft->value() == 0) {
		timer_example->stop();
		ui.input->setText("");
		emit example_over_sig();
	}
	else timer_example->start(speed());
}

void RiskerWindow::start_input_pro() {
	ui.timeleft->setMaximum(30);
	ui.timeleft->setValue(ui.timeleft->maximum());
	ui.input_tip->show();
	timer_input->start(speed());
	ui.input->setFocus();
}

void RiskerWindow::input_one_pro() {
	ui.timeleft->setValue(ui.timeleft->value() - 1);
	if (ui.timeleft->value() == 0) {
		timer_input->stop();
		emit game_fail_sig();
	}
	else if (ui.input->text().toStdString() == example_word) {
		timer_input->stop();
		emit pass_round_sig();
	}
	else timer_input->start(speed());
}

void RiskerWindow::pass_round_pro() {
	//round++;
	gk.round++;
	user->update_exp(exp_prize() + user->get_exp());
	emit correct_show_sig();
}

void RiskerWindow::game_fail_pro() {
	QMessageBox::warning(NULL, QStringLiteral("啊噢"), QStringLiteral("你挂了"), QMessageBox::Yes, QMessageBox::Yes);
	switch_to_info();
}

void RiskerWindow::correct_show_pro() {
	to_green();
	ui.correct_label->show();
	ui.exp_add_label->show();
	ui.add_val_label->setText(QString::fromStdString(std::to_string(exp_prize())));
	ui.add_val_label->show();
	timer_correct->start(1000);
}

void RiskerWindow::correct_over_pro() {
	timer_correct->stop();
	if (round_enough()) {
		emit pass_ck_sig();
	}
	else start_round_pro();
}

void RiskerWindow::pass_ck_pro() {
	gk.ck_now++;
	refresh_play();
	refresh_info();
	if (gk.ck_now - 1 > user->get_checkpoints()) {
		user->update_checkpoints(gk.ck_now - 1);
	}
	start_ck_pro();
}

bool RiskerWindow::round_enough() {
	//暂时这样
	return gk.round > gk.ck_now + 1;
}

int RiskerWindow::speed() {
	return 100;
}

void RiskerWindow::window_add_word(int len) {
	do {
		user->risker_get_word(len, wordpool);
		len = len - 1;
	} while (wordpool.size() == 0);
	for (int i = 0; i < wordpool.size(); i++) {
		std::cout << wordpool[i] << std::endl;
	}
}

void RiskerWindow::to_green() {
	palette.setBrush(QPalette::Text, greenBrush);
	ui.input->setPalette(palette);
}

void RiskerWindow::to_black() {
	palette.setBrush(QPalette::Text, blackBrush);
	ui.input->setPalette(palette);
}

int RiskerWindow::wordlenofck() {
	return gk.ck_now + 2;
}

void RiskerWindow::recover_time() {
	ui.timeleft->setMaximum(30 - gk.ck_now * 5);
	ui.timeleft->setValue(ui.timeleft->maximum());
	ui.timeleft->setValue(30 - gk.ck_now * 5);
}

int RiskerWindow::exp_prize() {
	return 2 *gk.ck_now + 8;//暂时
}

void RiskerWindow::Search_open_pro() {
	SearchWindow* SW = new SearchWindow();
	SW->setAttribute(Qt::WA_DeleteOnClose, true);
	SW->show();
}

void RiskerWindow::Online_open_pro() {
	Online_Window *OW = new Online_Window();
	OW->setAttribute(Qt::WA_DeleteOnClose, true);
	OW->get_sock(user->get_sockout());
	OW->show();
}

void RiskerWindow::change_id_pro() {

}

void RiskerWindow::get_sock(Connetion *__sk) {
	user->get_sock(__sk);
}

std::string RiskerWindow::get_name() {
	return user->get_name();
}

void RiskerWindow::click_challege_pro() {
	Connetion *sk = user->get_sockout();
	std::string challeged_name = ui.challege_name->text().toStdString();
	challeger_name = challeged_name;
	if (challeger_name == user->get_name()) {
		QMessageBox::warning(NULL, QStringLiteral("通知"), QStringLiteral("不能挑战自己哦"), QMessageBox::Yes, QMessageBox::Yes);
	}
	else sk->send_challege(challeged_name);
}

void RiskerWindow::get_pk_word(int len) {
	wordpool.clear();
	window_add_word(len);
}
void RiskerWindow::start_pk_pro() {
	ui.timeleft->setMaximum(30);
	ui.timeleft->setValue(ui.timeleft->maximum());
	ui.input_tip->hide();
	srand(pk_round_now);
	example_word = wordpool[rand() % wordpool.size()];
	ui.input->clearFocus();
	ui.input->setText(QString::fromStdString(example_word));
	ui.input->setFocusPolicy(Qt::NoFocus);//不允许获得焦点
	timer_pk_example->start(speed());
}

void RiskerWindow::pk_example_one_pro() {
	ui.timeleft->setValue(ui.timeleft->value() - 1);
	if (ui.timeleft->value() == 0) {
		timer_pk_example->stop();
		ui.input->setText("");
		//emit pk_example_over_sig();
		start_pkinput_pro();
	}
	else timer_pk_example->start(speed());
}

void RiskerWindow::start_pkinput_pro() {
	ui.timeleft->setMaximum(30 - gk.ck_now * 5);
	ui.timeleft->setValue(ui.timeleft->maximum());
	ui.input_tip->show();
	timer_pkinput->start(pk_input_gap);
	ui.input->setFocus();
}

void RiskerWindow::pkinput_one_pro() {
	ui.timeleft->setValue(ui.timeleft->value() - 1);
	if (ui.timeleft->value() == 0) {
		timer_pkinput->stop();
		emit pk_round_fail_sig();
	}
	else if (ui.input->text().toStdString() == example_word) {
		timer_pkinput->stop();
		emit pk_round_pass_sig();
	}
	else timer_pkinput->start(pk_input_gap);
}

void RiskerWindow::pk_round_over_pro() {
	//user->get_sockout()->send;
}

void RiskerWindow::Click_acc_pro() {
	Connetion *sk;
	sk = user->get_sockout();
	sk->send_accept(ui.challeger_name->text().toStdString());
	score = 0;
	pk_round_now = 0;
	get_pk_word(5);
	before_start_pro();
}

void RiskerWindow::he_accept_you() {
	ui.reply_label->setText(QStringLiteral("对方接受咯,3 s 后开始pk"));
	//timer_before_start->start(300);
	ui.reply_label->show();
	score = 0;
	pk_round_now = 0;
	get_pk_word(5);
	before_start_pro();
}
void RiskerWindow::he_refuse_you() {
	ui.reply_label->setText(QStringLiteral("对方不想和你玩"));
	ui.reply_label->show();
}
void RiskerWindow::he_challege_you(std::string his_name) {
	ui.refresh_button->hide();
	challeger_name = his_name;
	ui.challeger_name->setText(QString::fromStdString(challeger_name));
	ui.acc_button->show();
	ui.refuse_button->show();
	ui.challeger_name->show();
	ui.be_challeged_label->show();
}

void RiskerWindow::he_is_busy() {
	ui.reply_label->setText(QStringLiteral("对方忙"));
	ui.reply_label->show();
}

void RiskerWindow::Click_refuse_pro() {
	Connetion *sk;
	sk = user->get_sockout();
	sk->send_refuse(challeger_name);
	switch_to_info();
}

void RiskerWindow::before_start_pro() {
	ui.refresh_button->hide();
	ui.name_label->hide();
	ui.name->hide();
	ui.checkpoints_label->hide();
	ui.checkpoints->hide();
	ui.exp_label->hide();
	ui.exp_bar->hide();
	ui.level_label->hide();
	ui.level->hide();
	ui.search_button->hide();
	ui.input_tip->hide();
	ui.continue_button->hide();
	ui.start_button->hide();
	ui.exp_display->hide();
	ui.need_display->hide();
	ui.online_button->hide();
	ui.current_checkpoint_label->hide();
	ui.current_checkpoint->hide();
	ui.challege_button->hide();
	ui.acc_button->hide();
	ui.refuse_button->hide();
	ui.challeger_name->hide();
	ui.challege_name->hide();
	ui.reply_label->hide();
	ui.be_challeged_label->hide();
	ui.timeleft->show();
	ui.input->show();
	emit start_pk_sig();
}

void RiskerWindow::pk_round_pass_pro() {
	pk_round_now++;
	score += ui.timeleft->value();
	//score += 1;
	if (pk_round_now == pk_rounds_all) {
		Connetion *sk = user->get_sockout();
		sk->send_end(challeger_name, score);
		emit pk_all_over_sig();
	}
	else {
		emit start_pk_sig();
	}
}
void RiskerWindow::pk_round_fail_pro() {
	pk_round_now++;
	score += 0;
	if (pk_round_now == pk_rounds_all) {
		emit pk_all_over_sig();
	}
	else {
		emit start_pk_sig();
	}
}

void RiskerWindow::pk_all_over_pro() {
	switch_to_result();
	Connetion *sk = user->get_sockout();
	sk->send_end(challeger_name, score);
}
void RiskerWindow::show_he_result(int he_score) {
	ui.he_time->setText(QString::fromStdString(std::to_string(score)));
	ui.he_time->setText(QString::fromStdString(std::to_string(he_score)));
	if (he_score < score) {
		ui.result_label->setText(QStringLiteral("赛果：胜利啦"));
	}
	else if (he_score > score) {
		ui.result_label->setText(QStringLiteral("赛果：你输了哦"));
	}
	else {
		ui.result_label->setText(QStringLiteral("赛果：平局"));
	}
}

void RiskerWindow::switch_to_result() {
	ui.timeleft->hide();
	ui.input_tip->hide();
	ui.input->hide();
	ui.your_time->setText(QString::fromStdString(std::to_string(score)));
	if (result_flag == 0) {
		ui.result_label->setText(QStringLiteral("赛果：等待中"));
		ui.he_time->setText(QStringLiteral("等待中"));
	}
	else {
		;
	}
	ui.back_button->show();
	ui.result_label->show();
	ui.he_time_label->show();
	ui.he_time->show();
	ui.your_time_label->show();
	ui.your_time->show();
	ui.he_time->show();
}

void RiskerWindow::Click_back_pro() {
	result_flag = 0;
	Connetion *sk = user->get_sockout();
	sk->send_free();
	switch_to_info();
}

void RiskerWindow::set_result_flag() {
	result_flag = 1;
}

void RiskerWindow::he_offline() {
	ui.reply_label->setText(QStringLiteral("对方不在线啊"));
	ui.reply_label->show();
}

void RiskerWindow::Click_refresh_pro() {
	switch_to_info();
}