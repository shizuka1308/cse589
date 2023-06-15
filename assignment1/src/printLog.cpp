/**
 * @printLog
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
 * This contains all the print loggers which will be required in the whole code.
 */

#include "../include/global.h"
#include "../include/logger.h"
extern string my_ip;
extern int my_port_number;
using namespace std;
extern vector<SocketObject> socketlist;

// LOGGER FOR SUCCESS/FAILURE/END
void enter_success(string instruction)
{
    cse4589_print_and_log("[%s:SUCCESS]\n", instruction.c_str());
}

void enter_end(string instruction)
{
    cse4589_print_and_log("[%s:END]\n", instruction.c_str());
    cout << ("\n");
}

void enter_error(string instruction)
{
    cse4589_print_and_log("[%s:ERROR]\n", instruction.c_str());
    enter_end(instruction);
}

// These loggers are for both CLIENT and SERVER
//  This will print the author name alongwith the policy statement
void enter_ip()
{
    cse4589_print_and_log("[IP:SUCCESS]\nIP:%s\n[IP:END]\n", (my_ip).c_str());
}

//  This will print the author name alongwith the policy statement
void enter_author()
{
    cse4589_print_and_log("[AUTHOR:SUCCESS]\nI, kajol, have read and understood the course academic integrity policy.\n[AUTHOR:END]\n");
}

// This will display list of all currently logged in clients
void enter_list()
{
    sort(socketlist.begin(), socketlist.end());
    cse4589_print_and_log("[LIST:SUCCESS]\n");
    int iterator = 0;

    if (iterator < socketlist.size())
    {
        do
        {
            if (socketlist[iterator].status == "logged-in")
            {
                cse4589_print_and_log("%-5d%-35s%-20s%-8d\n", iterator + 1, socketlist[iterator].hostname.c_str(), socketlist[iterator].ip.c_str(), socketlist[iterator].port_num);
            }
            iterator++;
        } while (iterator < socketlist.size());
    }
    cse4589_print_and_log("[LSIT:END]\n");
    cout << ("\n");
}

// This will print the port number the process is listening on
void enter_listen_port()
{
    cse4589_print_and_log("[PORT:SUCCESS]\nPORT:%d\n[PORT:END]\n", my_port_number);
}

void enter_received(string client_ip, string msg)
{
    cse4589_print_and_log("[RECEIVED:SUCCESS]\nmsg from:%s\n[msg]:%s\n[RECEIVED:END]\n", client_ip.c_str(), msg.c_str());
}

void enter_relayed(string from_client_ip, string msg, string to_client_ip)
{
    cse4589_print_and_log("[RELAYED:SUCCESS]\nmsg from:%s, to:%s\n[msg]:%s\n[RELAYED:END]\n", from_client_ip.c_str(), to_client_ip.c_str(), msg.c_str());
}

void enter_statistics()
{
    int iterator = 0;
    sort(socketlist.begin(), socketlist.end());
    cse4589_print_and_log("[STATISTICS:SUCCESS]\n");
    if (iterator < socketlist.size())
    {
        do
        {
            cse4589_print_and_log("%-5d%-35s%-8d%-8d%-8s\n", iterator + 1, socketlist[iterator].hostname.c_str(), socketlist[iterator].num_msg_sent, socketlist[iterator].num_msg_rcv, socketlist[iterator].status.c_str());
            iterator++;
        } while (iterator < socketlist.size());
    }
    cse4589_print_and_log("[STATISTICS:END]\n");
    cout << ("\n");
}

void enter_blocked(string ip)
{
    SocketObject *verytemporary;
    SocketObject *highd = socket_exist_or_not(ip);
    int indicator = !ipValidOrNot(ip) || highd == NULL;
    if (indicator)
    {
        enter_error("BLOCKED");
        return;
    }

    cse4589_print_and_log("[BLOCKED:SUCCESS]\n");
    int iterator = 0;
    if (iterator < highd->blockeduser.size())
    {
        do
        {
            verytemporary = socket_exist_or_not(highd->blockeduser[iterator]);
            if (!(!(verytemporary == NULL)))
            {
                cout << "Print Blocked has some error" << endl;
                return;
            }
            cse4589_print_and_log("%-5d%-35s%-20s%-8s\n", iterator + 1, verytemporary->hostname.c_str(), verytemporary->ip.c_str(), verytemporary->port.c_str());
            iterator++;
        } while (iterator < highd->blockeduser.size());
    }
    cse4589_print_and_log("[BLOCKED:END]\n");
    cout << ("\n");
}
