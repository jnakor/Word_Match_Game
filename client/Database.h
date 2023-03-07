#pragma once
#include <WINSOCK2.H>
#include<Windows.h>
#include "mysql.h"
#include<string>
#include<iostream>
#include<stdio.h>
#include<vector>
using std::string;
class Database
{
public:
	MYSQL *con;
	//string dbuser = "player";//自行修改
	//string dbpasswd = "1357984";//自行修改
	//string dbip = "39.106.65.214";//自行修改
	string dbuser = "root";
	string dbpasswd = "123456"; // it must be    changed
	string dbip = "localhost";
	string dbname = "game_database";
	string table_player = "player";
	string table_test_maker = "testmaker";
	string table_risker = "risker";
	string table_word = "wordpool";
	string table_exp = "exp_each";
	string table_password = "passwd";
	string table_num = "num_each";
	Database();
	~Database();
	bool name_exist_check(const string &temp_name);
	bool insert_new_type(const string &new_name, int type);//for player
	bool insert_new(const string &new_name, const std::string &table_name);//for testmaker and risker
	bool insert_passwd(const string &new_name, const std::string &pass_word);
	bool update_something(const string &target_name, const string &table_name, const string &something, const string &new_val);
	bool update_something(const string &target_name, const string &table_name, const string &something, int new_val);
	MYSQL_ROW read_data(const string &user_name, const string &table_name);
	bool insert_newword(const std::string &new_word);
	MYSQL_RES *database_get_word(int len);
	MYSQL_RES *get_risker();
	MYSQL_RES *get_testmaker();
	MYSQL_RES *get_exp_need();
	MYSQL_RES *get_num_need();
};

