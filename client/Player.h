#pragma once
#include<string>
#include<iostream>
#include "Database.h"
//#include "Connetion.h"
#include "MD_FIVE.h"

using std::string;

struct player_info {
	string name;
	int level;
	int type;//0 for player,1 for testmaker
	player_info() {
		name = "";
		level = 0;
		type = 0;
	}
};

class Player
{
private:
	const int max_name_size = 20;
	string player_table;
	bool refresh();
protected:
	string Testmaker_table;
	string Risker_table;
	Database* game_database;
	struct player_info * info;
	bool register_name(std::string temp_name, int type, std::string pass_word);
	bool update_name(std::string temp_name, std::string new_name);
public:
	static const int type_risker = 0;
	static const int type_testmaker = 1;
	Player();
	~Player();
	bool Player_login(const string user_name);
	void update_level(int new_val);
	void add_level();
	string get_name();
	int get_level();
	int get_type();
	player_info get_player_info();
	friend bool exist(std::string  user_name);
	friend player_info getplayerinfobyname(std::string  user_name);
	friend bool check_passwd(const string user_name, string pass_word);
};