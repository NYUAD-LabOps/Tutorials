#include "USBDevice.h"
#include "Example.h"

static UX_SLAVE_CLASS_CDC_ACM *g_cdc;

/* USBDevice entry function */
void USBDevice_entry(void)
{
    UINT status;
    ULONG actual_length = 0;

    while (machineGlobalsBlock->globalsInit != 1)
    {
        tx_thread_sleep (500);
    }


    ///Initialize the Device buffer.
    machineGlobalsBlock->USBBufferB = initUSBBuffer_PoolB (512);

    while (1)
    {
        memset (machineGlobalsBlock->USBBufferB, 0, 49);
        status = _ux_device_class_cdc_acm_read (g_cdc, machineGlobalsBlock->USBBufferB, 49, &actual_length);
        if (status == UX_SUCCESS)
        {
            if (machineGlobalsBlock->USBBufferB[0] == 'U' && machineGlobalsBlock->USBBufferB[1] == 'S'
                    && machineGlobalsBlock->USBBufferB[2] == 'B')
            {
                status = _ux_device_class_cdc_acm_write (g_cdc, (UCHAR *) "USB", 4, &actual_length);
            }
            else if (machineGlobalsBlock->USBBufferB[0] == 'T' && machineGlobalsBlock->USBBufferB[1] == 'M'
                    && machineGlobalsBlock->USBBufferB[2] == 'P')
            {
                float tempRead = 0.01;
                char tmpUSBOut[12];
                memset (tmpUSBOut, 0, 12);
                tmpUSBOut[0] = 'T';
                tmpUSBOut[1] = 'M';
                tmpUSBOut[2] = 'P';

                snprintf (tmpUSBOut + 3, 8, "%f", tempRead);
                status = _ux_device_class_cdc_acm_write (g_cdc, (UCHAR *) tmpUSBOut, 12, &actual_length);
            }
            else
            {
                processReceivedMsg (machineGlobalsBlock->USBBufferB);
            }
        }
        else
        {

        }
        tx_thread_sleep (1);
    }
}

void processReceivedMsg(char *message_buffer)
{
    printf (message_buffer);
}

void ux_cdc_device1_instance_activate(VOID *cdc_instance)
{
    /* Save the CDC instance.  */
    g_cdc = (UX_SLAVE_CLASS_CDC_ACM *) cdc_instance;
    tx_semaphore_put (&g_cdc_activate_semaphore);
}

void ux_cdc_device1_instance_deactivate(VOID *cdc_instance)
{
    SSP_PARAMETER_NOT_USED(cdc_instance);

    g_cdc = UX_NULL;
}
