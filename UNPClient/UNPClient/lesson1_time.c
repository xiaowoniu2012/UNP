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
    
    Inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    // conect to server
    
    err_msg("connet socket");
    
    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // read data from server
    
    
    err_msg("read socket");
    while ((readlength = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[readlength] = 0;
        
        if (fputs(recvline, stdout) == EOF) {
            err_sys("fputs server data error");
        }
    }
    
    err_msg("read done.");
    if (readlength <=0) {
        err_sys("read data from server error");
    }
    
    exit(0);
    
    
    
    
}
