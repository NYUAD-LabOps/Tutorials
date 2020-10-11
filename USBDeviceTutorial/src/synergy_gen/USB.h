/* generated thread header file - do not edit */
#ifndef USB_H_
#define USB_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void USB_entry(void);
#else
extern void USB_entry(void);
#endif
#ifdef __cplusplus
extern "C"
{
#endif
extern TX_SEMAPHORE g_cdc_activate_semaphore;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* USB_H_ */
