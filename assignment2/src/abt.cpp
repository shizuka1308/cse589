#include "../include/simulator.h"
#include <iostream>
#include <string.h>
#include <vector>
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
#define RTT 20.0
#define CHUNKSIZE 20
#define BUFFER 1000
#define AHOST 0
#define BHOST 1

using namespace std;

int acknowledgmentflag, sequence_a, sequence_b, sequence = 0;
vector<pkt> packets;

struct pkt lastings;
int sumchecking(struct pkt);

struct pkt *createPacket(struct msg message)
{
    struct pkt *packet = new struct pkt;
    (*packet).seqnum = sequence;
    (*packet).acknum = sequence;
    strcpy((*packet).payload, message.data);
    (*packet).checksum = sumchecking((*packet));
    return packet;
}

int sumchecking(struct pkt packet)
{
    char data[CHUNKSIZE];
    strcpy(data, packet.payload);
    int localsum_check = 0;
    int jiterator = 0;
    while (jiterator < CHUNKSIZE && data[jiterator] != '\0')
    {
        localsum_check = localsum_check+ data[jiterator];
        jiterator++;
    }

    localsum_check =localsum_check+ packet.seqnum;
    localsum_check =localsum_check+ packet.acknum;

    return localsum_check;
}
/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
    packets.push_back(*createPacket(message));
    sequence = sequence + 1;
    if (acknowledgmentflag == 1)
    {
        acknowledgmentflag = 0;
        lastings = packets.at(sequence_a);
        tolayer3(AHOST, lastings);
        starttimer(AHOST, RTT);
    }
}

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
    if (packet.acknum == sequence_a)
    {
        acknowledgmentflag = 1;
        stoptimer(AHOST);
        sequence_a=sequence_a+1;
    }
    else
    {
        starttimer(AHOST, RTT);
        tolayer3(AHOST, lastings);
    }
}

/* called when A's timer goes off */
void A_timerinterrupt()
{
    starttimer(AHOST, RTT);
    tolayer3(AHOST, lastings);
}

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init()
{
    acknowledgmentflag = 1;
    sequence_a = 0;
}

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet)
{
    if(sumchecking(packet) == packet.checksum){
    if (sequence_b == packet.seqnum)
    {
        tolayer5(BHOST, packet.payload);
        pkt *ACK = new struct pkt;
        (*ACK).acknum = sequence_b;
        (*ACK).checksum = packet.seqnum;
        tolayer3(BHOST, *ACK);
        sequence_b=sequence_b+1;
    } else 
    {
        pkt *ACK = new struct pkt;
        (*ACK).acknum = -1;
        (*ACK).checksum = packet.seqnum;
        tolayer3(BHOST, *ACK);
    }
    }
}

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init()
{
    sequence_b = 0;
}
