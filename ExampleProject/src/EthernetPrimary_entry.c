#include "EthernetPrimary.h"
#include "Example.h"

#define APP_UDP_INSTANT_RX      1
#define APP_UDP_RTT_LOG         (1)

static NX_UDP_SOCKET g_udp_sckPrimary;

static void g_udp_sckPrimary_receive_cb(NX_UDP_SOCKET *);
void ethernetPrimarySend(unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);

/* Ethernet entry function */
void EthernetPrimary_entry(void)
{
    UINT status;
    ULONG event;
    ULONG link_status;

//    ip_init0 ();

    while (machineGlobalsBlock->globalsInit != 1)
        tx_thread_sleep (1);

    status = nx_ip_status_check (&g_ip0, NX_IP_INITIALIZE_DONE, &link_status, NX_WAIT_FOREVER);

    if (DEBUGGER)
    {
        printf ("\nIP initialization complete. IP:%s", IPADDSTRING);
    }

    if (DEBUGGER)
    {
        printf ("\nCreating and binding Primary socket...");
    }

    status = nx_udp_socket_create(&g_ip0, &machineGlobalsBlock->g_udp_sckPrimary, "UDP Socket", NX_IP_NORMAL,
                                  NX_DONT_FRAGMENT, NX_IP_TIME_TO_LIVE, 512);
    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nPrimary socket creation failed.");
        }
        else
        {
            printf ("\nPrimary socket creation successful.");
        }
    }

    status = nx_udp_socket_bind (&machineGlobalsBlock->g_udp_sckPrimary, PRIMARY_PORT,
    NX_NO_WAIT);

    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nPrimary socket binding failed.");
        }
        else
        {
            printf ("\nPrimary socket binding successful.");
        }
    }

    status = nx_udp_socket_receive_notify (&machineGlobalsBlock->g_udp_sckPrimary, g_udp_sckPrimary_receive_cb);

    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nPrimary receive interrupt binding failed.");
        }
        else
        {
            printf ("\nPrimary receive interrupt binding successful. Bound to port:%d",
                    machineGlobalsBlock->g_udp_sckSecondary.nx_udp_socket_port);
        }
    }

    if (DEBUGGER)
    {
        printf ("\nEthernet Primary initialization complete.");
        printf ("\nStarting example send loop...");
    }

    ///Clear the event flags
    status = tx_event_flags_get (&g_udp_echo_received, 1, TX_AND_CLEAR, &event, NX_NO_WAIT);

//    NX_PACKET *my_packet;
//    NX_PACKET *receive_packet;
//    UCHAR buffer[64];
//    ULONG bytes_copied;

    int sendCount = 1;
    while (1)
    {

        snprintf (machineGlobalsBlock->primarySendBuff, UDPMSGLENGTH, "Count:%d", sendCount);
        printf ("Primary sending \"%s\"...", machineGlobalsBlock->primarySendBuff);

        ethernetPrimarySend (UDPMSGLENGTH, &machineGlobalsBlock->g_udp_sckPrimary,
        LOOPBACKIP,
                             SECONDARY_PORT, &g_udp_echo_received);

        ///Increment the counter and clear the buffer.
        sendCount++;
        memset (machineGlobalsBlock->primarySendBuff, 0, UDPMSGLENGTH);
        tx_thread_sleep (2000);
    }
}

void ethernetPrimarySend(unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received)
{
    UINT status;
    ULONG tmp = 0;

    NX_PACKET *my_packet;
    do
    {
        status = nx_packet_allocate (&g_packet_pool0, &my_packet, NX_UDP_PACKET, NX_WAIT_FOREVER);
        /* Check for error.  */
        nx_packet_data_append (my_packet, machineGlobalsBlock->primarySendBuff, length, &g_packet_pool0,
                               NX_WAIT_FOREVER);

        status = nx_udp_socket_send(udp_sck, my_packet, ip_address, port);

        if (NX_SUCCESS == status)
        {
        }
        else
        {
            nx_packet_release(my_packet);
        }

        status = tx_event_flags_get (udp_echo_received, 1, TX_AND_CLEAR, &tmp, 300);
    }
    while (tmp == 0);

    memset (machineGlobalsBlock->primarySendBuff, 0, UDPMSGLENGTH);
}

void processUDPRx(NX_PACKET *p_packet)
{
    UINT status;
    if (memcmp (machineGlobalsBlock->primarySendBuff, p_packet->nx_packet_prepend_ptr, UDPMSGLENGTH) == 0)
    {
///An echo packet was received.
        status = tx_event_flags_set (&g_udp_echo_received, 1, TX_OR);
    }
    else
    {
///A data packet was received.
//        memcpy (machineGlobalsBlock->UDPRxBuff, p_packet->nx_packet_prepend_ptr, UDPMSGLENGTH);
//        status = tx_event_flags_set (&g_udp_data_received, 1, TX_OR);
    }
}


static void g_udp_sckPrimary_receive_cb(NX_UDP_SOCKET *p_sck)
{
    NX_PACKET *p_packet = NULL;
    /* Receive data here */

    nx_udp_socket_receive (p_sck, &p_packet, NX_NO_WAIT);
///No echo from the Primary
//    nx_udp_source_extract (p_packet, &ip, &client_port);
//    status = nx_udp_socket_send(p_sck, p_packet, ip, client_port);

    if (NULL != p_packet)
    {
        if (DEBUGGER)
        {
            printf ("\nPrimary Received:%s.", p_packet->nx_packet_prepend_ptr);
        }
//        nx_packet_data_retrieve (p_packet, &machineGlobalsBlock->UDPRxBuff, length);

        processUDPRx (p_packet);
        nx_packet_release(p_packet);
    }
}
