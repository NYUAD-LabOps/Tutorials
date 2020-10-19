#include "EthernetSecondary.h"
#include "Example.h"

static void g_udp_sckSecondary_receive_cb(NX_UDP_SOCKET *p_sck);

/* EthernetSecondary entry function */
void EthernetSecondary_entry(void)
{
    int i;
    UINT status;
    ULONG event;
    ULONG link_status;
    /* Create all sockets and bind them to their respective ports */
    /* Wait for the IP stack and network hardware
     * to get initialized.
     */
    //    ///Should be replaced with a proper wait flag.
    //    tx_thread_sleep (50);
    //    ip_init0 ();
    while (machineGlobalsBlock->globalsInit != 1)
        tx_thread_sleep (10);
    status = nx_ip_status_check (&g_ip0, NX_IP_INITIALIZE_DONE, &link_status, NX_WAIT_FOREVER);

    if (DEBUGGER)
    {
        printf ("\nCreating and binding Secondary socket...");
    }

    status = nx_udp_socket_create(&g_ip0, &machineGlobalsBlock->g_udp_sckSecondary, "UDP Socket", NX_IP_NORMAL,
                                  NX_DONT_FRAGMENT, NX_IP_TIME_TO_LIVE, 512);
    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nSecondary socket creation failed.");
        }
        else
        {
            printf ("\nSecondary socket creation successful.");
        }
    }

    status = nx_udp_socket_bind (&machineGlobalsBlock->g_udp_sckSecondary, SECONDARY_PORT,
    NX_NO_WAIT);

    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nSecondary socket binding failed.");
        }
        else
        {
            printf ("\nSecondary socket binding successful.");
        }
    }
    status = nx_udp_socket_receive_notify (&machineGlobalsBlock->g_udp_sckSecondary, g_udp_sckSecondary_receive_cb);

    if (DEBUGGER)
    {
        if (NX_SUCCESS != status)
        {
            printf ("\nSecondary receive interrupt binding failed.");
        }
        else
        {
            printf ("\nSecondary receive interrupt binding successful. Bound to port:%d",
                    machineGlobalsBlock->g_udp_sckSecondary.nx_udp_socket_port);
        }
    }

    if (DEBUGGER)
    {
        printf ("\nEthernet Secondary initialization complete.");
    }

    int sendCount = 1;
    while (1)
    {

        tx_thread_suspend (tx_thread_identify ());
    }
}

UINT EthernetSecondarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received)
{
    UINT status;
    ioport_level_t level;
    NX_PACKET *my_packet;
    status = nx_packet_allocate (&g_packet_pool0, &my_packet, NX_UDP_PACKET, NX_WAIT_FOREVER);
    nx_packet_data_append (my_packet, data, length, &g_packet_pool0,
    NX_WAIT_FOREVER);
//    if (DEBUG)
//    {
//        printf ("\nSending:%s...", machineGlobalsBlock->UDPTxBuff);
//    }
    status = nx_udp_socket_send(udp_sck, my_packet, ip_address, port);
    if (status != NX_SUCCESS)
    {
        nx_packet_release(my_packet);
    }
//    if (DEBUG)
//    {
//        if (NX_SUCCESS == status)
//        {
//            printf ("\nSend success.");
//        }
//        else
//        {
//            printf ("\nSend fail.");
//        }
//    }
    return status;
}

static void g_udp_sckSecondary_receive_cb(NX_UDP_SOCKET *p_sck)
{
    UINT status;
    NX_PACKET *p_packet = NULL;
    ULONG *length;
    char buff[UDPMSGLENGTH];
    /* Receive data here */
    status = nx_udp_socket_receive (p_sck, &p_packet, NX_NO_WAIT);
    if (status == NX_SUCCESS)
    {
        ///The following commented code has been left here to give future developers some example code that will allow them to extract source information
        /// from an incoming packet. For more information about these and other UDP operations, please refer to the Renesas documentation.
        //        ULONG ip;
        //        UINT client_port;
        //        nx_udp_source_extract (p_packet, &ip, &client_port);

        memcpy (buff, p_packet->nx_packet_prepend_ptr, UDPMSGLENGTH);

        ///Send echo packet to Primary.
        status = nx_udp_socket_send(&machineGlobalsBlock->g_udp_sckSecondary, p_packet, LOOPBACKIP, PRIMARY_PORT);

        if (status != NX_SUCCESS)
        {
            ///The Ethernet API is designed to release the packet after a successful send operation. If the operation fails,
            /// the application must release the packet separately to avoid memory errors.
            status = nx_packet_release(p_packet);
            if (DEBUGGER)
                printf ("\nEcho Fail.");
        }
        if (DEBUGGER)
        {

            if (NX_SUCCESS == status)
            {
                printf ("\nEcho send success.");
            }
            else
            {
                printf ("\nEcho send fail.");
            }
        }

    }
    else
    {
        if (DEBUGGER)
            printf ("\nReceive Fail.");
    }

    if (NULL != buff[0])
    {

        if (DEBUGGER)
        {
            printf ("\nSecondary Received:%s", buff);
        }
//        processEth (buff);
    }
}
