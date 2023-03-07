#pragma
#include "info.h"
#define Server_Port 6888
#define MAXEPOLLSIZE 10000
#define MAXLINE 10240
typedef Info_Pack info;
int setnonblocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}
void send_control(int fd,int type){
    info tp;
    tp.type=type;
    write(fd,(char *)&tp, sizeof(tp));
}
void send_end(int fd,int score){
    info tp;
    tp.type=END_TYPE;
    tp.score=score;
    write(fd,(char *)&tp,sizeof(tp));
}
void send_control_withname(int fd,int type,string name){
    info tp;
    tp.type=type;
    set_str(tp.name,name);
    write(fd,(char *)&tp, sizeof(tp));
}
void send_Users_Pack(int fd,Users_Pack *tp){
    write(fd,(char *)tp,sizeof(Users_Pack));
}
