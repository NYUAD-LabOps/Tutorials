/* generated thread source file - do not edit */
#include "USB.h"

TX_THREAD USB;
void USB_create(void);
static void USB_func(ULONG thread_input);
static uint8_t USB_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.USB") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_SEMAPHORE g_cdc_activate_semaphore;
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void USB_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_cdc_activate_semaphore;
    err_g_cdc_activate_semaphore = tx_semaphore_create (&g_cdc_activate_semaphore, (CHAR *) "g_cdc_activate_semaphore",
                                                        0);
    if (TX_SUCCESS != err_g_cdc_activate_semaphore)
    {
        tx_startup_err_callback (&g_cdc_activate_semaphore, 0);
    }

    UINT err;
    err = tx_thread_create (&USB, (CHAR *) "USB", USB_func, (ULONG) NULL, &USB_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&USB, 0);
    }
}

static void USB_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    USB_entry ();
}
