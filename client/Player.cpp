#include "Player.h"

Player::Player() :game_database(new Database) {
	info = new player_info();
	player_table = game_database->table_player;
	Testmaker_table = game_database->table_test_maker;
	Risker_table = game_database->table_risker;
	sk = NULL;
}

Player::~Player() {
	delete game_database;
	delete info;
	if (sk != NULL)delete sk;
}
//name_api

bool Player::register_name(std::string temp_name, int type, std::string pass_word) {
	if (exist(temp_name)) {
		//只进行查重检测，合法性由输入框去限制
		return false;
	}
	MD_FIVE hasher;
	if (game_database->insert_new_type(temp_name, type) && game_database->insert_passwd(temp_name, hasher.MD5_HASH(pass_word))) {
		std::cout << "Player::注册成功" << std::endl;
		info->name = temp_name;
		refresh();//默认值导入,这里不进行成功刷新与否检测
		return true;
	}
	else {
		std::cout << "Player::注册失败" << std::endl;
		return false;
	}
}


//get_api
std::string Player::get_name() {
	return info->name;
}
int Player::get_level() {
	return info->level;
}
int Player::get_type() {
	return info->type;
}
player_info Player::get_player_info() {
	return *info;
}

//updata_api
bool Player::update_name(std::string temp_name, std::string new_name) {
	if (exist(new_name)) {
		//只进行查重检测，合法性由输入框去限制
		return false;
	}
	if (game_database->update_something(temp_name, game_database->table_player, "name", new_name)) {
		std::cout << "Player::修改" << std::endl;
		info->name = new_name;
		refresh();//默认值导入,这里不进行成功刷新与否检测
		return true;
	}
	else {
		std::cout << "Player::修改失败" << std::endl;
		return false;
	}
}
void Player::update_level(int new_val) {
	game_database->update_something(info->name, player_table, "level", new_val);
	refresh();
}
void Player::add_level() {
	update_level(info->level + 1);
}
bool Player::refresh() {
	if (!exist(info->name))
	{
		std::cout << "Player::refresh failed" << std::endl;
		return false;
	}
	else {
		MYSQL_ROW row = game_database->read_data(info->name, player_table);
		info->name = row[0];
		info->level = std::atoi(row[1]);
		info->type = std::atoi(row[2]);
		return true;
	}
}
bool Player::Player_login(const std::string user_name) {
	info->name = user_name;
	if (refresh()) {
		return true;
	}
	else {
		std::cout << "Player_login::failed" << std::endl;
		return false;
	}
}

bool exist(std::string  user_name) {
	Player *temp = new Player();
	bool ans = temp->game_database->name_exist_check(user_name);
	delete temp;
	return ans;
}

player_info getplayerinfobyname(std::string user_name) {
	Player *temp = new Player();
	temp->info->name = user_name;
	temp->refresh();
	player_info ans = *(temp->info);
	delete temp;
	return ans;
}

bool check_passwd(const string user_name, string pass_word) {
	Player *temp = new Player();
	temp->info->name = user_name;
	temp->refresh();
	MYSQL_ROW row = temp->game_database->read_data(user_name, temp->game_database->table_password);
	delete temp;
	if (row == NULL)return false;
	else {
		MD_FIVE hasher;
		return hasher.MD5_HASH(pass_word) == row[1];
	}
}

void Player::get_sock(Connetion *__sk) {//父亲不允许调用，只允许孩子调用
	this->sk = __sk;
}

Connetion *Player::get_sockout() {
	return sk;
}