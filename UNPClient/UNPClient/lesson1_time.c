//
//  lesson1_time.c
//  UNPClient
//
//  Created by smart on 2019/8/15.
//  Copyright © 2019 smart. All rights reserved.
//

#include "lesson1_time.h"
#include "unp.h"

int client_lesson1(int argc, char **argv) {
    int sockfd, readlength;
    char recvline[MAXLINE];
    struct sockaddr_in server_addr;
    
    err_msg("create socket");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_sys("socket create error");
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);
    
    // char address to net address
    
    Inet_pton(AF_INET, "172.24.80.21", &server_addr.sin_addr);
    
//    inet_aton("172.24.80.21", &server_addr.sin_addr);
    
    // conect to server
    
    
    err_msg("connet socket");
    
    /*
     // Error checking omitted for expository purposes
     int sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     // Bind to a specific network interface (and optionally a specific local port)
     struct sockaddr_in localaddr;
     localaddr.sin_family = AF_INET;
     localaddr.sin_addr.s_addr = inet_addr("192.168.1.100");
     localaddr.sin_port = 0;  // Any local port will do
     bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr));
     
     // Connect to the remote server
     struct sockaddr_in remoteaddr;
     remoteaddr.sin_family = AF_INET;
     remoteaddr.sin_addr.s_addr = inet_addr(server_ip);
     remoteaddr.sin_port = htons(server_port);
     connect(sockfd, (struct sockaddr *)&remoteaddr, sizeof(remoteaddr));
     */
    
    
    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // read data from server
    
    
    err_msg("read socket");
    static int count = 0;
    while ((readlength = read(sockfd, recvline, MAXLINE)) > 0) {
        ++count;
        recvline[readlength] = 0;
        
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs server data error");
        }
    }
    
    printf("read count is %d \n",count);
    err_msg("read done.");
    if (readlength <=0) {
        err_sys("read data from server error");
    }
    
    exit(0);
    
}

void client_test() {
    int ip;
    char *host = "127.0.0.1";
    // presention to number : char *host to int ip
    if (inet_pton(AF_INET, host, &ip) == 1) {
        err_msg("ip is %d",ip);
    }
    // number to presention : int ip to char *host
    char address[INET_ADDRSTRLEN];
//  INET_ADDRSTRLEN 16 ipv4 len
//  INET6_ADDRSTRLEN 46 ipv6 len
    if (inet_ntop(AF_INET, &ip, address, INET_ADDRSTRLEN) != NULL) {
        err_msg("address is %s",address);
    }
    
}
