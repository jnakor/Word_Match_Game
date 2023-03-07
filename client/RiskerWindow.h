#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RiskerWindow.h"
#include "Risker.h"
#include "SearchWindow.h"
#include "Online_Window.h"
#include <qtimer.h>
#include<vector>
#include<stdlib.h>
#include"Connetion.h"
#include"guanka.h"
class RiskerWindow : public QWidget
{
	Q_OBJECT

public:
	RiskerWindow(QWidget *parent = Q_NULLPTR);
	~RiskerWindow();
	bool user_login(std::string user_name);
	void get_sock(Connetion *__sk);
	std::string get_name();
	void he_accept_you();
	void he_refuse_you();
	void he_challege_you(std::string his_name);
	void he_is_busy();
	void he_offline();
	void show_he_result(int __time_use);
	void set_result_flag();
private:
	Ui::RiskerWindow ui;
	Risker *user;
	QBrush greenBrush;
	QBrush blackBrush;
	QPalette palette;
	QTimer *timer_example;
	QTimer *timer_input;
	QTimer *timer_correct;
	QTimer *timer_pk_example;
	QTimer *timer_pkinput;
	QTimer *timer_before_start;
	Connetion *acc_sk;

	guanka gk;
	int score = 0;
	int pk_rounds_all = 2;
	int pk_round_now = 1;
	int result_flag = 0;
	std::string challeger_name;
	int pk_input_gap = 100;
	std::string example_word;
	std::vector<std::string> wordpool;
	void refresh_info();
	void refresh_play();
	void switch_to_play();
	void switch_to_info();
	void switch_to_result();
	void window_add_word(int len);
	void get_pk_word(int len);
	void exampleword_show();
	int wordlenofck();
	void recover_time();
	bool round_enough();
	void to_green();
	void to_black();
	int speed();
	int exp_prize();
signals:
	void example_over_sig();
signals:
	void pass_ck_sig();
signals:
	void pass_round_sig();
signals:
	void game_fail_sig();
signals:
	void start_ck_sig();
signals:
	void correct_show_sig();
signals:
	void start_pk_sig();
signals:
	void pk_inputtimer_over_sig();
signals:
	void pk_example_over_sig();
signals:
	void pk_round_pass_sig();
signals:
	void pk_round_fail_sig();
signals:
	void pk_all_over_sig();
private slots:
	void change_id_pro();
	void Search_open_pro();
	void Online_open_pro();
	void Start_click_pro();
	void Continue_click_pro();
	void Click_acc_pro();
	void Click_refuse_pro();
	void example_one_pro();
	void input_one_pro();
	void pk_example_one_pro();
	void pkinput_one_pro();
	void start_input_pro();
	void start_ck_pro();
	void start_pkinput_pro();
	void game_fail_pro();
	void pass_round_pro();
	void pass_ck_pro();
	void start_round_pro();
	void correct_show_pro();
	void correct_over_pro();
	void start_pk_pro();
	void pk_round_over_pro();
	void click_challege_pro();
	void before_start_pro();
	void pk_round_pass_pro();
	void pk_round_fail_pro();
	void pk_all_over_pro();
	void Click_back_pro();
	void Click_refresh_pro();
};