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
#define BASESTATION_ADDR "192.168.1.1"
#define PORT 8080

/*----------Usings------------*/
using namespace std;

/*---------Variables----------*/
int SocketID = 0;
struct sockaddr_in serv_addr; 

/*---------Prototypes---------*/
void Routine(void);
void init(void);
int SendSocket(char* message);
int RecieveSocket(char** message);

int main(int argv, char** argc)
{
    init();
    Routine();
}

void init()
{
    /*-------Initialization-------*/
    //Open TCP socket client
    if ((SocketID = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, BASESTATION_ADDR, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
    }

    for(int i = 0; i<30; i++)
    {
        sleep(2);
        if(connect(SocketID, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
            printf("\nConnection Failed \n"); 
        }
    }
}

void Routine()
{
    char* message = "Hello World";
    char* messageRecv[1024] = {};
    while(true)
    {
        sleep(2);
        SendSocket(message);
        RecieveSocket(messageRecv);
    }
}

int SendSocket(char* message)
{
    send(SocketID, message, strlen(message), 0);  
    return 0; 
}

int RecieveSocket(char** message)
{
    recv(SocketID , &message, 1024, MSG_WAITALL); 
    printf("%s\n",&message ); 
    return 0; 
}
