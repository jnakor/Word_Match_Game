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

	//QObject::connect(ui.online_button, SIGNAL(clicked()), this, SLOT(Online_open_pro()));

	QObject::connect(ui.continue_button, SIGNAL(clicked()), this, SLOT(Continue_click_pro()));

	//QObject::connect(ui.challege_button, SIGNAL(clicked()), this, SLOT(click_challege_pro()));

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



	//QObject::connect(ui.refresh_button, SIGNAL(clicked()), this, SLOT(Click_refresh_pro()));
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


void RiskerWindow::change_id_pro() {

}

std::string RiskerWindow::get_name() {
	return user->get_name();
}









