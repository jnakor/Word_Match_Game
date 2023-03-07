#include "Connetion.h"


Connetion::Connetion()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0) {
		printf("WSAStartup failed\n");
	}
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET) {
		printf("invalid socket !");
	}
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(server_port);
	inet_pton(AF_INET, server_ip, &serAddr.sin_addr.S_un.S_addr);
}

bool Connetion::Connect_to_Server() {
	if (::connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error!");
		closesocket(sclient);
		return false;
	}
	else {
		printf("connect success!");
		return true;
	}
}

Info_Pack Connetion::Receive_Info_Pack() {
	Info_Pack tp;
	recv(sclient, (char*)&tp, pack_size, 0);
	return tp;
}
Users_Pack Connetion::Receive_Users_Pack() {
	Users_Pack tp;
	recv(sclient, (char*)&tp, sizeof(Users_Pack), 0);
	return tp;
}
void Connetion::Send_Info_Pack(Info_Pack tp) {
	send(sclient, (char*)&tp, pack_size, 0);
}
void Connetion::send_name(std::string user_name) {
	Info_Pack tp;
	tp.type = NAME_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}
void Connetion::send_thread(std::string user_name) {
	Info_Pack tp;
	tp.type = THREAD_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}
void Connetion::send_force(std::string user_name) {
	printf("send_force\n");
	Info_Pack tp;
	tp.type = FORCE_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}
void Connetion::send_bump(std::string user_name) {
	Info_Pack tp;
	tp.type = BUMP_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}
void Connetion::send_online() {
	Info_Pack tp;
	tp.type = SEEONLINE_TYPE;

	Send_Info_Pack(tp);
}
void Connetion::send_challege(std::string user_name) {
	Info_Pack tp;
	tp.type = CHALLEGE_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}
void Connetion::send_accept(std::string user_name) {
	Info_Pack tp;
	tp.type = ACCEPT_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}

void Connetion::send_refuse(std::string user_name) {
	Info_Pack tp;
	tp.type = REFUSE_TYPE;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}

void Connetion::send_end(std::string user_name, int __score) {
	Info_Pack tp;
	tp.type = END_TYPE;
	tp.score = __score;
	tp.set_name(user_name);

	Send_Info_Pack(tp);
}

void Connetion::send_free() {
	Info_Pack tp;
	tp.type = FREE_TYPE;

	Send_Info_Pack(tp);
}
Connetion::~Connetion()
{
	/*WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0) {
		printf("WSAStartup failed\n");
	}*/
	closesocket(sclient);
	WSACleanup();//???
}