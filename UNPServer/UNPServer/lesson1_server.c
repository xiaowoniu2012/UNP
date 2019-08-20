//
//  lesson1_server.c
//  UNPServer
//
//  Created by smart on 2019/8/15.
//  Copyright © 2019 smart. All rights reserved.
//

#include "lesson1_server.h"
#include "time.h"
#include "unp.h"

int server_lesson1(int argc,char **argv) {
    int listenfd, connfd;
    struct sockaddr_in servaddr,client_addr;
    socklen_t clinet_addr_len = sizeof(client_addr);
    char buffer[MAXLINE];
    time_t ticks;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    
    //socket status: closed -> listen
    Listen(listenfd, LISTENQ);
    
    while (1) {
        
        err_msg("server: accepting... \n");
        
        connfd = accept(listenfd, (SA *)&client_addr , &clinet_addr_len);
        
        err_msg("server: accepted \n");
        
//        char *present = inet_ntoa(client_addr.sin_addr);
        //print connected socket
        char connect_ip[16];
        Inet_ntop(AF_INET, &(client_addr.sin_addr), connect_ip, 16);
        printf("connect from ip: %s port: %d \n",connect_ip, ntohs(client_addr.sin_port));
        
        ticks = time(NULL);
        
        snprintf(buffer, sizeof(buffer), "%.24s\r\n",ctime(&ticks));
        
        Write(connfd, buffer, sizeof(buffer));
        
        Close(connfd);
    }
    
    return 1;
    
}
