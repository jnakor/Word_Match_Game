#include "info.h"
#include "Server.h"
map<string,int>name_to_fd;
map<int,string>fd_to_name;
map<string,int>name_to_thread;
int handle(int connfd);
void refresh_kick_ass();
int kdpfd;
int online[MAXEPOLLSIZE]={0};
int bump_chance[MAXEPOLLSIZE]={0};
int busy_acc[MAXEPOLLSIZE]={0};
struct epoll_event ev;
struct epoll_event events[MAXEPOLLSIZE];
void insert_people(std::string name,int fd){
    name_to_fd.insert(std::pair<string, int>(name, fd));
    fd_to_name.insert(std::pair<int, string>(fd,name));
    online[fd]=1;
    bump_chance[fd]=1;
    busy_acc[fd]=0;
}
bool del_people(int del_fd){
    std::string del_name=fd_to_name[del_fd];
    if(name_to_fd[del_name]==del_fd){
        online[del_fd]=0;
        name_to_fd.erase(del_name);
        fd_to_name.erase(del_fd);
	    std::cout<<"del thread:"<<del_name<<" fd:"<<name_to_thread[del_name]<<std::endl;
        name_to_thread.erase(del_name);
        return true;
    }
    else{
        std::cout<<"del nothing"<<std::endl;
        return false;
    }
}

int main(int argc, char **argv)
{
    int servPort =Server_Port;
    int listenq = 1024;
    int listenfd, connfd, nfds, n, nread, curfds,acceptCount = 0;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
    {
        perror("setrlimit error");
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servaddr.sin_port = htons (servPort);
    listenfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (listenfd == -1) {
        perror("can't create socket file");
        return -1;
    }
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (setnonblocking(listenfd) < 0) {
        perror("setnonblock error");
    }
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) == -1) 
    {
        perror("bind error");
        return -1;
    } 
    if (listen(listenfd, listenq) == -1) 
    {
        perror("listen error");
        return -1;
    }

   
    kdpfd = epoll_create(MAXEPOLLSIZE);
    cout<<"epoll handle"<<kdpfd<<endl;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listenfd;
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) 
    {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
        return -1;
    }
    curfds = 1;
    printf("epollserver startup,port %d, max connection is %d, backlog is %d\n", servPort, MAXEPOLLSIZE, listenq);

    //心跳踢人线程启动
    std::thread bump_thread(refresh_kick_ass);
    bump_thread.detach();

    for (;;) {
        /* 等待有事件发生 */
        nfds = epoll_wait(kdpfd, events, curfds, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }
        /* 处理所有事件 */
        for (n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == listenfd) 
            {
                connfd = accept(listenfd, (struct sockaddr *)&cliaddr,&socklen);
                if (connfd < 0) 
                {
                    perror("accept error");
                    continue;
                }
		        else{
		            printf("%d connected\n",connfd);
		        }

                printf( "accept form %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
                if (curfds >= MAXEPOLLSIZE) {
                    fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
                    close(connfd);
                    continue;
                } 
                if (setnonblocking(connfd) < 0) {
                    perror("setnonblocking error");
                }
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, connfd, &ev) < 0)
                {
                    fprintf(stderr, "add socket '%d' to epoll failed: %s\n", connfd, strerror(errno));
                    return -1;
                }
                curfds++;
                continue;
            } 
            // 处理客户端请求
            if (handle(events[n].data.fd) < 0) {
                epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd,&ev);
                if(online[events[n].data.fd]==1)
                {
                    if(del_people(events[n].data.fd)){
			            curfds--;
		            }
                }
            }
        }
    }
    close(listenfd);
    return 0;
}
int handle(int connfd) {
    int nread;
    info buf;
    nread = read(connfd, (char *)&buf, MAXLINE);
    if (nread == 0) {
        printf("client close the connection %d\n",connfd);
        close(connfd);
        return -1;
    } 
    if (nread < 0) {
        perror("read error ");
	    printf(" %d ",connfd);
        close(connfd);
        return -1;
    }
    switch (buf.type)
    {
    case NAME_TYPE:{
        if(name_to_fd.size()==0||name_to_fd.find(buf.name)==name_to_fd.end())
        {
            insert_people(buf.name,connfd);
            send_control(connfd,OFFLINE_TYPE);
        }
        else{
            send_control(connfd,ONLINE_TYPE);
        }
        break;
    }
    case Thread_TYPE:{
	    printf("get_thread\n");
        name_to_thread.insert(std::pair<string, int>(buf.name, connfd));
        break;
    }
    case FORCE_TYPE:{
	    printf("get_force\n");
        if(name_to_fd.size()!=0&&(name_to_fd.find(buf.name)!=name_to_fd.end())){
            if(name_to_thread.size()!=0&&(name_to_thread.find(buf.name)!=name_to_thread.end())){
                //在线者已经挂上监听线程
                send_control(name_to_thread[buf.name],KILL_TYPE);
                del_people(name_to_fd[buf.name]);
	            printf("send kill\n");
                insert_people(buf.name,connfd);
                send_control(connfd,OFFLINE_TYPE);
            }
            else{//对方也正在登录,但比自己快
                send_control(connfd,COLLID_TYPE);//冲突登录，退避
            }
        }
        else{
            insert_people(buf.name,connfd);
            send_control(connfd,OFFLINE_TYPE);
        }
	    break;
    }
    case BUMP_TYPE:{//客户端心跳包
        bump_chance[name_to_fd[buf.name]]=1;
	    break;
    }
    case SEEONLINE_TYPE:{
        Users_Pack tp;
        tp.number=name_to_fd.size()>100? 100:name_to_fd.size();
        int i=0;
        for(auto ptr=name_to_fd.begin();i<tp.number;ptr++,i++){
            set_str(tp.user_names[i],ptr->first);
        }
        send_Users_Pack(connfd,&tp);
	    break;
    }
    case CHALLEGE_TYPE:{
        //主sk发送
        string starter_name=fd_to_name[connfd];
        string receiver_name=buf.name;
	busy_acc[name_to_fd[starter_name]]=1;
	if(name_to_fd.count(buf.name)==0){
	  send_control(name_to_thread[starter_name],OFFLINE_TYPE);	
	  busy_acc[name_to_fd[starter_name]]=0;
	}
        else if(busy_acc[name_to_fd[receiver_name]]==1){
            send_control(name_to_thread[starter_name],BUSY_TYPE);
	    busy_acc[name_to_fd[starter_name]]=0;
        }
        else{
	    busy_acc[name_to_fd[receiver_name]]=1;
            send_control_withname(name_to_thread[receiver_name],CHALLEGE_TYPE,starter_name);
        }
        break;
    }
    case ACCEPT_TYPE:{
        string starter_name=fd_to_name[connfd];
        string receiver_name=buf.name;
	busy_acc[name_to_fd[starter_name]]=1;
        send_control(name_to_thread[receiver_name],ACCEPT_TYPE);
        break;
    }
    case REFUSE_TYPE:{
        string starter_name=fd_to_name[connfd];
        string receiver_name=buf.name;
        //变为空闲
        busy_acc[name_to_fd[starter_name]]=0;
        busy_acc[name_to_fd[receiver_name]]=0;
        send_control(name_to_thread[receiver_name],REFUSE_TYPE);
        break;
    }
    case END_TYPE:{
    	string starter_name=fd_to_name[connfd];
	string receiver_name=buf.name;
	int starter_score=buf.score;
	send_end(name_to_thread[receiver_name],starter_score);
	break;
    }
    case FREE_TYPE:{
	busy_acc[connfd]=0;
	break;
    }
    default:
        break;
    }   
    return 0;
}
void refresh_kick_ass(){
    //如果客户端掉线了，比如崩溃，断电，服务器可能会以为还在
    //此时由于这些sockfd删除之前并不会被新的占用，所以不需要上锁
    while(1){
        sleep(300);//60s查一次
	for(auto ptr=name_to_fd.begin();ptr!=name_to_fd.end();ptr++){
	   send_control(name_to_thread[ptr->first],BUMP_TYPE);	
	   perror("bump to\n");
	}
	sleep(60);
        for(auto ptr=name_to_fd.begin();ptr!=name_to_fd.end();ptr++){
            if(bump_chance[ptr->second]==0)//死掉了
            {
		        printf("dead\n");
                del_people(ptr->second);
            }
        }
    }
}
