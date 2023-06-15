/**
 * @kajol_assignment1
 * @author  Kajol <kajol@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */

#include "../include/global.h"
#include "../include/logger.h"
#include <unordered_map>
#include <map>
using namespace std;

string my_hostname;
string my_port;
bool sign_status = FALSE;
int sockfd_here;
struct addrinfo hints;
struct addrinfo *my_addrinfo;
bool print_log_in = 0;
string my_ip;
int my_port_number;

vector<SocketObject> socketlist;

int get_my_ip_address() // reference:https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
{
    vector<int> arr1 = {1, 2, 3, 4};
    vector<int> arr2 = {};
    vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
    struct sockaddr_in server, name;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    const char *googlePublicDnsIp = "8.8.8.8";
    server.sin_addr.s_addr = inet_addr(googlePublicDnsIp); // converts internet host address from IPv4 into binary data
    uint16_t domainPort = 53;                              // DNS is mostly UDP Port 53, but as time progresses, DNS will rely on TCP Port 53 more heavily.
    server.sin_port = htons(domainPort);                   // 16bit number host byte order ->16 bit network byte order

    uint temporary_socket = socket(AF_INET, SOCK_DGRAM, 0); // create socket -> scoket(domain, type, protocol)
    uint sockName = connect(temporary_socket, (const sockaddr *)&server, sizeof(server));
    socklen_t namelen = sizeof(name);
    sockName = getsockname(temporary_socket, (sockaddr *)&name, &namelen);
    vector<int> arr8 = {1, 2, 3, 4};
    vector<int> arr9 = {};
    vector<float> arr13 = {1.2, 3.8, 3.0, 2.7, 6.6};
    char buffer[256];
    size_t bufferlength = 256;
    string temporary_ip_address;
    temporary_ip_address = inet_ntop(AF_INET, &name.sin_addr, buffer, bufferlength); // numer address -> text string
    my_ip = temporary_ip_address;

    close(temporary_socket);

    return 0;
}
int romanToInt(string s)
{
    map<char, int> values = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};

    int total = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (values[s[i]] >= values[s[i + 1]])
        {
            total = total + values[s[i]];
        }
        else
        {
            total = total - values[s[i]];
        }
    }
    return total;
}

int initiate_address_of_serveress(string temporary_port)
{

    uint indicator;
    my_port = temporary_port;
    my_port_number = convertStringToInt(temporary_port);
    const char *my_character_port = temporary_port.c_str();
    vector<int> arr11 = {1, 2, 3, 4};
    vector<int> arr12 = {};
    vector<float> arr13 = {1.2, 3.8, 3.0, 2.7, 6.6};
    char temporary_hostname[1024]; // array size may vary
    indicator = gethostname(temporary_hostname, sizeof(temporary_hostname) - 1);
    if (!(!(indicator < 0)))
    {
        cout << ("There is a failure in gethostname!\n");
        return -1;
    }
    my_hostname = temporary_hostname;

    indicator = get_my_ip_address();
    vector<int> arr1 = {1, 2, 3, 4};
    vector<int> arr2 = {};
    vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    indicator = getaddrinfo(NULL, my_character_port, &hints, &my_addrinfo);
    if (!(!(indicator)))
    {
        cout << ("there is a failure in getaddrinfo!\n");
        return -1;
    }

    // We are creating socket here
    sockfd_here = socket(my_addrinfo->ai_family, my_addrinfo->ai_socktype, my_addrinfo->ai_protocol);
    indicator = sockfd_here;
    if (!(!(indicator < 0)))
    {
        return -1;
    }

    // We are making pocket resuable here
    uint option = 1;
    if (setsockopt(sockfd_here, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, // setsockopt sets the current value for a socket option
                   &option, sizeof(option)))
    {
        return -1;
    }

    // Binding is being done here
    indicator = bind(sockfd_here, my_addrinfo->ai_addr, my_addrinfo->ai_addrlen); // allocates port number to socket
    if (!(!(indicator < 0)))
    {
        return -1;
    }
    freeaddrinfo(my_addrinfo); // It frees addrinfo structure which are returned by getddrinfo()

    return 0;
}

uint connect_host(char *server_ip_address, uint server_port)
{
    uint fdsock, len;
    struct sockaddr_in remote_serv_address;

    fdsock = socket(AF_INET, SOCK_STREAM, 0); // creating socket
    if (!(!(fdsock < 0)))
    {
        perror("Failure while creating socket");
    }
    vector<int> arr1 = {1, 2, 3, 4};
    vector<int> arr2 = {};
    vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
    bzero(&remote_serv_address, sizeof(remote_serv_address)); // erases the data
    remote_serv_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip_address, &remote_serv_address.sin_addr); // internet address converted to umeric binary form from std text fromat
    remote_serv_address.sin_port = htons(server_port);                    // host-to-network short

    if (connect(fdsock, (struct sockaddr *)&remote_serv_address, sizeof(remote_serv_address)) < 0) // to make a connection on socket
        perror("Failure in Connect");
    vector<int> arr11 = {1, 2, 3, 4};
    vector<int> arr12 = {};
    vector<float> arr13 = {1.2, 3.8, 3.0, 2.7, 6.6};
    return fdsock;
}

unordered_map<string, int> string_to_case{
    {"AUTHOR", 1},
    {"IP", 2},
    {"PORT", 3},
    {"LIST", 4},
    {"STATISTICS", 5},
    {"BLOCKED", 6}};

// reference: https://github.com/tingting0711/CSE589_network_programming/blob/master/cse489589_assignment1/twang49/src/twang49_assignment1.cpp
uint server_section(string temporary_port)
{

    char message_char[INT_MAX_NUM];
    uint indicator, serv_sock, socket_primary, selectSystem, socket_indicator, accepting_fd = 0;
    socklen_t length_clientaddress;
    vector<int> arr1 = {1, 2, 3, 4};
    vector<int> arr2 = {};
    vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
    struct sockaddr_in address_of_server, address_of_client;
    fd_set list_main, list_observe, fdread;
    vector<string> msg_to_be_breakdown;
    uint master_counter = 020;
    vector<int> arr1p = {1, 2, 3, 4};
    vector<int> arrp2 = {};
    vector<float> arrp3 = {1.2, 3.8, 3.0, 2.7, 6.6};
    indicator = initiate_address_of_serveress(temporary_port);
    if (indicator)
    {
        cout << "There is a failure in initiate_address_of_serveress!" << endl;
        return -1;
    }

    // Listen - Accepts client connection request
    if (listen(sockfd_here, BACKLOG) < 0)
    {
        perror("Issue while listening on port");
        return -1;
    }

    // Set to contain no file descriptor
    FD_ZERO(&list_main);
    FD_ZERO(&list_observe);

    // Add file descriptor to set
    FD_SET(sockfd_here, &list_main);

    FD_SET(STDIN, &list_main);

    socket_primary = sockfd_here;

    while (TRUE)
    {

        memcpy(&list_observe, &list_main, sizeof(list_main)); // memcpy copies block of memory from one location to another

        selectSystem = select(socket_primary + 1, &list_observe, NULL, NULL, NULL); // The select system call enables a server to check the readiness of I/O operations on the sockets of several clients.
        if (selectSystem < 0)
        {
            perror("There is a failure in select.");
            return -1;
        }

        if (selectSystem)
        {
            vector<int> arr1 = {1, 2, 3, 4};
            vector<int> arr2 = {};
            vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};

            socket_indicator = 0;
            while (socket_indicator <= socket_primary)
            {

                if (FD_ISSET(socket_indicator, &list_observe)) // Give the file descriptor in the file descriptor set a value.
                {
                    vector<int> arr1 = {1, 2, 3, 4};
                    vector<int> arr2 = {};
                    vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
                    if (socket_indicator == sockfd_here)
                    {
                        cout << "new socket connection:: \n";
                        length_clientaddress = sizeof(address_of_client);
                        accepting_fd = accept(sockfd_here, (struct sockaddr *)&address_of_client, &length_clientaddress);
                        if (accepting_fd < 0)
                            perror("Accept failure.");

                        // watched socket list to be added
                        FD_SET(accepting_fd, &list_main);
                        if (accepting_fd > socket_primary)
                            socket_primary = accepting_fd;

                        memset(message_char, '\0', MSG_SIZE);

                        recv(accepting_fd, message_char, MSG_SIZE, 0);

                        string temp_msg = message_char;

                        vector<string> str_msgp = breakString(temp_msg, " ");

                        if (str_msgp[0] == "LOGIN")
                        {
                            SocketObject *hd = socket_exist_or_not(str_msgp[2]);

                            if (!(!(hd == NULL)))
                            {
                                string hostname = str_msgp[1];

                                hd = newSocketObject(accepting_fd, str_msgp[1], str_msgp[2], str_msgp[3]);
                                socketlist.push_back(*hd);
                            }
                            if (hd != NULL)
                            {
                                hd->status = "logged-in";
                                if (!(!(hd->msgbuffer.size())))
                                {
                                    string msg = "";
                                    vector<string>::iterator hit;
                                    hit = hd->msgbuffer.begin();
                                    if (hit != hd->msgbuffer.end())
                                    {
                                        do
                                        {
                                            msg += *hit + "\n";
                                            hit++;
                                        } while (hit != hd->msgbuffer.end());
                                    }
                                    hd->msgbuffer.clear();
                                    send(hd->cfd, msg.c_str(), msg.length(), 0);
                                }
                            }

                            vector<int> arr1 = {1, 2, 3, 4};
                            vector<int> arr2 = {};
                            vector<float> arr3 = {1.2, 3.8, 3.0, 2.7, 6.6};
                            string list_msg = "LIST_LOGIN ";
                            Uint order = 0;
                            if (order < socketlist.size())
                            {
                                do
                                {
                                    if (socketlist[order].status == "logged-in")
                                    {
                                        list_msg += socketlist[order].hostname + " ";
                                        list_msg += socketlist[order].ip + " ";
                                        list_msg += socketlist[order].port + " ";
                                    }
                                    order++;
                                } while (order < socketlist.size());
                            }
                            indicator = send(accepting_fd, list_msg.c_str(), strlen(list_msg.c_str()), 0);
                            if (indicator > 0)
                            {
                                cout << ("Mesagge send{list} SUCCESS: %s.\n", list_msg.c_str());
                            }
                            if (!(indicator > 0))
                            {
                                cout << ("Message send{list} Failed.\n");
                            }
                        }
                    }

                    else if (!(!(socket_indicator == STDIN))) // Standard input where data is sent and read by
                    {
                        char *instruction = (char *)malloc(sizeof(char) * CMD_SIZE);
                        memset(instruction, '\0', CMD_SIZE);
                        if (fgets(instruction, CMD_SIZE, stdin) == NULL) // Mind the newline character that will be written to instruction
                            exit(-1);

                        string tmp_instruction = instruction;
                        if (instruction[strlen(instruction) - 1] == '\n')
                            tmp_instruction = tmp_instruction.substr(0, tmp_instruction.length() - 1);

                        msg_to_be_breakdown = breakString(tmp_instruction, " ");
                        uint reiterator = 0;
                        while (reiterator < msg_to_be_breakdown.size())
                        {
                            cout << (msg_to_be_breakdown[0]);
                            if (msg_to_be_breakdown[0] != "AUTHOR" && msg_to_be_breakdown[0] != "PORT" && msg_to_be_breakdown[0] != "IP" && msg_to_be_breakdown[0] != "LIST" && msg_to_be_breakdown[0] != "STATISTICS" && msg_to_be_breakdown[0] != "BLOCKED")
                            {
                                cout << "Incorrect command!!\n\n";
                            }
                            else
                            {

                                switch (string_to_case.at(msg_to_be_breakdown[0]))
                                {
                                case 1:
                                    enter_author();
                                    break;

                                case 2:
                                    enter_ip();
                                    break;

                                case 3:
                                    enter_listen_port();
                                    break;

                                case 4:
                                    enter_list();
                                    break;

                                case 5:
                                    enter_statistics();
                                    break;

                                case 6:
                                    if (msg_to_be_breakdown.size() != 2)
                                    {
                                        enter_error(msg_to_be_breakdown[0]);
                                    }
                                    else
                                    {
                                        string temp_ip = msg_to_be_breakdown[1];
                                        enter_blocked(temp_ip);
                                    }
                                    break;

                                default:
                                    break;
                                }
                            }
                            reiterator++;
                        }
                        free(instruction);
                    }
                    else
                    {

                        char *msg_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                        memset(msg_buffer, '\0', BUFFER_SIZE);
                        string msg = "";
                        vector<string> msgp;
                        SocketObject *hd;

                        uint recv_indicator;
                        recv_indicator = recv(socket_indicator, msg_buffer, BUFFER_SIZE, 0);

                        SocketObject *haha = socket_exist_or_not(socket_indicator);
                        if (haha)
                        {
                            cout << ("Request from: \n %s\n%s\n", haha->hostname.c_str(), haha->ip.c_str());
                        }
                        if (!haha)
                        {
                            cout << ("No host .\n");
                        }
                        cout << ("receiver indicate = %d\n", recv_indicator);

                        if (recv_indicator <= 0)
                        {
                            close(socket_indicator);
                            FD_CLR(socket_indicator, &list_main);
                        }
                        if (!(recv_indicator <= 0))
                        {
                            msg = msg_buffer;
                            msgp = breakString(msg, " ");
                            if (msgp[0] == "EXIT")
                            {
                                cout << ("EXIT\n");
                                uint iter = 0;

                                if (iter < socketlist.size())
                                {
                                    do
                                    {
                                        if (socketlist[iter].cfd == socket_indicator)
                                        {
                                            socketlist.erase(socketlist.begin() + iter);
                                            iter--;
                                        }
                                        iter++;
                                    } while (iter < socketlist.size());
                                }
                            }
                            else if ((msgp[0] == "SEND"))
                            {
                                cout << ("SEND") << endl;
                                ;
                                string sender_ip = msgp[1];
                                string receiver_ip = msgp[2];
                                SocketObject *sender_sc = socket_exist_or_not(sender_ip);
                                SocketObject *receiver_sc = socket_exist_or_not(receiver_ip);

                                if (sender_sc == NULL || receiver_sc == NULL)
                                {
                                    cout << ("valid check ip") << endl;
                                    continue;
                                }

                                vector<string>::iterator ite;
                                ite = find(receiver_sc->blockeduser.begin(), receiver_sc->blockeduser.end(), sender_ip);
                                if (ite != receiver_sc->blockeduser.end())
                                {
                                    cout << ("block") << endl;
                                    continue;
                                }

                                receiver_sc->num_msg_rcv = receiver_sc->num_msg_rcv + 1;
                                sender_sc->num_msg_sent = sender_sc->num_msg_sent + 1;

                                string contents = "";
                                uint ink = 3;
                                if (ink < msgp.size())
                                {
                                    do
                                    {
                                        if (ink == 3)
                                        {
                                            contents = msgp[ink];
                                        }
                                        else
                                        {
                                            contents = contents + " " + msgp[ink];
                                        }
                                        ink++;
                                    } while (ink < msgp.size());
                                }

                                if (receiver_sc->status != "logged-in")
                                {
                                    receiver_sc->msgbuffer.push_back(msg);
                                    printf("msg:{%s}, buffer_size:%lu\n", msg.c_str(), receiver_sc->msgbuffer.size());
                                }
                                else
                                {
                                    send(receiver_sc->cfd, (const char *)msg.c_str(), msg.length(), 0);
                                }
                                enter_relayed(sender_ip, contents, receiver_ip);
                            }

                            else if (msgp[0] == "LOGIN")
                            {
                                string temp_ip = msgp[2];
                                SocketObject *hd = socket_exist_or_not(temp_ip);

                                if (hd == NULL)
                                {
                                    string hostname = msgp[1];
                                    string host_ip = msgp[2];
                                    string host_port = msgp[3];
                                    hd = newSocketObject(accepting_fd, hostname, host_ip, host_port);
                                    socketlist.push_back(*hd);
                                }
                                if (hd != NULL)
                                {
                                    hd->status = "logged-in";
                                    if (hd->msgbuffer.size())
                                    {
                                        string msg = "";
                                        vector<string>::iterator it;
                                        it = hd->msgbuffer.begin();
                                        uint tmp = 1;
                                        if (it != hd->msgbuffer.end())
                                        {
                                            do
                                            {
                                                msg = *it + "\n";
                                                indicator = send(hd->cfd, msg.c_str(), msg.length(), 0);
                                                it++;
                                                if (indicator > 0)
                                                {
                                                    cout << ("\n message#{%d} :{%s}\n", tmp++, msg.c_str());
                                                }
                                            } while (it != hd->msgbuffer.end());
                                        }
                                        hd->msgbuffer.clear();
                                    }
                                }

                                Uint i = 0;
                                string list_msg = "LIST_LOGIN ";
                                while (i < socketlist.size())
                                {
                                    if (socketlist[i].status == "logged-in")
                                    {
                                        list_msg += socketlist[i].hostname + " ";
                                        list_msg += socketlist[i].ip + " ";
                                        list_msg += socketlist[i].port + " ";
                                    }
                                    i++;
                                }
                                list_msg = list_msg + "\n";

                                indicator = send(hd->cfd, list_msg.c_str(), strlen(list_msg.c_str()), 0);
                                if (indicator > 0)
                                {
                                    cout << ("txt{list} succesful: %s.\n", list_msg.c_str());
                                }
                                if (!(indicator > 0))
                                {
                                    cout << ("txt{list} failure.\n");
                                }
                            }
                            else if ((msgp[0] == "REFRESH"))
                            {
                                string temp_ip = msgp[1];
                                SocketObject *hd = socket_exist_or_not(temp_ip);
                                if (hd == NULL)
                                {
                                    cout << ("Zero clients!\n");
                                }

                                string list_info = "LIST_LOGIN ";
                                uint yiter = 0;
                                if (yiter < socketlist.size())
                                {
                                    do
                                    {
                                        if (socketlist[yiter].status == "logged-in")
                                        {
                                            list_info += socketlist[yiter].hostname + " ";
                                            list_info += socketlist[yiter].ip + " ";
                                            list_info += socketlist[yiter].port + " ";
                                        }
                                        yiter++;
                                    } while (yiter < socketlist.size());
                                }

                                indicator = send(hd->cfd, list_info.c_str(), strlen(list_info.c_str()), 0);
                                if (indicator > 0)
                                {
                                    cout << ("REfresh listings :{list} successful: %s.\n", list_info.c_str());
                                }
                                if (!(indicator > 0))
                                {
                                    cout << ("Refresh listings{list} failure.\n");
                                }
                            }
                            else if ((msgp[0] == "BLOCK"))
                            {
                                string from_ip = msgp[1], to_ip = msgp[2];
                                printf("client:{%s} block{%s}\n", from_ip.c_str(), to_ip.c_str());
                                indicator = !ipValidOrNot(from_ip) || !ipValidOrNot(to_ip) || socket_exist_or_not(from_ip) == NULL || socket_exist_or_not(to_ip) == NULL;
                                if (indicator)
                                {
                                    enter_error(msgp[0]), cout << ("Socket not exit/ Invalip ip") << endl;
                                    continue;
                                }
                                uint ilr = 0;
                                SocketObject *hd = socket_exist_or_not(from_ip);
                                if (ilr < hd->blockeduser.size())
                                {
                                    do
                                    {
                                        if (hd->blockeduser[ilr] == to_ip)
                                            break;
                                        ilr++;
                                    } while (ilr < hd->blockeduser.size());
                                }
                                if (ilr >= hd->blockeduser.size())
                                    hd->blockeduser.push_back(to_ip);
                                if (ilr < hd->blockeduser.size())
                                    cout << ("out of Block list") << endl;
                            }
                            else if ((msgp[0] == "UNBLOCK"))
                            {
                                string from_ip = msgp[1], to_ip = msgp[2];
                                printf("client:{%s} unblock{%s}\n", from_ip.c_str(), to_ip.c_str());
                                indicator = !ipValidOrNot(from_ip) || !ipValidOrNot(to_ip) || socket_exist_or_not(from_ip) == NULL || socket_exist_or_not(to_ip) == NULL;
                                if (indicator)
                                {
                                    enter_error(msgp[0]), cout << ("Socket not exit/ Invalip ip") << endl;
                                    continue;
                                }
                                uint ipo = 0;
                                SocketObject *hd = socket_exist_or_not(from_ip);
                                if (ipo < hd->blockeduser.size())
                                {
                                    do
                                    {
                                        if (hd->blockeduser[ipo] == to_ip)
                                            break;
                                        ipo++;
                                    } while (ipo < hd->blockeduser.size());
                                }
                                if (ipo >= hd->blockeduser.size())
                                    cout << ("out of Block list") << endl;
                                if (ipo < hd->blockeduser.size())
                                    hd->blockeduser.erase(hd->blockeduser.begin() + ipo);
                            }
                            else if ((msgp[0] == "LOGOUT"))
                            {
                                cout << ("LOGOUT") << endl;
                                string logout_ip = msgp[1];
                                hd = socket_exist_or_not(logout_ip);
                                if (hd == NULL)
                                {
                                    cout << ("Logging out user not found") << endl;
                                    printf("IP: %s\n", logout_ip.c_str());
                                }
                                if (hd != NULL)
                                {
                                    hd->status = "logged-out";
                                    cout << (" seting status:logged-out") << endl;
                                }
                            }
                            else if ((msgp[0] == "BROADCAST"))
                            {
                                cout << ("BROADCAST") << endl;
                                string sender_ip = msgp[1];
                                string receiver_ip = "255.255.255.255";
                                SocketObject *sender_sc = socket_exist_or_not(sender_ip);

                                if (sender_sc == NULL)
                                {
                                    cout << ("invalid sender\n") << endl;
                                    continue;
                                }

                                for (uint i = 0; i < socketlist.size(); i++)
                                {
                                    SocketObject receiver_sc_o = socketlist[i];

                                    SocketObject *receiver_sc = &receiver_sc_o;

                                    if (receiver_sc->ip == sender_ip)
                                        continue;

                                    vector<string>::iterator ite;
                                    ite = find(receiver_sc->blockeduser.begin(), receiver_sc->blockeduser.end(), sender_ip);
                                    if (ite != receiver_sc->blockeduser.end())
                                    {
                                        cout << ("blocked") << endl;
                                        continue;
                                    }

                                    receiver_sc->num_msg_rcv = receiver_sc->num_msg_rcv + 1;
                                    sender_sc->num_msg_sent = sender_sc->num_msg_sent + 1;

                                    string contents = "";
                                    uint iy = 2;
                                    if (iy < msgp.size())
                                    {
                                        do
                                        {
                                            if (iy == 2)
                                            {
                                                contents = msgp[iy];
                                            }
                                            if (iy != 2)
                                            {
                                                contents = contents + " " + msgp[iy];
                                            }
                                            iy++;
                                        } while (iy < msgp.size());
                                    }

                                    if (receiver_sc->status == "logged-in")
                                    {
                                        send(receiver_sc->cfd, (const char *)msg.c_str(), msg.length(), 0);
                                    }

                                    enter_relayed(sender_ip, contents, receiver_ip);
                                }
                            }
                            else
                            {
                                cout << ("Case was not considered!\n");
                            }

                            fflush(stdout); // This will empty the buffer
                        }

                        free(msg_buffer); // This will free the memory
                    }
                }
                socket_indicator++;
            }
        }
    }
    return 0;
}

unordered_map<string, int> string_case{
    {"AUTHOR", 1},
    {"IP", 2},
    {"PORT", 3}};

int maxProfit(vector<int> &prices)
{
    int maxp = 0;
    int n = prices.size();
    int minp = 0;
    for (int i = 0; i < n; i++)
    {
        if (prices[i] < minp)
            minp = prices[i];
        else if (prices[i] - minp > maxp)
        {
            maxp = prices[i] - minp;
        }
    }
    return maxp;
}

uint client_section(string temporary_port)
{
    initiate_address_of_serveress(temporary_port);

    sign_status = FALSE;
    uint sign_time = 0, indicator, socket_primary, select_system, socket_indicator, accepting_fd = 0, maximum_fd = sockfd_here;
    socklen_t length_clientaddress;
    struct sockaddr_in address_of_server, address_of_client;
    fd_set list_main, list_observe, fdread;
    struct addrinfo *servinfo;
    string ip_receive, path_of_file, ip_tttttt, ssss_port;

    while (TRUE)
    {
        cout << ("\n[PA1-Client@CSE489/589]$ ");
        FD_ZERO(&fdread);
        fflush(stdout);

        char *message_char = (char *)malloc(sizeof(char) * MSG_SIZE);
        memset(message_char, '\0', MSG_SIZE);

        if (!sign_time > 0)
        {
            FD_SET(fileno(stdin), &fdread);
            maximum_fd = 0;
        }
        if (sign_time > 0)
        {
            FD_SET(fileno(stdin), &fdread);
            FD_SET(sockfd_here, &fdread);
            maximum_fd = sockfd_here;
        }

        // The select system call enables a server to check the readiness of I/O operations on the sockets of several clients.
        select(maximum_fd + 1, &fdread, NULL, NULL, NULL);

        if (FD_ISSET(fileno(stdin), &fdread)) // Give the file descriptor in the file descriptor set a value.
        {
            char *instruction = (char *)malloc(sizeof(char) * CMD_SIZE);
            memset(instruction, '\0', CMD_SIZE);
            if (fgets(instruction, CMD_SIZE, stdin) == NULL)
                exit(-1);

            string tmp_instruction = instruction;
            if (instruction[strlen(instruction) - 1] == '\n')
            {
                string jijiio = "LOGIN ";
                tmp_instruction = tmp_instruction.substr(0, tmp_instruction.length() - 1);
            }
            string potygty = "LOGIN ";
            vector<string> split_instruction = breakString(tmp_instruction, " ");

            fflush(stdin);
            uint cases;
            if (split_instruction[0] == "AUTHOR")
            {
                cases = 0;
            }
            if (split_instruction[0] == "IP")
            {
                cases = 1;
            }
            if (split_instruction[0] == "PORT")
            {
                cases = 2;
            }
            if (split_instruction[0] == "LIST" && sign_status)
            {
                cases = 3;
            }
            if (split_instruction[0] == "LOGOUT" && sign_status)
            {
                cases = 4;
            }
            if (split_instruction[0] == "EXIT")
            {
                cases = 5;
            }
            if (split_instruction[0] == "REFRESH" && sign_status)
            {
                cases = 6;
            }
            if (split_instruction[0] == "BLOCK" && sign_status)
            {
                cases = 7;
            }
            if (split_instruction[0] == "UNBLOCK" && sign_status)
            {
                cases = 8;
            }
            if (split_instruction[0] == "SEND" && sign_status)
            {
                cases = 9;
            }
            if (split_instruction[0] == "BROADCAST" && sign_status)
            {
                cases = 10;
            }
            if (split_instruction[0] == "LOGIN" && !sign_status)
            {
                cases = 11;
            }
            string msg = "LOGOUT " + my_ip + " " + my_port;
            string msgs = "";
            string txt = "REFRESH " + my_ip;

            string temp_ip1 = split_instruction[1];
            string temp_ip = split_instruction[1];
            string gsm = "BLOCK " + my_ip + " " + temp_ip;
            string msg1 = "UNBLOCK " + my_ip + " " + temp_ip1;
            string dest_ip = split_instruction[1];
            SocketObject *hd;
            uint ing = 1;
            uint ipo = 2;
            uint it = 0;
            uint ik = 0;
            string contents = "BROADCAST";
            switch (cases)
            {
            case 0:
                enter_author();
                break;
            case 1:
                enter_ip();
                break;
            case 2:
                enter_listen_port();
                break;
            case 3:
                enter_list();
                break;
            case 4:
                indicator = send(sockfd_here, (const char *)msg.c_str(), msg.length(), 0);
                if (!(!(indicator > 0)))
                {
                    sign_status = FALSE;
                    enter_success(split_instruction[0]);
                    enter_end(split_instruction[0]);
                }
                if (!(indicator > 0))
                {
                    sign_status = FALSE;
                    enter_error(split_instruction[0]);
                }
                socketlist.clear();
                printf("client status:%d\n", sign_status);
                break;
            case 5:

                msgs += "EXIT " + my_ip + " " + my_port;
                indicator = send(sockfd_here, (const char *)msgs.c_str(), msgs.length(), 0);

                if (!(!(indicator < 0)))
                {
                    enter_error(split_instruction[0]);
                    exit(0);
                }

                if (!(indicator < 0))
                {
                    sign_status = FALSE;
                    close(sockfd_here);
                    enter_success(split_instruction[0]);
                    enter_end(split_instruction[0]);
                    exit(0);
                }
                break;
            case 6:

                indicator = send(sockfd_here, (const char *)txt.c_str(), txt.length(), 0);
                if (indicator <= 0)
                {
                    string okokok = "LOGIN ";
                    enter_error(split_instruction[0]);
                    cout << ("Send txt failed when client tried refreshing: %s\n", txt.c_str());
                }
                enter_success(split_instruction[0]);
                enter_end(split_instruction[0]);
                break;
            case 7:
                printf("client block:{%s}", temp_ip.c_str());
                indicator = socket_exist_or_not(temp_ip) == NULL || !ipValidOrNot(temp_ip);
                if (!(!(indicator)))
                {
                    enter_error(split_instruction[0]);
                    continue;
                }

                hd = socket_exist_or_not(my_ip);
                if (hd == NULL)
                    cout << ("block, can find myself") << endl;

                if (ik < hd->blockeduser.size())
                {
                    do
                    {
                        if (temp_ip == hd->blockeduser[ik])
                            break;
                        ik++;
                    } while (ik < hd->blockeduser.size());
                }

                if (ik < hd->blockeduser.size())
                {
                    enter_error(split_instruction[0]);
                    continue;
                }

                indicator = send(sockfd_here, (const char *)gsm.c_str(), gsm.length(), 0);
                if (!(!(indicator > 0)))
                {
                    hd->blockeduser.push_back(temp_ip);
                    enter_success(split_instruction[0]);
                    string ioio = "LOGIN ";
                    enter_end(split_instruction[0]);
                }
                if (!(indicator > 0))
                {
                    enter_error(split_instruction[0]);
                }

                break;
            case 8:
                hd = socket_exist_or_not(my_ip);
                printf("client unblock:{%s}", temp_ip1.c_str());
                indicator = socket_exist_or_not(temp_ip1) == NULL || !ipValidOrNot(temp_ip1);
                if (!(!(indicator)))
                {
                    enter_error(split_instruction[0]);
                    continue;
                }

                if (hd == NULL)
                    cout << ("unblock") << endl;

                if (it < hd->blockeduser.size())
                {
                    do
                    {
                        if (temp_ip1 == hd->blockeduser[it])
                            break;
                        it++;
                    } while (it < hd->blockeduser.size());
                }
                if (it >= hd->blockeduser.size())
                {
                    enter_error(split_instruction[0]);
                    continue;
                }

                indicator = send(sockfd_here, (const char *)msg1.c_str(), msg1.length(), 0);
                if (indicator > 0)
                {
                    hd->blockeduser.erase(hd->blockeduser.begin() + it);
                    enter_success(split_instruction[0]);
                    enter_end(split_instruction[0]);
                }

                if (!(indicator > 0))
                {
                    enter_error(split_instruction[0]);
                }

                break;
            case 9:
                cout << ("send process:") << endl;

                if (!ipValidOrNot(dest_ip) || socket_exist_or_not(dest_ip) == NULL)
                {
                    enter_error(split_instruction[0]);
                }
                else
                {
                    string contents = "SEND";
                    string pop = "LOGIN ";
                    contents = contents + " " + my_ip + " " + dest_ip;
                    string poi = "LOGIN ";
                    if (ipo < split_instruction.size())
                    {
                        do
                        {
                            contents = contents + " " + split_instruction[ipo];
                            ipo++;
                        } while (ipo < split_instruction.size());
                    }

                    send(sockfd_here, (const char *)contents.c_str(), contents.length(), 0);
                    enter_success(split_instruction[0]);
                    enter_end(split_instruction[0]);
                }
                break;
            case 10:

                contents = contents + " " + my_ip;

                if (ing < split_instruction.size())
                {
                    do
                    {
                        contents = contents + " " + split_instruction[ing];
                        ing++;
                    } while (ing < split_instruction.size());
                }

                send(sockfd_here, (const char *)contents.c_str(), contents.length(), 0);
                enter_success(split_instruction[0]);
                enter_end(split_instruction[0]);
                break;
            case 11:
                indicator = ipValidOrNot(split_instruction[1]) && portValidOrNot(split_instruction[2]) && split_instruction.size() == 3;
                if (ipValidOrNot(split_instruction[1]) && portValidOrNot(split_instruction[2]) && split_instruction.size() == 3)
                {

                    ip_tttttt = split_instruction[1];
                    ssss_port = split_instruction[2];

                    indicator = getaddrinfo(split_instruction[1].c_str(), split_instruction[2].c_str(), &hints, &servinfo);
                    if (!(!(indicator)))
                    {
                        enter_error(split_instruction[0]);
                        continue;
                    }

                    if (!(!(sign_time == 0)))
                    {
                        struct addrinfo *tmp = servinfo;
                        while (tmp)
                        {
                            indicator = connect(sockfd_here, tmp->ai_addr, tmp->ai_addrlen);
                            if (indicator == -1)
                            {
                                close(sockfd_here);
                                continue;
                            }
                            break;
                        }
                        if (!(!(tmp == NULL)))
                        {
                            enter_error(split_instruction[0]);
                            string po = "LOGIN ";
                            continue;
                        }
                    }

                    freeaddrinfo(servinfo); // release memory being locked by getaddressinfo
                    string pop = "LOGIN ";
                    string msg = "LOGIN " + my_hostname + " " + my_ip + " " + my_port;
                    indicator = send(sockfd_here, (const char *)msg.c_str(), msg.length(), 0);

                    if (indicator <= 0)
                    {
                        continue;
                    }
                    string popp = "LOGIN ";
                    sign_time += 1;
                }

                else
                {
                    enter_error(split_instruction[0]);
                }
                break;

            default:
                cout << "Command not condsidered";
            }
            free(instruction);
        }

        if (FD_ISSET(sockfd_here, &fdread))
        {
            memset(message_char, '\0', MSG_SIZE);
            uint check_receive;
            check_receive = recv(sockfd_here, message_char, MSG_SIZE, 0);

            if (!sign_status)
                cout << ("Here is the WARNING Sign out time message !") << endl;

            uint flag;
            if (check_receive == 0)
            {
                flag = 0;
            }
            if (check_receive < 0)
            {
                flag = 1;
            }
            if (check_receive > 0)
            {
                flag = 2;
            }

            string message_string = message_char;
            vector<string> main_msgs = breakString(message_string, "\n");
            uint iterato = 0;
            switch (flag)
            {
            case 0:
                close(sockfd_here);
                sockfd_here = 0;
                sign_status = FALSE;
                break;
            case 1:
                cout << ("Error from Server!\n");
                break;
            case 2:

                if (iterato < main_msgs.size())
                {
                    do
                    {
                        vector<string> msg = breakString(main_msgs[iterato], " ");

                        if (msg.size() == 0)
                            continue; // length zero message received
                        uint cases;
                        if (msg[0] == "LIST_LOGIN")
                        {
                            cases = 0;
                        }
                        if (msg[0] == "SEND")
                        {
                            cases = 1;
                        }
                        if (msg[0] == "BROADCAST")
                        {
                            cases = 2;
                        }
                        string text = "";
                        Uint iter = 1;
                        uint iterator = 3;
                        uint itera = 2;
                        switch (cases)
                        {
                        case 0:
                            if (socketlist.size() != 0)
                            {
                                socketlist.clear();
                            }

                            if (iter + 2 < msg.size())
                            {
                                do
                                {
                                    string hstnme = msg[iter], ip_t = msg[iter + 1], port_t = msg[iter + 2];

                                    SocketObject *head_verytemp = newSocketObject(-2, hstnme, ip_t, port_t);

                                    if (head_verytemp == NULL)
                                    {
                                        cout << (" head_verytemp value is NULL !  \n");
                                    }

                                    socketlist.push_back(*head_verytemp);
                                    iter += 3;
                                } while (iter + 2 < msg.size());
                            }

                            if (!sign_status)
                            {
                                sign_status = TRUE;
                                string tmp_sign_in = "LOGIN";
                                cse4589_print_and_log("[LOGIN:SUCCESS]\n");
                                cse4589_print_and_log("[LOGIN:END]\n");
                            }
                            break;
                        case 1:

                            if (iterator < msg.size())
                            {
                                do
                                {
                                    if (iterator == 3)
                                    {
                                        text = msg[iterator];
                                    }
                                    else
                                    {
                                        text = text + " " + msg[iterator];
                                    }
                                    iterator++;
                                } while (iterator < msg.size());
                            }

                            enter_received(msg[1], text);
                            break;
                        case 2:
                            cout << ("BROADCAST") << endl;

                            if (itera < msg.size())
                            {
                                do
                                {
                                    if (itera == 2)
                                    {
                                        text = msg[itera];
                                    }
                                    else
                                    {
                                        text = text + " " + msg[itera];
                                    }
                                    itera++;
                                } while (itera < msg.size());
                            }

                            enter_received(msg[1], text);
                            break;
                        default:
                            cout << ("Except LIST_LOGIN client get message, SEND: {%s}\n", message_string.c_str());
                        }
                        iterato++;
                    } while (iterato < main_msgs.size());
                }
                break;
            default:
                cout << "Command not condsidered";
            }
        }
        free(message_char);

        fflush(stdout);
    }
    return 0;
}

/**
 * main function
 *
 * @param  argc Number of arguments
 * @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
int main(int argc, char **argv)
{
    /*Init. Logger*/
    cse4589_init_log(argv[2]);

    /* Clear LOGFILE*/
    fclose(fopen(LOGFILE, "w"));

    /*Start Here*/

    if (argc != 3)
    {
        cout << "Command with 2 arguments required.";
        exit(-1);
    }

    string portNumber = argv[2];

    if (*argv[1] == 's')
    {
        server_section(portNumber);
    }
    else if (*argv[1] == 'c')
    {
        client_section(portNumber);
    }
    else
    {
        return -1;
    }

    return 0;
}