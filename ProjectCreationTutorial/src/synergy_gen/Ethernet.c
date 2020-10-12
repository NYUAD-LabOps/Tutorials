/* generated thread source file - do not edit */
#include "Ethernet.h"

TX_THREAD Ethernet;
void Ethernet_create(void);
static void Ethernet_func(ULONG thread_input);
static uint8_t Ethernet_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Ethernet") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_EVENT_FLAGS_GROUP g_udp_ready;
TX_EVENT_FLAGS_GROUP g_udp_echo_received;
TX_EVENT_FLAGS_GROUP g_udp_data_received;
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Ethernet_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_udp_ready;
    err_g_udp_ready = tx_event_flags_create (&g_udp_ready, (CHAR *) "UDP Ready");
    if (TX_SUCCESS != err_g_udp_ready)
    {
        tx_startup_err_callback (&g_udp_ready, 0);
    }
    UINT err_g_udp_echo_received;
    err_g_udp_echo_received = tx_event_flags_create (&g_udp_echo_received, (CHAR *) "UDP Echo Received");
    if (TX_SUCCESS != err_g_udp_echo_received)
    {
        tx_startup_err_callback (&g_udp_echo_received, 0);
    }
    UINT err_g_udp_data_received;
    err_g_udp_data_received = tx_event_flags_create (&g_udp_data_received, (CHAR *) "UDP Data Received");
    if (TX_SUCCESS != err_g_udp_data_received)
    {
        tx_startup_err_callback (&g_udp_data_received, 0);
    }

    UINT err;
    err = tx_thread_create (&Ethernet, (CHAR *) "Ethernet", Ethernet_func, (ULONG) NULL, &Ethernet_stack, 1024, 2, 2, 1,
                            TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Ethernet, 0);
    }
}

static void Ethernet_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Ethernet_entry ();
}
