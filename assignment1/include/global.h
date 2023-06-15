
#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <algorithm> 
#include <sstream>
#include <string>

#define BACKLOG 5
#define STDIN 0
#define CMD_SIZE 65535
#define MSG_SIZE 65535
#define BUFFER_SIZE 65535
#define INT_MAX_NUM 65535
#define TRUE 1
#define FALSE 0

using namespace std;

//functions
bool numberOrNot(char c);
int fsize(FILE *fp);
int convertStringToInt(string s);
vector<string> breakString(const string str, const string &seperator);

int ipValidOrNot(string ipAddress);
int portValidOrNot(string portNo);

void enter_success(string command);
void enter_end(string command);
void enter_error(string command);

void enter_author();
void enter_ip();
void enter_listen_port();
void enter_list();
void enter_statistics();
void enter_blocked(string ip);
void enter_received(string client_ip, string msg);
void enter_relayed(string from_client_ip, string msg, string to_client_ip);

//****struct Socket************
//reference:https://github.com/jessefjxm/CSE589-Text-Chat-Application/blob/master/src/hwang58_assignment1.cpp
struct SocketObject
{
    int cfd;
    int port_num;
    int num_msg_sent;
    int num_msg_rcv;
    string status; 
    string ip;
    string port;
    string hostname;
    vector<string> blockeduser;
    vector<string> msgbuffer;
    bool operator<(const SocketObject &abc) const 
    {
        return convertStringToInt(port) < convertStringToInt(abc.port);
    }
};

SocketObject* newSocketObject(int cfd, string hostname, string ip, string port);
SocketObject* socket_exist_or_not(string ip, string port);
SocketObject* socket_exist_or_not(string ip);
SocketObject* socket_exist_or_not(int cfd);

typedef unsigned int Uint;
#define HOSTNAME_LEN 128
#define PATH_LEN 256


#endif