/* generated thread header file - do not edit */
#ifndef ETHERNETPRIMARY_H_
#define ETHERNETPRIMARY_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void EthernetPrimary_entry(void);
#else
extern void EthernetPrimary_entry(void);
#endif
#ifdef __cplusplus
extern "C"
{
#endif
extern TX_EVENT_FLAGS_GROUP g_udp_ready;
extern TX_EVENT_FLAGS_GROUP g_udp_echo_received;
extern TX_EVENT_FLAGS_GROUP g_udp_data_received;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ETHERNETPRIMARY_H_ */
