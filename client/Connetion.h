#pragma once
#include <WINSOCK2.H>
#include <STDIO.H>
#include<WS2tcpip.h>
#include<string>
#pragma  comment(lib,"ws2_32.lib")
#define MAX_NAME_SIZE 20
typedef struct Info_Pack {
	int type;
	int score;
	char name[MAX_NAME_SIZE + 2];
	Info_Pack() {
		type = 0x1;//Connetion::UNKNOWN_TYPE;
		score = 0;
		memset(name, 0, sizeof(name));
	}
	void set_name(const char *s) {
		memset(name, 0, sizeof(name));
		if (strlen(s) > MAX_NAME_SIZE)printf("set_name:too big\n");
		for (int i = 0; i < strlen(s); i++) {
			name[i] = s[i];
		}
	}
	void set_name(std::string s) {
		memset(name, 0, sizeof(name));
		if (s.size() > MAX_NAME_SIZE)printf("set_name:too big\n");
		for (int i = 0; i < s.size(); i++) {
			name[i] = s[i];
		}
	}
}Info_Pack;
typedef struct users_pack {
	int number;
	char user_names[100][MAX_NAME_SIZE];
}Users_Pack;
class Connetion
{
private:
	SOCKET sclient;
	sockaddr_in serAddr;
	int server_port =6888;//�������˿ںţ������޸�
	char *server_ip = (char *)"39.106.65.214";//ip��ַ�������޸�
public:
	static const int UNKNOWN_TYPE = 0x0;
	static const int ASK_TYPE = 0x1;//ѯ�ʵ�½��ID
	static const int NAME_TYPE = 0x2;//ID
	static const int ONLINE_TYPE = 0x3;//��½ʱ����˷����Ѿ����ߣ�����
	static const int OFFLINE_TYPE = 0x4;//����˷��͵�ǰ������

	static const int BUMP_TYPE = 0x5;//������

	static const int THREAD_TYPE = 0x6;//�������ͷ���һ������̣߳��ͻ��˷�
	static const int KILL_TYPE = 0X7;//��¼��ռ��ɱ�źţ�ֻ�з������ᷢ
	static const int FORCE_TYPE = 0x8;
	static const int SEEONLINE_TYPE = 0x9;//��ѯ����Щ�����ߵ��ź�
	static const int COLLID_TYPE = 0X10;
	static const int CHALLEGE_TYPE = 0x11;
	static const int ACCEPT_TYPE = 0x12;
	static const int REFUSE_TYPE = 0x13;
	static const int IMACC_TYPE = 0x14;
	static const int BUSY_TYPE = 0x15;
	static const int END_TYPE = 0x16;
	static const int FREE_TYPE = 0x17;
	static const int pack_size = sizeof(Info_Pack);
	Connetion();
	~Connetion();
	bool Connect_to_Server();
	Info_Pack Receive_Info_Pack();
	Users_Pack Receive_Users_Pack();
	void Send_Info_Pack(Info_Pack tp);
	void send_name(std::string user_name);
	void send_thread(std::string user_name);
	void send_force(std::string user_name);
	void send_bump(std::string user_name);
	void send_online();
	void send_challege(std::string user_name);
	void send_accept(std::string user_name);
	void send_refuse(std::string user_name);
	void send_end(std::string user_name, int __time_use);
	void send_free();
};



