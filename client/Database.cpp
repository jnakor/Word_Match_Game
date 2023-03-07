#include "Database.h"
Database::Database()
{
	std::cout << "Database" << std::endl;
	int rt;
	con = mysql_init((MYSQL*)0);
	if (con != NULL && mysql_real_connect(con, dbip.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname.c_str())) {
			printf("连接数据库成功\n");
			con->reconnect = 1;
			//std::string query = "set names gbk";    //"set names \'GBK\'";
			//rt = mysql_real_query(con, query.c_str(), query.length());
			//if (rt) {
			//	printf("数据库初始化失败: %s !!!\n", mysql_error(con));
			//}
			//else {
			//	printf("数据库初始化成功：%s succeed!\n", query.c_str());
			//}
		}
	}
	else {
		printf("无法连接数据库\n");
	}
}
Database::~Database()
{
	std::cout << "~Database" << std::endl;
}
bool Database::name_exist_check(const std::string &temp_name) {
	int rt;
	MYSQL_RES *res;
	std::string query = "select name from player where binary name=\'" + temp_name + "\'";
	rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("name_exist_check::Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		std::cout << query << "name_exist_check::executed!!\n" << std::endl;
	}
	res = mysql_store_result(con);
	return mysql_num_rows(res);
}
bool Database::insert_new(const std::string &new_name, const std::string &table_name) {
	std::string query = "insert into " + table_name + " (name) values" + " (\'" + new_name + "\');";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("insert_new::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "insert_new::executed!!\n" << std::endl;
		return true;
	}
}
bool Database::insert_new_type(const std::string &new_name, int type) {
	//type 0 for risker,type 1 for testmaker
	string type_str = std::to_string(type);
	std::string query = "insert into " + table_player + " (name,type) values" + " (\'" + new_name + "\'," + type_str + ");";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("insert_new_type::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "insert_new_type::executed!!\n" << std::endl;
		return true;
	}
}
bool Database::update_something(const string &target_name, const string &table_name, const string &something, const string &new_val) {
	std::string query = "UPDATE " + table_name + " SET " + something + "= \'" + new_val + "\' where binary name=\'" + target_name + "\';";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("update_something::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "update_something::executed!!\n" << std::endl;
		return true;
	}
}
bool Database::update_something(const string &target_name, const string &table_name, const string &something, int new_val) {
	std::string query = "UPDATE " + table_name + " SET " + something + "= " + std::to_string(new_val) + " where binary name=\'" + target_name + "\';";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("update_something::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "update_something::executed!!\n" << std::endl;
		return true;
	}
}
MYSQL_ROW Database::read_data(const string &user_name, const string &table_name) {
	std::string query = "select * from " + table_name + " where binary name=\'" + user_name + "\';";
	MYSQL_RES *res;
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("read_data::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "read_data::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		MYSQL_ROW row = mysql_fetch_row(res);
		return row;
	}
}
bool Database::insert_newword(const std::string &new_word) {
	string len = std::to_string(new_word.length());
	std::string query = "insert into " + table_word + " (content,length) values" + " (\'" + new_word + "\'" + "," + len + ");";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("insert_newword::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "insert_newword::executed!!\n" << std::endl;
		return true;
	}
}

MYSQL_RES *Database::database_get_word(int len) {
	string str_len = std::to_string(len);
	std::string query = "select * from " + table_word + " where length=" + str_len + ";";
	MYSQL_RES *res;
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("database_get_word::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "database_get_word::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		return res;
	}
}

MYSQL_RES * Database::get_risker() {
	std::string query = "select a.name,a.level,b.exp,b.checkpoints from " + table_player + " a inner join " + table_risker
		+ " b on a.name=b.name;";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	MYSQL_RES *res;
	if (rt)
	{
		printf("Database::get_risker::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "Database::get_risker::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		return res;
	}
}

MYSQL_RES * Database::get_testmaker() {
	std::string query = "select a.name,a.level,b.num from " + table_player + " a inner join " + table_test_maker
		+ " b on a.name=b.name;";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	MYSQL_RES *res;
	if (rt)
	{
		printf("Database::get_risker::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "Database::get_risker::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		return res;
	}
}

MYSQL_RES* Database::get_exp_need() {
	std::string query = "select exp from " + table_exp + ";";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	MYSQL_RES *res;
	if (rt)
	{
		printf("Database::get_exp_need::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "Database::get_exp_need::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		return res;
	}
}

MYSQL_RES* Database::get_num_need() {
	std::string query = "select num from " + table_num + ";";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	MYSQL_RES *res;
	if (rt)
	{
		printf("Database::get_num_need::Error making query: %s !!!\n", mysql_error(con));
		return NULL;
	}
	else
	{
		std::cout << query << "Database::get_num_need::executed!!\n" << std::endl;
		res = mysql_store_result(con);
		return res;
	}
}

bool Database::insert_passwd(const string &new_name, const std::string &pass_word) {
	std::string query = "insert into " + table_password + " (name,password) values" + " (\'" + new_name + "\'" + ",\'" + pass_word + "\');";
	int rt = mysql_real_query(con, query.c_str(), query.length());
	if (rt)
	{
		printf("insert_passwd::Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		std::cout << query << "insert_passwd::executed!!\n" << std::endl;
		return true;
	}
}