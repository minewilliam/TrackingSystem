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
//#define BASESTATION_ADDR "192.168.1.1"
#define BASESTATION_ADDR "192.168.243.2"
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
int RecieveSocket(char* message[1024]);

int main(int argv, char** argc)
{
    cout << "Starting..." << endl;
    system("./ServerSim");
    init();
    Routine();
}

void init()
{
    /*-------Initialization-------*/
    //Open TCP socket client
    if ((SocketID = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        cout << "Socket creation error" << endl; 
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    //Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, BASESTATION_ADDR, &serv_addr.sin_addr)<=0)  
    { 
        cout << "Invalid address/ Address not supported " << endl; 
    }

    for(int i = 0; i<10; i++)
    {
        if(connect(SocketID, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
            cout << "Connection Failed" << endl; 
        }
    }
}

void Routine()
{
    char message[] = {"Hello World"};
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

int RecieveSocket(char* message[1024])
{
    recv(SocketID , message, 1024, MSG_WAITALL); 
    cout << (*message) << endl; 
    return 0; 
}