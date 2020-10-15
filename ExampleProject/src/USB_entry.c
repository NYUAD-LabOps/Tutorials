#include "USB.h"
#include <Ganymede.h>
#include "fx_api.h"
#include "Example.h"

static UX_SLAVE_CLASS_CDC_ACM *g_cdc;
#define SEMI_HOSTING

#define     MAX_NUM_OF_TRY              (1000000)
#define     UX_STORAGE_BUFFER_SIZE      (64*1024)

#define     EVENT_USB_PLUG_IN           (1UL << 0)
#define     EVENT_USB_PLUG_OUT          (1UL << 1)

static FX_FILE my_file;
static FX_FILE ini_file;
static char *local_buffer;

/* USB entry function */

///This example USB thread begins by creating a memory block pool. This memory block pool resides in a protected space, where it is protected from corruption by any RTOS
/// operations. This memory pool is set up to store a character buffer and machine state information, including the state of the USB plug. Next, it waits until the USB Host device
/// registers a USB plug has been connected. This initiates a callback function which registers the change in the memory block pool. Once the main thread registers this, it opens
/// the device via the FILEX API, and checks for the existence of an INI file. If the file does not exist, it creates it. If it does, it loads its contents into memory.
/// Finally, it closes the file, flushes the media, and then closes the media. Note: flushing the media is required for every file or filesystem change, as it writes the
/// changes to the device. This demonstrates the operation of a startup INI file which can be used to retain machine settings.
///
/// After completing this operation, the thread moves into an infinite loop, which waits for incoming USB Device communications, reads this data, processes the received string, and
/// sends a response. This demonstrates basic operation of the USB Device interface.
///
/// For an explanation of the Renesas Memory Block Pool operation, please refer to "http://renesasrulz.com/synergy/b/weblog/posts/transitioning-to-threadx-memory-pools" or the
/// ThreadX documentation. Memory pools should always be used instead of malloc operations. Memory pools are the only way to ensure that data is kept safe from RTOS
/// thread operations.
void USB_entry(void)
{
    CHAR volume[32];
    FX_MEDIA *p_media;
    ULONG actual_length = 0;
    ULONG actual_flags;
    int iValue = 0;
    UINT tx_return;
    UINT fx_return;
    UINT status;
    UINT tmpIndex;
    ULONG length_tmp;

    while (machineGlobalsBlock->globalsInit != 1)
    {
        tx_thread_sleep (500);
    }

    ///Setup the byte pool for handling FileX operations.
    local_buffer = initUSBBuffer_Pool (UX_STORAGE_BUFFER_SIZE);
    machineGlobalsBlock->local_buffer = local_buffer;
    if (DEBUGGER)
        printf ("\nUSB Host buffer initialized.");

    ///Wait until a USB plug is inserted.
    while (machineGlobalsBlock->USBPlugIn != 1)
    {
        tx_thread_sleep (500);
    }

    if (DEBUGGER)
        printf ("\nUSB Plug detected.");

    // Get the pointer to FileX Media Control Block for a USB flash device.
//    p_media = ;
    machineGlobalsBlock->p_media = g_fx_media0_ptr;

    // Retrieve the volume name of the opened media from the Data sector
    fx_return = fx_media_volume_get (machineGlobalsBlock->p_media, volume, FX_DIRECTORY_SECTOR);

    if (fx_return == FX_SUCCESS)
    {
        // Set the default directory in the opened media, arbitrary name called "firstdir".
        fx_directory_default_set (machineGlobalsBlock->p_media, "firstdir");

        // Suspend this thread for 100 time-ticks.
        tx_thread_sleep (100);

        // Try to open the file, 'init.ini'.
        fx_return = fx_file_open(machineGlobalsBlock->p_media, &ini_file, "init.ini",
                                 FX_OPEN_FOR_READ | FX_OPEN_FOR_WRITE);

        if (fx_return != FX_SUCCESS)
        {
            if (DEBUGGER)
                printf ("\ninit.ini not found. Creating...");

            //The 'init.ini' file was not found, so create a new file
            fx_return = fx_file_create (machineGlobalsBlock->p_media, "init.ini");

            if (fx_return != FX_SUCCESS)
            {
                if (DEBUGGER)
                    printf ("\nFailed to create init.ini.");

            }
            else
            {
                if (DEBUGGER)
                    printf ("\ninit.ini created.");

                // Open that file
                fx_return = fx_file_open(machineGlobalsBlock->p_media, &ini_file, "init.ini",
                                         FX_OPEN_FOR_READ | FX_OPEN_FOR_WRITE);
                if (fx_return != FX_SUCCESS)
                {
                    if (DEBUGGER)
                        printf ("\nCannot open init.ini.");
                }
                else
                {
                    if (DEBUGGER)
                        printf ("\ninit.ini opened.");

                    if (DEBUGGER)
                        printf ("\nThe INI file is empty. Saving a 1...");

                    local_buffer[0] = '1';

                    tmpIndex = 0;

                    ///Go to INI file start
                    fx_return = fx_file_seek (&ini_file, 0);

                    printf ("\nWriting INI data...");

                    // Write the file in blocks
                    fx_return = fx_file_write (&ini_file, local_buffer, 1);

                    if (fx_return != FX_SUCCESS)
                    {
                        if (DEBUGGER)
                            printf ("\nINI write failed.");
                    }
                    else
                    {
                        if (DEBUGGER)
                            printf ("\nINI write successful. Flushing media...");

                        fx_return = fx_media_flush (machineGlobalsBlock->p_media);
                        if (fx_return != FX_SUCCESS)
                        {
                            if (DEBUGGER)
                                printf ("\nMedia Flush failed.");
                        }
                        else
                        {
                            if (DEBUGGER)
                                printf ("\nMedia Flush successful.");
                        }
                    }
                }

            }

        }
        else
        {
            ///init.ini is already present. Load INI data
            if (DEBUGGER)
                printf ("\nINI present. Reading...");

            tmpIndex = 0;

            ///Go to INI file start
            fx_return = fx_file_seek (&ini_file, 0);

            ///Read the first byte of the file and place it in local_buffer.
            fx_return = fx_file_read (&ini_file, local_buffer, 1, &actual_length);

            if (fx_return != FX_SUCCESS)
            {
                if (DEBUGGER)
                    printf ("\nINI read fail.");
            }
            else
            {
                if (DEBUGGER)
                    printf ("\nINI read success.");
            }

            if (DEBUGGER)
                printf ("\nINI data loaded.");

            if (actual_length > 0)
            {
                if (DEBUGGER)
                    printf ("\nIncrementing and saving retrieved byte.");

                local_buffer[0]++;

                tmpIndex = 0;

                ///Go to INI file start
                fx_return = fx_file_seek (&ini_file, 0);

                printf ("\nWriting INI data...");

                // Write the file in blocks
                fx_return = fx_file_write (&ini_file, local_buffer, 1);

                if (fx_return != FX_SUCCESS)
                {
                    if (DEBUGGER)
                        printf ("\nINI write failed.");
                }
                else
                {
                    if (DEBUGGER)
                        printf ("\nINI write successful. Flushing media...");

                    fx_return = fx_media_flush (machineGlobalsBlock->p_media);
                    if (fx_return != FX_SUCCESS)
                    {
                        if (DEBUGGER)
                            printf ("\nMedia Flush failed.");
                    }
                    else
                    {
                        if (DEBUGGER)
                            printf ("\nMedia Flush successful.");
                    }
                }

            }
            else
            {
                if (DEBUGGER)
                    printf ("\nThe INI file is empty. Saving a 1...");

                local_buffer[0] = '1';

                tmpIndex = 0;

                ///Go to INI file start
                fx_return = fx_file_seek (&ini_file, 0);

                printf ("\nWriting INI data...");

                // Write the file in blocks
                fx_return = fx_file_write (&ini_file, local_buffer, 1);

                if (fx_return != FX_SUCCESS)
                {
                    if (DEBUGGER)
                        printf ("\nINI write failed.");
                }
                else
                {
                    if (DEBUGGER)
                        printf ("\nINI write successful. Flushing media...");

                    fx_return = fx_media_flush (machineGlobalsBlock->p_media);
                    if (fx_return != FX_SUCCESS)
                    {
                        if (DEBUGGER)
                            printf ("\nMedia Flush failed.");
                    }
                    else
                    {
                        if (DEBUGGER)
                            printf ("\nMedia Flush successful.");
                    }
                }
            }

            ///Clear local_buffer
            memset (machineGlobalsBlock->local_buffer, 0, 1);

        }

        // Already open a file, then read the file in blocks
        // Set a specified byte offset for reading
//        fx_return = fx_file_seek (&my_file, 0);

        machineGlobalsBlock->USBBufferOpen = 1;
        if (DEBUGGER)
            printf ("\nUSB buffer ready.");
        if (DEBUGGER)
            printf ("\nController ready.");

        //Close already opened file
        fx_return = fx_file_close (&my_file);

        tx_thread_sleep (200);

        /* flush the media */
        fx_return = fx_media_flush (machineGlobalsBlock->p_media);

        /* close the media */
        fx_return = fx_media_close (machineGlobalsBlock->p_media);

    }
    else
    {
        if (DEBUGGER)
            printf ("\nCould not retrieve media information.");
    }

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

    while (machineGlobalsBlock->USBPlugIn == 1)
    {
        tx_thread_sleep (500);
    }

}

void processReceivedMsg(char *message_buffer)
{
    printf (message_buffer);
}

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance)
{
    /* variable to hold the UX calls return values */
    UINT ux_return;

    UX_HOST_CLASS_STORAGE_MEDIA *p_ux_host_class_storage_media;

// Check if host_class is for Mass Storage class.
    if (UX_SUCCESS
            == _ux_utility_memory_compare (_ux_system_host_class_storage_name, host_class,
                                           _ux_utility_string_length_get (_ux_system_host_class_storage_name)))
    {
        // Get the pointer to the media
        ux_return = ux_system_host_storage_fx_media_get (instance, &p_ux_host_class_storage_media, &g_fx_media0_ptr);

        if (ux_return != UX_SUCCESS)
        {
            /* This is a fairly simple error handling - it holds the
             application execution. In a more realistic scenarios
             a more robust and complex error handling solution should
             be provided. */

            if (DEBUGGER)
                printf ("\nCould not get the pointer to the media, error:%d\n", ux_return);

//                   tx_thread_sleep(TX_WAIT_FOREVER);
        }
        else
        {
            if (DEBUGGER)
                printf ("\nGot USB plug media pointer.");
            //Check the usb_event type
            switch (usb_event)
            {
                case EVENT_USB_PLUG_IN:
                    // Notify the insertion of a USB Mass Storage device.
                    tx_event_flags_set (&g_usb_plug_events, EVENT_USB_PLUG_IN, TX_OR);

                    ///Your code here
                    machineGlobalsBlock->USBPlugIn = 1;
                break;
                case EVENT_USB_PLUG_OUT:
                    // Notify the removal of a USB Mass Storage device.
                    tx_event_flags_set (&g_usb_plug_events, EVENT_USB_PLUG_OUT, TX_OR);

                    ///Your code here
                    machineGlobalsBlock->USBPlugIn = 0;
                break;
                default:
                    //ignore this unsupported event
                break;
            }
        }
    }
    return UX_SUCCESS;
}

/// Saves all persistent machine information, including motor calibration settings
void saveINI()
{
//    UINT fx_return;
//    UINT tmpIndex;
//    ULONG length_tmp;
//
//    tmpIndex = 0;
//    length_tmp = sizeof(struct motorController);
//    ///Go to INI file start
//    fx_return = fx_file_seek (&ini_file, 0);
//
//    memcpy (local_buffer, motorBlockZ, length_tmp);
//    memcpy ((local_buffer + length_tmp), motorBlockX, length_tmp);
//    memcpy ((local_buffer + (2 * length_tmp)), motorBlockY, length_tmp);
//    memcpy ((local_buffer + (3 * length_tmp)), toolBlockA->motorBlock, length_tmp);
//
//    printf ("\nWriting INI data...");
//    // Write the file in blocks
//    fx_return = fx_file_write (&ini_file, local_buffer, (4 * length_tmp));
//    if (fx_return != FX_SUCCESS)
//    {
//        if (DEBUGGER)
//            printf ("\nINI write fail.");
//    }
//    else
//    {
//        if (DEBUGGER)
//            printf ("\nINI write success.");
//        fx_return = fx_media_flush (machineGlobalsBlock->p_media);
//    }
//    if (DEBUGGER)
//        printf ("\nINI save complete.");
//
/////Clear local buffer to prevent errors with other USB operations
//    memset (machineGlobalsBlock->local_buffer, 0, (4 * length_tmp));
//
//    if (DEBUGGER)
//        printf ("\nINI save complete.");
}

/// Saves all persistent machine information, including motor calibration settings
void loadINI()
{
//    UINT fx_return;
//    UINT tmpIndex;
//    ULONG length_tmp;
//    ULONG actual_length;
//
//    tmpIndex = 0;
//    length_tmp = sizeof(struct motorController);
//    ///Go to INI file start
//    fx_return = fx_file_seek (&ini_file, 0);
//
//    if (DEBUGGER)
//        printf ("\nLoading INI...");
//    ///Attempt to read 500 bytes
//    fx_return = fx_file_read (&ini_file, local_buffer, (4 * length_tmp), &actual_length);
//    if (fx_return != FX_SUCCESS)
//    {
//        if (DEBUGGER)
//            printf ("\nINI read fail.");
//    }
//    else
//    {
//        if (DEBUGGER)
//            printf ("\nINI read success.");
//    }
//
//    memcpy (motorBlockZ, local_buffer, length_tmp);
//    memcpy (motorBlockX, (local_buffer + length_tmp), length_tmp);
//    memcpy (motorBlockY, (local_buffer + (2 * length_tmp)), length_tmp);
//    memcpy (toolBlockA->motorBlock, (local_buffer + (3 * length_tmp)), length_tmp);
//
//    if (DEBUGGER)
//        printf ("\nINI data loaded.");
/////Clear local buffer to prevent errors with other USB operations
//    memset (machineGlobalsBlock->local_buffer, 0, (4 * length_tmp));
}

void ux_cdc_device0_instance_activate(VOID *cdc_instance)
{
    /* Save the CDC instance.  */
    g_cdc = (UX_SLAVE_CLASS_CDC_ACM *) cdc_instance;
    tx_semaphore_put (&g_cdc_activate_semaphore);
}

void ux_cdc_device0_instance_deactivate(VOID *cdc_instance)
{
    SSP_PARAMETER_NOT_USED(cdc_instance);

    g_cdc = UX_NULL;
}

