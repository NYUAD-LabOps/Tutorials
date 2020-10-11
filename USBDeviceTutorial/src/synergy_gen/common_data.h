/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_cgc.h"
#include "r_cgc_api.h"
#include "r_fmi.h"
#include "r_fmi_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"
#include "r_elc.h"
#include "r_elc_api.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "ux_api.h"

/* USBX Host Stack initialization error callback function. User can override the function if needed. */
void ux_v2_err_callback(void *p_instance, void *p_data);

#if !defined(NULL)
/* User Callback for Host Event Notification (Only valid for USB Host). */
extern UINT NULL(ULONG event, UX_HOST_CLASS *host_class, VOID *instance);
#endif

#if !defined(NULL)
/* User Callback for Device Event Notification (Only valid for USB Device). */
extern UINT NULL(ULONG event);
#endif

#ifdef UX_HOST_CLASS_STORAGE_H
/* Utility function to get the pointer to a FileX Media Control Block for a USB Mass Storage device. */
UINT ux_system_host_storage_fx_media_get(UX_HOST_CLASS_STORAGE * instance, UX_HOST_CLASS_STORAGE_MEDIA ** p_storage_media, FX_MEDIA ** p_fx_media);
#endif
void ux_common_init0(void);
#include "ux_api.h"
#include "ux_dcd_synergy.h"

/* USBX Device Stack initialization error callback function. User can override the function if needed. */
void ux_device_err_callback(void *p_instance, void *p_data);
void ux_device_init0(void);
void ux_device_remove_compiler_padding(unsigned char *p_device_framework, UINT length);
/* Header section starts for g_ux_device_class_cdc_acm0 */
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"
/* USBX CDC-ACM Instance Activate User Callback Function */
extern VOID ux_cdc_device0_instance_activate(VOID *cdc_instance);
/* USBX CDC-ACM Instance Deactivate User Callback Function */
extern VOID ux_cdc_device0_instance_deactivate(VOID *cdc_instance);
/* Header section ends for g_ux_device_class_cdc_acm0 */
void ux_device_class_cdc_acm_init0(void);
void g_ux_device_class_cdc_acm0_ux_device_open_init(void);
/** CGC Instance */
extern const cgc_instance_t g_cgc;
/** FMI on FMI Instance. */
extern const fmi_instance_t g_fmi;
/** IOPORT Instance */
extern const ioport_instance_t g_ioport;
/** ELC Instance */
extern const elc_instance_t g_elc;
void g_common_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* COMMON_DATA_H_ */
