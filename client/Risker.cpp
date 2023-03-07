#include "Risker.h"



Risker::Risker()
{
	else_info = new risker_info();
	own_table = Risker_table;
	risker_exp_get();
}


Risker::~Risker()
{
	delete else_info;
}

bool Risker::refresh() {
	MYSQL_ROW row = game_database->read_data(info->name, own_table);
	if (row == NULL) {
		//不存在时会返回空row
		std::cout << "Risker::refresh failed" << std::endl;
		return false;
	}
	else {
		else_info->exp = std::atoi(row[1]);
		else_info->checkpoints = std::atoi(row[2]);
		return true;
	}
}

bool Risker::risker_register(std::string temp_name, std::string pass_word) {
	if (register_name(temp_name, type_risker, pass_word));
	else return false;
	if (game_database->insert_new(temp_name, own_table)) {
		std::cout << "Risker::注册成功" << std::endl;
		refresh();//默认值导入
		return true;
	}
	else {
		std::cout << "Risker::注册失败" << std::endl;
		return false;
	}
}

void Risker::update_exp(int new_val) {
	if (new_val >= exp_each[get_level()]) {
		add_level();
	}
	if (game_database->update_something(info->name, own_table, "exp", new_val)) {
		std::cout << "Risker::修改成功" << std::endl;
		refresh();
	}
	else {
		std::cout << "Risker::修改失败" << std::endl;
	}
}
void Risker::add_exp() {
	update_exp(else_info->exp + 1);
}
void Risker::update_checkpoints(int new_val) {
	if (game_database->update_something(info->name, own_table, "checkpoints", new_val)) {
		std::cout << "Risker::修改成功" << std::endl;
		refresh();
	}
	else {
		std::cout << "Risker::修改失败" << std::endl;
	}
}
void Risker::add_checkpoints() {
	update_checkpoints(else_info->checkpoints + 1);
}
bool Risker::risker_login(const std::string user_name) {
	if (Player_login(user_name));
	else return false;
	return (refresh());
}
int Risker::get_exp() {
	return else_info->exp;
}
int Risker::get_checkpoints() {
	return else_info->checkpoints;
}

void Risker::risker_get_word(int len, std::vector<std::string>&word_vector) {
	//std::vector<std::string>word_vector;//重定义自动不需清空
	MYSQL_RES * res = game_database->database_get_word(len);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) {
		word_vector.push_back(row[0]);
	}
	//return word_vector;
}

risker_info Risker::get_risker_info() {
	return *else_info;
}

risker_info getriskerinfobyname(std::string user_name) {
	Risker temp;
	temp.info->name = user_name;
	temp.refresh();
	return *temp.else_info;
}

void get_all_risker(std::vector<risker_all_info> &all_info) {
	Risker temp;
	MYSQL_RES *res = temp.game_database->get_risker();
	MYSQL_ROW row;
	risker_all_info temp_all_info;
	while (row = mysql_fetch_row(res)) {
		temp_all_info.info.name = row[0];
		temp_all_info.info.level = std::atoi(row[1]);
		temp_all_info.else_info.exp = std::atoi(row[2]);
		temp_all_info.else_info.checkpoints = std::atoi(row[3]);
		all_info.push_back(temp_all_info);
	}
}

bool Risker::risker_exp_get() {
	exp_each.clear();
	MYSQL_RES *res = game_database->get_exp_need();
	if (res == NULL) {
		std::cout << "risker_exp_need::fail" << std::endl;
		return false;
	}
	else {
		MYSQL_ROW row;
		exp_each.push_back(0);//0级没东西，从1级开始
		while (row = mysql_fetch_row(res)) {
			exp_each.push_back(std::atoi(row[0]));
			std::cout << std::atoi(row[0]) << std::endl;
		}
		return true;
	}
}

int Risker::this_level_need() {
	return exp_each[get_level()];
}

int Risker::last_level_need() {
	if (get_level() == 0)return 0;
	else return exp_each[get_level() - 1];
}

bool Risker::risker_updatename(std::string temp_name, std::string new_name) {
	update_name(temp_name, new_name);
	if (game_database->update_something(temp_name, own_table, "name", new_name)) {
		std::cout << "Risker::修改成功" << std::endl;
		refresh();
	}
	else {
		std::cout << "Risker::修改失败" << std::endl;
	}
	return true;
}