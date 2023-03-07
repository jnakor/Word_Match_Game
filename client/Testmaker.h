#pragma once
#include "Player.h"
#include<string>
#include<vector>

struct testmaker_info
{
	int problem_num;
	testmaker_info() {
		problem_num = 0;
	}
};

typedef struct testmaker_all_info {
	player_info info;
	testmaker_info else_info;
}testmaker_all_info;

class Testmaker :public Player
{
private:
	struct testmaker_info *else_info;
	bool refresh();
	std::string own_table;
	std::vector<int> num_each;
public:
	Testmaker();
	~Testmaker();
	int get_num();
	void update_problem_num(int new_val);
	void add_problem_num();
	bool testmaker_register(std::string temp_name, std::string pass_word);
	bool testmaker_updatename(std::string temp_name, std::string new_name);
	bool testmaker_login(const std::string user_name);
	bool make_newword(std::string new_word);
	int this_level_need();
	int last_level_need();
	testmaker_info get_testmaker_info();
	friend testmaker_info gettestmakerinfobyname(std::string user_name);
	friend void get_all_testmaker(std::vector<testmaker_all_info> &all_info);
	bool testmaker_num_get();
};


