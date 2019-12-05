/**
 * @file main.cpp
 * 
 * @author William Longpré, Étienne Bellerose
 * @brief 
 * @version 0.1
 * @date 2019-11-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/*----------Includes----------*/
#include <math.h>
#include <stdint.h>
#include <iostream>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/*----------Defines-----------*/
//#define ANTENASTATION_ADDR "192.168.1.50"
#define ANTENASTATION_ADDR "192.168.243.2"
#define PORT 8080

/*----------Usings------------*/
using namespace std;

/*---------Variables----------*/
int SocketID = 0;
int server_fd;
struct sockaddr_in serv_addr; 

/*---------Prototypes---------*/
void Routine(void);
void init(void);
int SendSocket(char* message);
int RecieveSocket(char message[1024]);
void CloseSocket(void);

int main(int argv, char** argc)
{
    cout << "Starting..." << endl;
    init();
    Routine();
}

void init()
{
    /*-------Initialization-------*/
    atexit(CloseSocket);
    int opt = 1;
    //Open TCP socket server
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons( PORT ); 

    cout << "Binding to port..." << endl;
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    cout << "Listening..." << endl;
    listen(server_fd, 3);
}

void Routine()
{
    char message[] = {"Hello World"};
    char messageRecv[1024] = {};
    while(true)
    {
        RecieveSocket(messageRecv);
        SendSocket(messageRecv);
    }
}

int SendSocket(char* message)
{
    send(SocketID, message, strlen(message), 0);  
    return 0; 
}

int RecieveSocket(char message[1024])
{
    SocketID = accept(server_fd, (struct sockaddr *)&serv_addr, (socklen_t*)&serv_addr);
    recv(SocketID , message, 1024, MSG_WAITALL); 
    cout << (*message) << endl; 
    return 0; 
}

void CloseSocket()
{
    close(server_fd);
}