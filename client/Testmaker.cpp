#include "Testmaker.h"
#include<string>
using std::string;

Testmaker::Testmaker()
{
	own_table = Testmaker_table;
	else_info = new testmaker_info();
	testmaker_num_get();
}

Testmaker::~Testmaker()
{
	delete else_info;
}
bool Testmaker::testmaker_register(std::string temp_name, std::string pass_word) {
	if (register_name(temp_name, type_testmaker, pass_word));
	else return false;
	if (game_database->insert_new(temp_name, own_table)) {
		std::cout << "Testmaker::注册成功" << std::endl;
		refresh();//默认值导入
		return true;
	}
	else {
		std::cout << "Testmaker::注册失败" << std::endl;
		return false;
	}
}
bool Testmaker::testmaker_updatename(std::string temp_name, std::string new_name) {
	update_name(temp_name, new_name);
	if (game_database->update_something(temp_name, own_table, "name", new_name)) {
		std::cout << "Testmaker::修改成功" << std::endl;
		refresh();
	}
	else {
		std::cout << "Testmaker::修改失败" << std::endl;
	}
	return true;
}
bool Testmaker::refresh() {
	MYSQL_ROW row = game_database->read_data(info->name, own_table);
	if (row == NULL) {
		//不存在时会返回空row
		std::cout << "Testmaker::refresh failed" << std::endl;
		return false;
	}
	else {
		else_info->problem_num = std::atoi(row[1]);
		return true;
	}
}
void Testmaker::update_problem_num(int new_val) {
	if (game_database->update_something(info->name, own_table, "num", new_val)) {
		std::cout << "Testmaker::修改成功" << std::endl;
		refresh();
	}
	else {
		std::cout << "Testmaker::修改失败" << std::endl;
	}
	if (else_info->problem_num >= this_level_need())add_level();
}
void Testmaker::add_problem_num() {
	update_problem_num(else_info->problem_num + 1);//这里不用refresh，因为update里有
}
bool Testmaker::testmaker_login(const std::string user_name) {
	if (Player_login(user_name));
	else return false;
	if (refresh()) {
		return true;
	}
	else {
		std::cout << "Testmaker::login failed" << std::endl;
		return false;
	}
}
int Testmaker::get_num() {
	return else_info->problem_num;
}
bool Testmaker::make_newword(std::string new_word) {
	return game_database->insert_newword(new_word);
}

testmaker_info Testmaker::get_testmaker_info() {
	return *else_info;
}

testmaker_info gettestmakerinfobyname(std::string user_name) {
	Testmaker temp;
	temp.info->name = user_name;
	temp.refresh();
	return *temp.else_info;
}

void get_all_testmaker(std::vector<testmaker_all_info> &all_info) {
	Testmaker temp;
	MYSQL_RES *res = temp.game_database->get_testmaker();
	MYSQL_ROW row;
	testmaker_all_info temp_all_info;
	while (row = mysql_fetch_row(res)) {
		temp_all_info.info.name = row[0];
		temp_all_info.info.level = std::atoi(row[1]);
		temp_all_info.else_info.problem_num = std::atoi(row[2]);
		all_info.push_back(temp_all_info);
	}
}

bool Testmaker::testmaker_num_get() {
	num_each.clear();
	MYSQL_RES *res = game_database->get_num_need();
	if (res == NULL) {
		std::cout << "risker_exp_need::fail" << std::endl;
		return false;
	}
	else {
		MYSQL_ROW row;
		num_each.push_back(0);//0级没东西，从1级开始
		while (row = mysql_fetch_row(res)) {
			num_each.push_back(std::atoi(row[0]));
			std::cout << std::atoi(row[0]) << std::endl;
		}
		return true;
	}
}

int Testmaker::this_level_need() {
	return num_each[get_level()];
}

int Testmaker::last_level_need() {
	if (get_level() == 0)return 0;
	else return num_each[get_level() - 1];
}