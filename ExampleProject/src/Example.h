#include <USBHost.h>
#include <USBDevice.h>
#define DEBUGGER 1
#define UDPMSGLENGTH 10
#define IPADDSTRING "127.0.0.1"
#define LOOPBACKIP IP_ADDRESS(127,0,0,1)
#define PRIMARY_PORT 5000
#define SECONDARY_PORT 5001

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance);
void initGlobalsBlock();
char *initUSBBuffer_Pool(UINT size);
char *initUSBBuffer_PoolB(UINT size);
void processReceivedMsg(char *message_buffer);
void processUDPRx(NX_PACKET *p_packet);

void ux_cdc_device1_instance_activate(VOID *cdc_instance);
void ux_cdc_device1_instance_deactivate(VOID *cdc_instance);

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


    char primarySendBuff[UDPMSGLENGTH];


    char UDPBuffer[UDPMSGLENGTH];
    char UDPRxBuff[UDPMSGLENGTH];
    char UDPFlowControl;
    UINT UDPTimeout;
    NX_UDP_SOCKET g_udp_sckPrimary;
    NX_UDP_SOCKET g_udp_sckSecondary;
    ///UDPRX is a flag which indicates if data has been received via UDP. Active HIGH.
    char UDPRX;
    char echoWaitStart;
} *machineGlobalsBlock;
