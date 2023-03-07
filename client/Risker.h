#pragma once
#include "Player.h"
#include<string>

typedef struct risker_info {
	int exp;//经验值
	int checkpoints;//关卡数
}risker_info;

typedef struct risker_all_info {
	player_info info;
	risker_info else_info;
}risker_all_info;
class Risker :public Player
{
private:
	bool refresh();
	std::string own_table;
	struct risker_info *else_info;
	std::vector<int> exp_each;
public:
	Risker();
	~Risker();
	bool risker_register(std::string temp_name, std::string pass_word);
	void update_exp(int new_val);
	void add_exp();
	void update_checkpoints(int new_val);
	void add_checkpoints();
	bool risker_login(const std::string user_name);
	int get_exp();
	int get_checkpoints();
	int this_level_need();
	int last_level_need();
	bool risker_updatename(std::string temp_name, std::string new_name);
	void risker_get_word(int len, std::vector<std::string>&word_vector);
	friend void get_all_risker(std::vector<risker_all_info> &all_info);
	risker_info get_risker_info();
	friend risker_info getriskerinfobyname(std::string  user_name);
	bool risker_exp_get();
};

