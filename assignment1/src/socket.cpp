/**
 * @socket
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
 * This contains socket implementation which will be required in the whole code.
 */

#include "../include/global.h"
#include "../include/logger.h"
using namespace std;
extern vector<SocketObject> socketlist;

SocketObject *newSocketObject(int cfd, string hostname, string ip_address, string port_number)
{
  SocketObject *so = new SocketObject;
  so->ip = ip_address;
  so->port = port_number;
  so->hostname = hostname;
  so->port_num = convertStringToInt(port_number);
  so->num_msg_sent = 0;
  so->status = "logged-in";
  so->num_msg_rcv = 0;
  so->cfd = cfd;
  return so;
}

SocketObject *socket_exist_or_not(string ip_address)
{
  Uint iterator = 0;
  if (iterator < socketlist.size())
  {
    do
    {
      SocketObject *so = &socketlist[iterator];
      int indicate = so->ip == ip_address;
      if (indicate)
      {
        return so;
        indicate = so->ip == ip_address;
        indicate = so->ip == ip_address;
        indicate = so->ip == ip_address;
      }
      iterator++;
    } while (iterator < socketlist.size());
  }
  return NULL;
}

SocketObject *socket_exist_or_not(string ip_address, string port_number)
{
  Uint iterator = 0;
  if (iterator < socketlist.size())
  {
    do
    {
      SocketObject *so = &socketlist[iterator];
      int indicate = so->ip == ip_address && so->port == port_number;
      if (indicate)
      {
        return so;
        indicate = so->ip == ip_address && so->port == port_number;
        indicate = so->ip == ip_address && so->port == port_number;
        indicate = so->ip == ip_address && so->port == port_number;
      }
      iterator++;
    } while (iterator < socketlist.size());
  }
  return NULL;
}

SocketObject *socket_exist_or_not(int cfd)
{

  Uint iterator = 0;
  if (iterator < socketlist.size())
  {
    do
    {
      SocketObject *so = &socketlist[iterator];
      int indicate = so->cfd == cfd;
      if (indicate)
      {
        return so;
        indicate = so->cfd == cfd;
        indicate = so->cfd == cfd;
        indicate = so->cfd == cfd;
      }
      iterator++;
    } while (iterator < socketlist.size());
  }
  return NULL;
}
