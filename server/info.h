#pragma once
#include<string>
#include<string.h>
#include<memory.h>
#include  <unistd.h>
#include  <sys/types.h>       /* basic system data types */
#include  <sys/socket.h>      /* basic socket definitions */
#include  <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include  <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include<iostream>
#include<map>
#include<string>
#include <thread>
#include<vector>
#define FORCE_TYPE 0x8
#define ONLINE_TYPE 0x3
#define OFFLINE_TYPE 0x4
#define BUMP_TYPE 0x5
#define ASK_TYPE 0x1
#define NAME_TYPE 0x2
#define Thread_TYPE 0x6
#define KILL_TYPE 0x7
#define SEEONLINE_TYPE 0x9
#define COLLID_TYPE 0x10
#define CHALLEGE_TYPE  0x11
#define ACCEPT_TYPE  0x12
#define REFUSE_TYPE  0x13
#define IMACC_TYPE  0x14
#define BUSY_TYPE 0X15
#define END_TYPE 0x16
#define FREE_TYPE 0x17
#define MAX_NAME_SIZE 20 

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;
typedef struct Info_Pack {
	int type;
	int score;
	char name[MAX_NAME_SIZE+2];
	Info_Pack() {
		type = 0x1;//Connetion::UNKNOWN_TYPE;
		score=0;		
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
typedef struct Users_Pack {
	int number;
	char user_names[100][MAX_NAME_SIZE];
}Users_Pack;
void set_str(char *s,std::string v){
	memset(s,0,sizeof(s));
	for(int i=0;i<v.size();i++){
		s[i]=v[i];
	}
}

