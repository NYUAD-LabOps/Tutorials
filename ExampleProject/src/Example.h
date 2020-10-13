#include "USB.h"
#define DEBUGGER 1
#define UDPMSGLENGTH 10
UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance);
void initGlobalsBlock();
char *initUSBBuffer_Pool(UINT size);
char *initUSBBuffer_PoolB(UINT size);
void processReceivedMsg(char *message_buffer);

struct machineGlobals
{
    char globalsInit;
    char USBPlugIn;
    char USBBufferOpen;
    char USBINIReady;

    FX_MEDIA * p_media;
    CHAR                        volume[32];
    FX_FILE my_file;
    UX_HOST_CLASS_STORAGE_MEDIA * p_ux_host_class_storage_media;
    char *local_buffer;
    char *USBBufferB;

    char UDPBuffer[UDPMSGLENGTH];
    char UDPRxBuff[UDPMSGLENGTH];
    char UDPFlowControl;
    UINT UDPTimeout;
    NX_UDP_SOCKET g_udp_sck;
    ///UDPRX is a flag which indicates if data has been received via UDP. Active HIGH.
    char UDPRX;
    char echoWaitStart;
} *machineGlobalsBlock;s
