#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
#include<errno.h>  //错误
#include "info.h"
#define MAXLINE 10240
#define SER_PORT 6888
int main(int argc,char *argv[]){


    struct sockaddr_in servaddr;
    info buf;

    int sockfd,n;
    char *str;
    char tt[5];

    //if(argc != 2){
       // fputs("usage: ./client message \n ",stderr);
       // exit(1);
    //}

    //str = argv[1];

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,"10.122.210.64",&servaddr.sin_addr);
    // inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    servaddr.sin_port = htons(SER_PORT);

    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
            printf("connet error:%s\n",strerror(errno));
        }   //链接服务器
    cout<<"input_your_name"<<endl;
    char name[10];
    cin>>name;
    while(1){
        //getchar();
        info tp;
       // memset(buf,0,MAXLINE);
        printf("client connet server ...\n");
         //getchar();  //从标准输入  读取数据
        read(sockfd,(char*)&buf,sizeof(buf));
        //write(STDOUT_FILENO,buf.name,sizeof(buf.name));
        if(buf.type==ASK_TYPE){
            set_str(tp.name,name);
            tp.type=NAME_TYPE;
            write(sockfd,(char*)&tp,sizeof(buf));   //把我们的输入，写到服务器
        }
        else if(buf.type==BUMP_TYPE){
            tp.type=BUMP_TYPE;
            set_str(tp.name,"bobo");
            write(sockfd,(char*)&tp,sizeof(buf));
        }
        else {
            set_str(tp.name,"what?");
            write(sockfd,(char*)&tp,sizeof(buf));
        }
    //从服务器读取数据

        printf("Response from server:\n");
        write(STDOUT_FILENO,buf.name,sizeof(buf.name));   //写到标注输出上
        printf("\n");
    }
    
    close(sockfd);
    return 0;

}
