#include "../include/simulator.h"
#include <iostream>
#include <vector>
#include <string.h>

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional data transfer
   protocols (from A to B). Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

/********* STUDENTS WRITE THE NEXT SEVEN ROUTINES *********/
#define RTT 25.0
#define CHKSIE 20
#define HOST_A 0
#define HOST_B 1

using namespace std;

int acknowledgmentflag, sequence_A, sequence_B, check = 0, sequence = 0, destination = 0, ready_active = 0, seq_end = 0;
vector<pkt> packets;

struct pkt lasting;
int checksum(struct pkt);

struct pkt *createPacket(struct msg message)
{
  struct pkt *packet = new struct pkt;
  (*packet).seqnum = sequence;
  (*packet).acknum = sequence;
  strcpy((*packet).payload, message.data);
  (*packet).checksum = checksum((*packet));
  return packet;
}

int checksum(struct pkt packet)
{
  char data[CHKSIE];
  strcpy(data, packet.payload);
  int localchecksum = 0;
  int iterator = 0;
  while (iterator < CHKSIE && data[iterator] != '\0')
  {
    localchecksum = localchecksum + data[iterator];
    iterator = iterator + 1;
  }

  localchecksum = localchecksum + packet.seqnum;
  localchecksum = localchecksum + packet.acknum;

  return localchecksum;
}
/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
  packets.push_back(*createPacket(message));
  if (ready_active == 0)
  {
    lasting = packets.at(sequence);
    tolayer3(HOST_A, lasting);
    sequence = sequence + 1;
    starttimer(HOST_A, RTT);
    ready_active = ready_active + 1;
  }
  else if (ready_active < getwinsize())
  {
    lasting = packets.at(sequence);
    tolayer3(HOST_A, lasting);
    sequence = sequence + 1;
    ready_active = ready_active + 1;
  }
  else if (ready_active != 0)
  {
  }
  else if (ready_active > getwinsize())
  {
  }
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
  acknowledgmentflag = 1;

  if (packet.acknum == seq_end + 1)
  {
    seq_end = seq_end + 1;
  }
  else if (packet.acknum == destination + getwinsize())
  {
    destination = destination + getwinsize();
    stoptimer(HOST_A);
    ready_active = 0;
  }
  else if (packet.acknum != seq_end + 1)
  {
  }
  else if (packet.acknum != destination + getwinsize())
  {
  }
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
  for (int ierator = seq_end; ierator < seq_end + getwinsize() && ierator < ready_active; ierator++)
  {
    lasting = packets.at(ierator);
    tolayer3(HOST_A, lasting);
  }
  starttimer(HOST_A, RTT);
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
  acknowledgmentflag = 1;
  sequence_A = 0;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
  if (checksum(packet) == packet.checksum)
  {
    if (sequence_B == packet.seqnum)
    {
      tolayer5(HOST_B, packet.payload);
      pkt *ACK = new struct pkt;
      (*ACK).acknum = sequence_B;
      (*ACK).checksum = packet.seqnum;
      tolayer3(HOST_B, *ACK);
      sequence_B = sequence_B + 1;
    }
    else
    {
      pkt *ACK = new struct pkt;
      (*ACK).acknum = sequence_B - 1;
      (*ACK).checksum = packet.seqnum;
      tolayer3(HOST_B, *ACK);
    }
  }
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
  sequence_B = 0;
}
