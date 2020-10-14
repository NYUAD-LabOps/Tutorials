#include "MainThread.h"
#include "Example.h"

TX_BLOCK_POOL globals_pool;
TX_BYTE_POOL USB_Byte_Pool;
TX_BYTE_POOL USB_Byte_PoolB;

/* MainThread entry function */
void MainThread_entry(void)
{
    /* TODO: add your own code here */
    if (DEBUGGER)
        initialise_monitor_handles ();

    initGlobalsBlock ();
    machineGlobalsBlock->USBBufferB = initUSBBuffer_PoolB (512);


    tx_thread_suspend (tx_thread_identify ());
}

void initGlobalsBlock()
{
    //init memory pool and block for retaining machine status information
    UINT status;
    ssp_err_t err;
    unsigned char *memory_ptr;

    status = tx_block_pool_create(&globals_pool, "globals", sizeof(struct machineGlobals), (VOID *) 0x20050000, 1000);

    status = tx_block_allocate (&globals_pool, (VOID **) &memory_ptr, TX_NO_WAIT);
    machineGlobalsBlock = (struct machineGlobals *) memory_ptr;


    machineGlobalsBlock->USBPlugIn = 0;

    machineGlobalsBlock->globalsInit = 1;


}

char *initUSBBuffer_Pool(UINT size)
{
    unsigned char *memory_ptr;
    UINT status;
    ///Create pool
    status = tx_byte_pool_create(&USB_Byte_Pool, "usb_byte_pool", (VOID *) 0x20060000, size + 128);

    ///Allocate bytes
    status = tx_byte_allocate (&USB_Byte_Pool, (VOID **) &memory_ptr, size, TX_NO_WAIT);
    if (status != TX_SUCCESS)
    {
        printf ("USB Buffer Init Failed.");
    }
    memset (memory_ptr, 0, size);
    return memory_ptr;
}

char *initUSBBuffer_PoolB(UINT size)
{
    unsigned char *memory_ptr;
    UINT status;
    ///Create pool
    status = tx_byte_pool_create(&USB_Byte_PoolB, "usb_byte_pool", (VOID *) 0x20070000, size + 64);

    ///Allocate bytes
    status = tx_byte_allocate (&USB_Byte_PoolB, (VOID **) &memory_ptr, size, TX_NO_WAIT);
    if (status != TX_SUCCESS)
    {
        printf ("USB Buffer Init Failed.");
    }
    memset (memory_ptr, 0, size);
    return memory_ptr;
}
