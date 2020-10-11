/**************************************************************************/ 
/*                                                                        */ 
/*            Copyright (c) 1996-2019 by Express Logic Inc.               */ 
/*                                                                        */ 
/*  This software is copyrighted by and is the sole property of Express   */ 
/*  Logic, Inc.  All rights, title, ownership, or other interests         */ 
/*  in the software remain the property of Express Logic, Inc.  This      */ 
/*  software may only be used in accordance with the corresponding        */ 
/*  license agreement.  Any unauthorized use, duplication, transmission,  */ 
/*  distribution, or disclosure of this software is expressly forbidden.  */ 
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */ 
/*  written consent of Express Logic, Inc.                                */ 
/*                                                                        */ 
/*  Express Logic, Inc. reserves the right to modify this software        */ 
/*  without notice.                                                       */ 
/*                                                                        */ 
/*  Express Logic, Inc.                     info@expresslogic.com         */
/*  11423 West Bernardo Court               http://www.expresslogic.com   */
/*  San Diego, CA  92127                                                  */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   Application Interface (API)                                         */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/ 
/*                                                                        */ 
/*  APPLICATION INTERFACE DEFINITION                       RELEASE        */ 
/*                                                                        */ 
/*    ux_api.h                                            PORTABLE C      */ 
/*                                                           5.9          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Express Logic Inc.                                   */ 
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This file defines the basic Application Interface (API) to the      */ 
/*    high-performance USBX real-time USB stack.  All service prototypes  */ 
/*    and data structure definitions are defined in this file.            */ 
/*    Please note that basic data type definitions and other architecture-*/ 
/*    specific information is contained in the file ux_port.h.            */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  07-01-2007     TCRG                     Initial Version 5.0           */ 
/*  11-11-2008     TCRG                     Modified comment(s), added    */ 
/*                                            constants, updated typedefs,*/ 
/*                                            and updated prototypes,     */ 
/*                                            resulting in  version 5.2   */ 
/*  07-10-2009     TCRG                     Modified comment(s), changed  */ 
/*                                            default timeout values, and */ 
/*                                            added trace logic,          */ 
/*                                            resulting in version 5.3    */ 
/*  06-13-2010     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.4    */ 
/*  09-01-2011     TCRG                     Modified comment(s), and      */ 
/*                                            added constants, etc.,      */ 
/*                                            resulting in version 5.5    */ 
/*  10-10-2012     TCRG                     Modified comment(s),          */ 
/*                                            added new constants, and    */ 
/*                                            DFU class support,          */ 
/*                                            resulting in version 5.6    */ 
/*  06-01-2014     TCRG                     Modified comment(s), added    */ 
/*                                            SCHAR default type,         */ 
/*                                            and added support for       */ 
/*                                            DEBUG_LOG, resulting in     */ 
/*                                            version 5.7                 */ 
/*  06-01-2017     TCRG                     Modified comment(s), derived  */ 
/*                                            USB internal timeout values */ 
/*                                            from ThreadX timer tick     */ 
/*                                            frequency, added new error  */ 
/*                                            trap function support,      */
/*                                            resulting in version 5.8    */ 
/*  08-15-2019     TCRG                     Modified comment(s), added    */ 
/*                                            IAD descriptor support,     */
/*                                            added symbols that allow    */ 
/*                                            users to set stack sizes    */ 
/*                                            for individual threads      */ 
/*                                            in the enum and hcd thread, */ 
/*                                            added support for HID       */
/*                                            client removal, added       */
/*                                            computation of lowest thread*/
/*                                            priority in system structure*/
/*                                            fixed timeout definitions,  */ 
/*                                            added network prototypes,   */ 
/*                                            added assertion macros,     */ 
/*                                            added thread pending member */ 
/*                                            to transfer control block,  */ 
/*                                            added synchronize cache     */ 
/*                                            function trace macros, added*/ 
/*                                            error context definition    */
/*                                            for device stack tracking,  */
/*                                            updated error code          */ 
/*                                            constants comment, added new*/ 
/*                                            error code for CDC-ECM,     */ 
/*                                            added data memory barrier   */ 
/*                                            definition, added new error */ 
/*                                            code for general malformed  */ 
/*                                            packets, fix API #define    */ 
/*                                            for ux_device_stack_transfer*/ 
/*                                            _abort, removed unused      */ 
/*                                            device member from DCD      */ 
/*                                            struct, added max length    */ 
/*                                            symbols for class and HCD   */ 
/*                                            names, changed name buffer  */ 
/*                                            in host and slave structs   */ 
/*                                            to use max class name       */
/*                                            length symbol,              */ 
/*                                            added trace event,          */
/*                                            resulting in version 5.9    */ 
/*                                                                        */ 
/**************************************************************************/ 

#ifndef UX_API_H       
#define UX_API_H

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef   __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
extern   "C" {

#endif


/* Include ThreadX API include file.  */

#include "tx_api.h"


/* Include USBX port specific file.  */

#include "ux_port.h"

/* Define the maximum length for class names (exclude string null-terminator).  */
#define UX_MAX_CLASS_NAME_LENGTH    63

/* Define the maximum length for HCD names (exclude string null-terminator).  */
#define UX_MAX_HCD_NAME_LENGTH      63

/* Disable warning of parameter not used. */
#ifndef UX_PARAMETER_NOT_USED
#define UX_PARAMETER_NOT_USED(p) ((VOID)(p))
#endif

/* Define additional generic USBX types.  */

#ifndef SCHAR
typedef signed char               SCHAR;
#endif

/* If the port file did not define the memory barrier instruction, define it
   to nothing since this is platform-specific.  */
#ifndef UX_DATA_MEMORY_BARRIER
#define UX_DATA_MEMORY_BARRIER
#endif


/* This defines the ASSERT and process on ASSERT fail. */
#ifdef UX_ENABLE_ASSERT
#ifndef UX_ASSERT_FAIL
#define UX_ASSERT_FAIL                                      for (;;) {tx_thread_sleep(UX_WAIT_FOREVER); }
#endif
#define UX_ASSERT(s)                                        if (!(s)) {UX_ASSERT_FAIL}
#else
#define UX_ASSERT(s)
#endif /* UX_ENABLE_ASSERT */


#ifndef UX_MAX_SLAVE_INTERFACES  
#define UX_MAX_SLAVE_INTERFACES                             16
#endif

/* Convert from millisecond to ThreadX Tick value. */
#define MS_TO_TICK(ms)                                     ((ms) * (UX_PERIODIC_RATE) / 1000)


/* Define USBX Host Enum Thread Stack Size. */
#ifndef UX_HOST_ENUM_THREAD_STACK_SIZE
#define UX_HOST_ENUM_THREAD_STACK_SIZE                      UX_THREAD_STACK_SIZE
#endif

/* Define USBX Host Thread Stack Size. */
#ifndef UX_HOST_HCD_THREAD_STACK_SIZE
#define UX_HOST_HCD_THREAD_STACK_SIZE                       UX_THREAD_STACK_SIZE
#endif

/* Define USBX Host HNP Polling Thread Stack Size */
#ifndef UX_HOST_HNP_POLLING_THREAD_STACK
#define UX_HOST_HNP_POLLING_THREAD_STACK                    UX_THREAD_STACK_SIZE
#endif


/* Determine if error log is enabled.  */

#ifdef UX_ENABLE_DEBUG_LOG

#ifndef UX_DEBUG_LOG_SIZE
#define UX_DEBUG_LOG_SIZE                                   (1024 * 32)
#endif
   
/* Map the error log macros to internal USBX function.  */

#define UX_DEBUG_LOG(debug_location, debug_message, debug_code, debug_parameter_1, debug_parameter_2)  _ux_utility_debug_log((UCHAR *) debug_location, (UCHAR *) debug_message, (ULONG) debug_code, (ULONG) debug_parameter_1, (ULONG) debug_parameter_2);

VOID _ux_utility_debug_log(UCHAR *debug_location, UCHAR *debug_message, ULONG debug_code, ULONG debug_parameter_1, ULONG debug_parameter_2);

/* DEBUG LOG MESSAGES SHOULD BE WRITEN LIKE THIS IN THE CODE :    */
/* If error log is enabled, insert this error message into the log buffer.  */
/* UX_DEBUG_LOG("_ux_host_stack_rh_device_insertion", "Device insertion", port_index, port_index, 0) */


#else

/* If Log is not defined, map it to nothing so that debug messages can stay in the code.  */
#define UX_DEBUG_LOG(debug_location, debug_message, debug_code, debug_parameter_1, debug_parameter_2)
#endif    
    
/* Determine if tracing is enabled.  */

#ifdef TX_ENABLE_EVENT_TRACE

/* Trace is enabled. Remap calls so that interrupts can be disabled around the actual event logging.  */

#include "tx_trace.h"


/* Map the trace macros to internal USBX versions so we can get interrupt protection.  */

#define UX_TRACE_OBJECT_REGISTER(t,p,n,a,b)                 _ux_trace_object_register(t, (VOID *) p, (CHAR *) n, (ULONG) a, (ULONG) b);
#define UX_TRACE_OBJECT_UNREGISTER(o)                       _ux_trace_object_unregister((VOID *) o);
#define UX_TRACE_IN_LINE_INSERT(i,a,b,c,d,f,g,h)            _ux_trace_event_insert((ULONG) i, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) f, g, h);
#define UX_TRACE_EVENT_UPDATE(e,t,i,a,b,c,d)                _ux_trace_event_update((TX_TRACE_BUFFER_ENTRY *) e, (ULONG) t, (ULONG) i, (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d);


/* Define USBX trace prototypes.  */

VOID    _ux_trace_object_register(UCHAR object_type, VOID *object_ptr, CHAR *object_name, ULONG parameter_1, ULONG parameter_2);
VOID    _ux_trace_object_unregister(VOID *object_ptr);
VOID    _ux_trace_event_insert(ULONG event_id, ULONG info_field_1, ULONG info_field_2, ULONG info_field_3, ULONG info_field_4, ULONG filter, TX_TRACE_BUFFER_ENTRY **current_event, ULONG *current_timestamp);
VOID    _ux_trace_event_update(TX_TRACE_BUFFER_ENTRY *event, ULONG timestamp, ULONG event_id, ULONG info_field_1, ULONG info_field_2, ULONG info_field_3, ULONG info_field_4);


/* Define USBX event trace constants.  */

#define UX_TRACE_OBJECT_TYPE_BASE                                       20
#define UX_TRACE_HOST_OBJECT_TYPE_DEVICE                                (UX_TRACE_OBJECT_TYPE_BASE + 1)
#define UX_TRACE_HOST_OBJECT_TYPE_INTERFACE                             (UX_TRACE_OBJECT_TYPE_BASE + 2)
#define UX_TRACE_HOST_OBJECT_TYPE_ENDPOINT                              (UX_TRACE_OBJECT_TYPE_BASE + 3)
#define UX_TRACE_HOST_OBJECT_TYPE_CLASS_INSTANCE                        (UX_TRACE_OBJECT_TYPE_BASE + 4)
                                                                        
#define UX_TRACE_DEVICE_OBJECT_TYPE_DEVICE                              (UX_TRACE_OBJECT_TYPE_BASE + 5)
#define UX_TRACE_DEVICE_OBJECT_TYPE_INTERFACE                           (UX_TRACE_OBJECT_TYPE_BASE + 6)
#define UX_TRACE_DEVICE_OBJECT_TYPE_ENDPOINT                            (UX_TRACE_OBJECT_TYPE_BASE + 7)
#define UX_TRACE_DEVICE_OBJECT_TYPE_CLASS_INSTANCE                      (UX_TRACE_OBJECT_TYPE_BASE + 8)

/* Define event filters that can be used to selectively disable certain events or groups of events.  */

#define UX_TRACE_ALL_EVENTS                                             0x7F000000  /* All USBX events                          */
#define UX_TRACE_ERRORS                                                 0x01000000  /* USBX Errors events                       */ 
#define UX_TRACE_HOST_STACK_EVENTS                                      0x02000000  /* USBX Host Class Events                   */ 
#define UX_TRACE_DEVICE_STACK_EVENTS                                    0x04000000  /* USBX Device Class Events                 */ 
#define UX_TRACE_HOST_CONTROLLER_EVENTS                                 0x08000000  /* USBX Host Controller Events              */ 
#define UX_TRACE_DEVICE_CONTROLLER_EVENTS                               0x10000000  /* USBX Device Controllers Events           */ 
#define UX_TRACE_HOST_CLASS_EVENTS                                      0x20000000  /* USBX Host Class Events                   */ 
#define UX_TRACE_DEVICE_CLASS_EVENTS                                    0x40000000  /* USBX Device Class Events                 */ 


/* Define the trace events in USBX, if not defined.  */

/* Define the USBX host stack events.  */

#define UX_TRACE_HOST_STACK_EVENTS_BASE                                 600
#define UX_TRACE_HOST_STACK_CLASS_INSTANCE_CREATE                       (UX_TRACE_HOST_STACK_EVENTS_BASE + 1)               /* I1 = class           , I2 = class instance                                                       */    
#define UX_TRACE_HOST_STACK_CLASS_INSTANCE_DESTROY                      (UX_TRACE_HOST_STACK_EVENTS_BASE + 2)               /* I1 = class           , I2 = class instance                                                       */    
#define UX_TRACE_HOST_STACK_CONFIGURATION_DELETE                        (UX_TRACE_HOST_STACK_EVENTS_BASE + 3)               /* I1 = configuration                                                                               */    
#define UX_TRACE_HOST_STACK_CONFIGURATION_ENUMERATE                     (UX_TRACE_HOST_STACK_EVENTS_BASE + 4)               /* I1 = device                                                                                      */    
#define UX_TRACE_HOST_STACK_CONFIGURATION_INSTANCE_CREATE               (UX_TRACE_HOST_STACK_EVENTS_BASE + 5)               /* I1 = configuration                                                                               */    
#define UX_TRACE_HOST_STACK_CONFIGURATION_INSTANCE_DELETE               (UX_TRACE_HOST_STACK_EVENTS_BASE + 6)               /* I1 = configuration                                                                               */    
#define UX_TRACE_HOST_STACK_CONFIGURATION_SET                           (UX_TRACE_HOST_STACK_EVENTS_BASE + 7)               /* I1 = configuration                                                                               */    
#define UX_TRACE_HOST_STACK_DEVICE_ADDRESS_SET                          (UX_TRACE_HOST_STACK_EVENTS_BASE + 8)               /* I1 = device          , I2 = device address                                                       */    
#define UX_TRACE_HOST_STACK_DEVICE_CONFIGURATION_GET                    (UX_TRACE_HOST_STACK_EVENTS_BASE + 9)               /* I1 = device          , I2 = configuration                                                        */    
#define UX_TRACE_HOST_STACK_DEVICE_CONFIGURATION_SELECT                 (UX_TRACE_HOST_STACK_EVENTS_BASE + 10)              /* I1 = device          , I2 = configuration                                                        */    
#define UX_TRACE_HOST_STACK_DEVICE_DESCRIPTOR_READ                      (UX_TRACE_HOST_STACK_EVENTS_BASE + 11)              /* I1 = device                                                                                      */    
#define UX_TRACE_HOST_STACK_DEVICE_GET                                  (UX_TRACE_HOST_STACK_EVENTS_BASE + 12)              /* I1 = device index                                                                                */    
#define UX_TRACE_HOST_STACK_DEVICE_REMOVE                               (UX_TRACE_HOST_STACK_EVENTS_BASE + 13)              /* I1 = hcd             , I2 = parent          , I3 = port index        , I4 = device               */    
#define UX_TRACE_HOST_STACK_DEVICE_RESOURCE_FREE                        (UX_TRACE_HOST_STACK_EVENTS_BASE + 14)              /* I1 = device                                                                                      */    
#define UX_TRACE_HOST_STACK_ENDPOINT_INSTANCE_CREATE                    (UX_TRACE_HOST_STACK_EVENTS_BASE + 15)              /* I1 = device          , I2 = endpoint                                                             */    
#define UX_TRACE_HOST_STACK_ENDPOINT_INSTANCE_DELETE                    (UX_TRACE_HOST_STACK_EVENTS_BASE + 16)              /* I1 = device          , I2 = endpoint                                                             */    
#define UX_TRACE_HOST_STACK_ENDPOINT_RESET                              (UX_TRACE_HOST_STACK_EVENTS_BASE + 17)              /* I1 = device          , I2 = endpoint                                                             */    
#define UX_TRACE_HOST_STACK_ENDPOINT_TRANSFER_ABORT                     (UX_TRACE_HOST_STACK_EVENTS_BASE + 18)              /* I1 = endpoint                                                                                    */    
#define UX_TRACE_HOST_STACK_HCD_REGISTER                                (UX_TRACE_HOST_STACK_EVENTS_BASE + 19)              /* I1 = hcd name                                                                                    */    
#define UX_TRACE_HOST_STACK_INITIALIZE                                  (UX_TRACE_HOST_STACK_EVENTS_BASE + 20)              /*                                                                                                  */       
#define UX_TRACE_HOST_STACK_INTERFACE_ENDPOINT_GET                      (UX_TRACE_HOST_STACK_EVENTS_BASE + 21)              /* I1 = interface       , I2 = endpoint index                                                       */    
#define UX_TRACE_HOST_STACK_INTERFACE_INSTANCE_CREATE                   (UX_TRACE_HOST_STACK_EVENTS_BASE + 22)              /* I1 = interface                                                                                   */    
#define UX_TRACE_HOST_STACK_INTERFACE_INSTANCE_DELETE                   (UX_TRACE_HOST_STACK_EVENTS_BASE + 23)              /* I1 = interface                                                                                   */    
#define UX_TRACE_HOST_STACK_INTERFACE_SET                               (UX_TRACE_HOST_STACK_EVENTS_BASE + 24)              /* I1 = interface                                                                                   */    
#define UX_TRACE_HOST_STACK_INTERFACE_SETTING_SELECT                    (UX_TRACE_HOST_STACK_EVENTS_BASE + 25)              /* I1 = interface                                                                                   */    
#define UX_TRACE_HOST_STACK_NEW_CONFIGURATION_CREATE                    (UX_TRACE_HOST_STACK_EVENTS_BASE + 26)              /* I1 = device          , I2 = configuration                                                        */    
#define UX_TRACE_HOST_STACK_NEW_DEVICE_CREATE                           (UX_TRACE_HOST_STACK_EVENTS_BASE + 27)              /* I1 = hcd             , I2 = device owner    , I3 = port index        , I4 = device               */    
#define UX_TRACE_HOST_STACK_NEW_ENDPOINT_CREATE                         (UX_TRACE_HOST_STACK_EVENTS_BASE + 28)              /* I1 = interface       , I2 = endpoint                                                             */    
#define UX_TRACE_HOST_STACK_RH_CHANGE_PROCESS                           (UX_TRACE_HOST_STACK_EVENTS_BASE + 29)              /* I1 = port index                                                                                  */       
#define UX_TRACE_HOST_STACK_RH_DEVICE_EXTRACTION                        (UX_TRACE_HOST_STACK_EVENTS_BASE + 30)              /* I1 = hcd             , I2 = port index                                                           */    
#define UX_TRACE_HOST_STACK_RH_DEVICE_INSERTION                         (UX_TRACE_HOST_STACK_EVENTS_BASE + 31)              /* I1 = hcd             , I2 = port index                                                           */    
#define UX_TRACE_HOST_STACK_TRANSFER_REQUEST                            (UX_TRACE_HOST_STACK_EVENTS_BASE + 32)              /* I1 = device          , I2 = endpoint        , I3 = transfer request                              */    
#define UX_TRACE_HOST_STACK_TRANSFER_REQUEST_ABORT                      (UX_TRACE_HOST_STACK_EVENTS_BASE + 33)              /* I1 = device          , I2 = endpoint        , I3 = transfer request                              */    
                                                                                                                                                                                                                    
/* Define the USBX host class events.  */                                                                                                                                                                     

#define UX_TRACE_HOST_CLASS_EVENTS_BASE                                 650                                                                                                                                            
#define UX_TRACE_HOST_CLASS_ASIX_ACTIVATE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 1)               /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_ASIX_DEACTIVATE                             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 2)               /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_ASIX_INTERRUPT_NOTIFICATION                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 3)               /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_ASIX_READ                                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 4)               /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */       
#define UX_TRACE_HOST_CLASS_ASIX_WRITE                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 5)               /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                
                                                                                                                                                                                                                       
#define UX_TRACE_HOST_CLASS_AUDIO_ACTIVATE                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 10)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_AUDIO_CONTROL_VALUE_GET                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 11)              /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_AUDIO_CONTROL_VALUE_SET                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 12)              /* I1 = class instance  , I2 = audio control                                                        */                               
#define UX_TRACE_HOST_CLASS_AUDIO_DEACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 13)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_AUDIO_READ                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 14)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */       
#define UX_TRACE_HOST_CLASS_AUDIO_STREAMING_SAMPLING_GET                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 15)              /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_AUDIO_STREAMING_SAMPLING_SET                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 16)              /* I1 = class instance  , I2 = audio sampling                                                       */                                                              
#define UX_TRACE_HOST_CLASS_AUDIO_WRITE                                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 17)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */       
                                                                                                                                                                                                                          
#define UX_TRACE_HOST_CLASS_CDC_ACM_ACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 20)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_CDC_ACM_DEACTIVATE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 21)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_SET_LINE_CODING               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 22)              /* I1 = class instance  , I2 = parameter                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_GET_LINE_CODING               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 23)              /* I1 = class instance  , I2 = parameter                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_SET_LINE_STATE                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 24)              /* I1 = class instance  , I2 = parameter                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_SEND_BREAK                    (UX_TRACE_HOST_CLASS_EVENTS_BASE + 25)              /* I1 = class instance  , I2 = parameter                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_ABORT_IN_PIPE                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 26)              /* I1 = class instance  , I2 = endpoint                                                             */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_ABORT_OUT_PIPE                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 27)              /* I1 = class instance  , I2 = endpointr                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_NOTIFICATION_CALLBACK         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 28)              /* I1 = class instance  , I2 = parameter                                                            */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_IOCTL_GET_DEVICE_STATUS             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 29)              /* I1 = class instance  , I2 = device status                                                        */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_READ                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 30)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */
#define UX_TRACE_HOST_CLASS_CDC_ACM_RECEPTION_START                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 31)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_RECEPTION_STOP                      (UX_TRACE_HOST_CLASS_EVENTS_BASE + 32)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_CDC_ACM_WRITE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 33)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */
                                                                                                                                                                                                                          
#define UX_TRACE_HOST_CLASS_CDC_ECM_ACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 35)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_CDC_ECM_DEACTIVATE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 36)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_CDC_ECM_READ                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 37)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */
#define UX_TRACE_HOST_CLASS_CDC_ECM_WRITE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 38)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */
#define UX_TRACE_HOST_CLASS_CDC_ECM_INTERRUPT_NOTIFICATION              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 39)              /* I1 = class instance                                                                              */                               
                                 
#define UX_TRACE_HOST_CLASS_HID_ACTIVATE                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 40)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_HID_CLIENT_REGISTER                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 41)              /* I1 = hid client name                                                                             */                               
#define UX_TRACE_HOST_CLASS_HID_DEACTIVATE                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 42)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_HID_IDLE_GET                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 43)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_HID_IDLE_SET                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 44)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_HID_KEYBOARD_ACTIVATE                       (UX_TRACE_HOST_CLASS_EVENTS_BASE + 45)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_KEYBOARD_DEACTIVATE                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 46)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_MOUSE_ACTIVATE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 47)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_MOUSE_DEACTIVATE                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 48)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_REMOTE_CONTROL_ACTIVATE                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 49)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_REMOTE_CONTROL_DEACTIVATE               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 50)              /* I1 = class instance  , I2 = hid client instance                                                  */                               
#define UX_TRACE_HOST_CLASS_HID_REPORT_GET                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 51)              /* I1 = class instance  , I2 = client report                                                        */                               
#define UX_TRACE_HOST_CLASS_HID_REPORT_SET                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 52)              /* I1 = class instance  , I2 = client report                                                        */                               
#define UX_TRACE_HOST_CLASS_HID_REMOTE_CONTROL_CALLBACK                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 53)              /* I1 = client instance , I2 = remote control instance                                              */                               
                                                                                                                                                                                                                       
#define UX_TRACE_HOST_CLASS_HUB_ACTIVATE                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 60)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_HUB_CHANGE_DETECT                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 62)              /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_HUB_PORT_CHANGE_CONNECTION_PROCESS          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 63)              /* I1 = class instance  , I2 = port            , I3 = port status                                   */
#define UX_TRACE_HOST_CLASS_HUB_PORT_CHANGE_ENABLE_PROCESS              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 64)              /* I1 = class instance  , I2 = port            , I3 = port status                                   */                                      
#define UX_TRACE_HOST_CLASS_HUB_PORT_CHANGE_OVER_CURRENT_PROCESS        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 65)              /* I1 = class instance  , I2 = port            , I3 = port status                                   */
#define UX_TRACE_HOST_CLASS_HUB_PORT_CHANGE_RESET_PROCESS               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 66)              /* I1 = class instance  , I2 = port            , I3 = port status                                   */
#define UX_TRACE_HOST_CLASS_HUB_PORT_CHANGE_SUSPEND_PROCESS             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 67)              /* I1 = class instance  , I2 = port            , I3 = port status                                   */
#define UX_TRACE_HOST_CLASS_HUB_DEACTIVATE                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 68)              /* I1 = class instance                                                                              */       
                                                                                                                                                                                                                            
#define UX_TRACE_HOST_CLASS_PIMA_ACTIVATE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 70)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_PIMA_DEACTIVATE                             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 71)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_PIMA_DEVICE_INFO_GET                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 72)              /* I1 = class instance  , I2 = pima device                                                          */       
#define UX_TRACE_HOST_CLASS_PIMA_DEVICE_RESET                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 73)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_PIMA_NOTIFICATION                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 74)              /* I1 = class instance  , I2 = event code      , I3 = transaction ID    , I4 = parameter1           */                               
#define UX_TRACE_HOST_CLASS_PIMA_NUM_OBJECTS_GET                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 75)              /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_CLOSE                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 76)              /* I1 = class instance  , I2 = object                                                               */                                      
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_COPY                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 77)              /* I1 = class instance  , I2 = object handle                                                        */                                      
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_DELETE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 78)              /* I1 = class instance  , I2 = object handle                                                        */                                                                     
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_GET                             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 79)              /* I1 = class instance  , I2 = object handle   , I3 = object                                        */                                                                                                    
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_INFO_GET                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 80)              /* I1 = class instance  , I2 = object handle   , I3 = object                                        */                                                                                                                                   
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_INFO_SEND                       (UX_TRACE_HOST_CLASS_EVENTS_BASE + 81)              /* I1 = class instance  , I2 = object                                                               */                               
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_MOVE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 82)              /* I1 = class instance  , I2 = object handle                                                        */                               
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_SEND                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 83)              /* I1 = class instance  , I2 = object          , I3 = object_buffer     , I4 = object length        */                               
#define UX_TRACE_HOST_CLASS_PIMA_OBJECT_TRANSFER_ABORT                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 84)              /* I1 = class instance  , I2 = object handle   , I3 = object                                        */                               
#define UX_TRACE_HOST_CLASS_PIMA_READ                                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 85)              /* I1 = class instance  , I2 = data pointer    , I3 = data length                                   */                               
#define UX_TRACE_HOST_CLASS_PIMA_REQUEST_CANCEL                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 86)              /* I1 = class instance                                                                              */
#define UX_TRACE_HOST_CLASS_PIMA_SESSION_CLOSE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 87)              /* I1 = class instance  , I2 = pima session                                                         */                                                              
#define UX_TRACE_HOST_CLASS_PIMA_SESSION_OPEN                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 88)              /* I1 = class instance  , I2 = pima session                                                         */                                                                                             
#define UX_TRACE_HOST_CLASS_PIMA_STORAGE_IDS_GET                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 89)              /* I1 = class instance  , I2 = storage ID array, I3 = storage ID length                             */                               
#define UX_TRACE_HOST_CLASS_PIMA_STORAGE_INFO_GET                       (UX_TRACE_HOST_CLASS_EVENTS_BASE + 90)              /* I1 = class instance  , I2 = storage ID      , I3 = storage                                       */                               
#define UX_TRACE_HOST_CLASS_PIMA_THUMB_GET                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 91)              /* I1 = class instance  , I2 = object handle                                                        */                               
#define UX_TRACE_HOST_CLASS_PIMA_WRITE                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 92)              /* I1 = class instance  , I2 = data pointer    , I3 = data length                                   */                               
                                                                                                                                                                                                                            
#define UX_TRACE_HOST_CLASS_PRINTER_ACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 100)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_PRINTER_DEACTIVATE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 101)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_PRINTER_NAME_GET                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 102)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PRINTER_READ                                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 103)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_PRINTER_WRITE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 104)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_PRINTER_SOFT_RESET                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 105)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PRINTER_STATUS_GET                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 106)             /* I1 = class instance  , I2 = printer status                                                       */                                      
                                                                                                                                                                                                                              
#define UX_TRACE_HOST_CLASS_PROLIFIC_ACTIVATE                           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 110)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_PROLIFIC_DEACTIVATE                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 111)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_SET_LINE_CODING              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 112)             /* I1 = class instance  , I2 = parameter                                                            */                             
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_GET_LINE_CODING              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 113)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_SET_LINE_STATE               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 114)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_PURGE                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 115)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_SEND_BREAK                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 116)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_ABORT_IN_PIPE                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 117)             /* I1 = class instance  , I2 = endpoint                                                             */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_ABORT_OUT_PIPE               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 118)             /* I1 = class instance  , I2 = endpointr                                                            */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_REPORT_DEVICE_STATUS_CHANGE  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 119)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_IOCTL_GET_DEVICE_STATUS            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 120)             /* I1 = class instance  , I2 = device status                                                        */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_READ                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 121)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_RECEPTION_START                    (UX_TRACE_HOST_CLASS_EVENTS_BASE + 122)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_RECEPTION_STOP                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 123)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_PROLIFIC_WRITE                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 124)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
                                                                                                                                                                                                                          
#define UX_TRACE_HOST_CLASS_STORAGE_ACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 130)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_STORAGE_DEACTIVATE                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 131)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_CAPACITY_GET                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 132)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_FORMAT_CAPACITY_GET           (UX_TRACE_HOST_CLASS_EVENTS_BASE + 133)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_MOUNT                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 134)             /* I1 = class instance  , I2 = sector                                                               */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_OPEN                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 135)             /* I1 = class instance  , I2 = media                                                                */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_READ                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 136)             /* I1 = class instance  , I2 = sector start    , I3 = sector count      , I4 = data pointer         */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_MEDIA_WRITE                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 137)             /* I1 = class instance  , I2 = sector start    , I3 = sector count      , I4 = data pointer         */                                       
#define UX_TRACE_HOST_CLASS_STORAGE_REQUEST_SENSE                       (UX_TRACE_HOST_CLASS_EVENTS_BASE + 138)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_START_STOP                          (UX_TRACE_HOST_CLASS_EVENTS_BASE + 139)             /* I1 = class instance  , I2 = start stop signal                                                    */                                      
#define UX_TRACE_HOST_CLASS_STORAGE_UNIT_READY_TEST                     (UX_TRACE_HOST_CLASS_EVENTS_BASE + 140)             /* I1 = class instance                                                                              */                                      
                                                                                                                                                                                                                              
#define UX_TRACE_HOST_CLASS_DPUMP_ACTIVATE                              (UX_TRACE_HOST_CLASS_EVENTS_BASE + 150)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_DPUMP_DEACTIVATE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 151)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_DPUMP_READ                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 152)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_DPUMP_WRITE                                 (UX_TRACE_HOST_CLASS_EVENTS_BASE + 153)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
                                                                                                                                                                                                                              
#define UX_TRACE_HOST_CLASS_SWAR_ACTIVATE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 160)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_SWAR_DEACTIVATE                             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 161)              /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_SWAR_IOCTL_ABORT_IN_PIPE                    (UX_TRACE_HOST_CLASS_EVENTS_BASE + 162)              /* I1 = class instance  , I2 = endpoint                                                             */                               
#define UX_TRACE_HOST_CLASS_SWAR_IOCTL_ABORT_OUT_PIPE                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 163)              /* I1 = class instance  , I2 = endpointr                                                            */                               
#define UX_TRACE_HOST_CLASS_SWAR_READ                                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 164)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */
#define UX_TRACE_HOST_CLASS_SWAR_RECEPTION_START                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 165)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_SWAR_RECEPTION_STOP                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 166)              /* I1 = class instance                                                                              */                               
#define UX_TRACE_HOST_CLASS_SWAR_WRITE                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 167)              /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */

#define UX_TRACE_HOST_CLASS_GSER_ACTIVATE                               (UX_TRACE_HOST_CLASS_EVENTS_BASE + 170)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_GSER_DEACTIVATE                             (UX_TRACE_HOST_CLASS_EVENTS_BASE + 171)             /* I1 = class instance                                                                              */       
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_SET_LINE_CODING                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 172)             /* I1 = class instance  , I2 = parameter                                                            */                             
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_GET_LINE_CODING                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 173)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_SET_LINE_STATE                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 174)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_PURGE                            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 175)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_SEND_BREAK                       (UX_TRACE_HOST_CLASS_EVENTS_BASE + 176)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_ABORT_IN_PIPE                    (UX_TRACE_HOST_CLASS_EVENTS_BASE + 177)             /* I1 = class instance  , I2 = endpoint                                                             */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_ABORT_OUT_PIPE                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 178)             /* I1 = class instance  , I2 = endpointr                                                            */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_REPORT_DEVICE_STATUS_CHANGE      (UX_TRACE_HOST_CLASS_EVENTS_BASE + 179)             /* I1 = class instance  , I2 = parameter                                                            */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_GET_DEVICE_STATUS                (UX_TRACE_HOST_CLASS_EVENTS_BASE + 180)             /* I1 = class instance  , I2 = device status                                                        */                                      
#define UX_TRACE_HOST_CLASS_GSER_IOCTL_NOTIFICATION_CALLBACK            (UX_TRACE_HOST_CLASS_EVENTS_BASE + 181)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_GSER_READ                                   (UX_TRACE_HOST_CLASS_EVENTS_BASE + 182)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      
#define UX_TRACE_HOST_CLASS_GSER_RECEPTION_START                        (UX_TRACE_HOST_CLASS_EVENTS_BASE + 183)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_GSER_RECEPTION_STOP                         (UX_TRACE_HOST_CLASS_EVENTS_BASE + 184)             /* I1 = class instance                                                                              */                                      
#define UX_TRACE_HOST_CLASS_GSER_WRITE                                  (UX_TRACE_HOST_CLASS_EVENTS_BASE + 185)             /* I1 = class instance  , I2 = data pointer    , I3 = requested length                              */                                      

/* Define the USBX device stack events.  */                                                                                                                                                                             

#define UX_TRACE_DEVICE_STACK_EVENTS_BASE                               850                                                                                                                                                   
#define UX_TRACE_DEVICE_STACK_ALTERNATE_SETTING_GET                     (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 1)             /* I1 = interface value                                                                             */                                      
#define UX_TRACE_DEVICE_STACK_ALTERNATE_SETTING_SET                     (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 2)             /* I1 = interface value , I2 = alternate setting value                                              */                                      
#define UX_TRACE_DEVICE_STACK_CLASS_REGISTER                            (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 3)             /* I1 = class name      , I2 = interface number, I3 = parameter                                     */
#define UX_TRACE_DEVICE_STACK_CLEAR_FEATURE                             (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 4)             /* I1 = request type    , I2 = request value   , I3 = request index                                 */
#define UX_TRACE_DEVICE_STACK_CONFIGURATION_GET                         (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 5)             /* I1 = configuration value                                                                         */
#define UX_TRACE_DEVICE_STACK_CONFIGURATION_SET                         (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 5)             /* I1 = configuration value                                                                         */
#define UX_TRACE_DEVICE_STACK_CONNECT                                   (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 6)             /*                                                                                                  */                                      
#define UX_TRACE_DEVICE_STACK_DESCRIPTOR_SEND                           (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 7)             /* I1 = descriptor type , I2 = request index                                                        */                                      
#define UX_TRACE_DEVICE_STACK_DISCONNECT                                (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 8)             /* I1 = device                                                                                      */
#define UX_TRACE_DEVICE_STACK_ENDPOINT_STALL                            (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 9)             /* I1 = endpoint                                                                                    */
#define UX_TRACE_DEVICE_STACK_GET_STATUS                                (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 10)            /* I1 = request type    , I2 = request value   , I3 = request index                                 */                                      
#define UX_TRACE_DEVICE_STACK_HOST_WAKEUP                               (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 11)            /*                                                                                                  */                                      
#define UX_TRACE_DEVICE_STACK_INITIALIZE                                (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 12)            /*                                                                                                  */                                      
#define UX_TRACE_DEVICE_STACK_INTERFACE_DELETE                          (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 13)            /* I1 = interface                                                                                   */                                      
#define UX_TRACE_DEVICE_STACK_INTERFACE_GET                             (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 14)            /* I1 = interface value                                                                             */
#define UX_TRACE_DEVICE_STACK_INTERFACE_SET                             (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 15)            /* I1 = alternate setting value                                                                     */
#define UX_TRACE_DEVICE_STACK_SET_FEATURE                               (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 16)            /* I1 = request value   , I2 = request index                                                        */
#define UX_TRACE_DEVICE_STACK_TRANSFER_ABORT                            (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 17)            /* I1 = transfer request, I2 = completion code                                                      */
#define UX_TRACE_DEVICE_STACK_TRANSFER_ALL_REQUEST_ABORT                (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 18)            /* I1 = endpoint        , I2 = completion code                                                      */
#define UX_TRACE_DEVICE_STACK_TRANSFER_REQUEST                          (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 19)            /* I1 = transfer request                                                                            */
#define UX_TRACE_DEVICE_STACK_MICROSOFT_EXTENSION_REGISTER              (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 20)            /* I1 = transfer request                                                                            */
#define UX_TRACE_DEVICE_STACK_CLASS_UNREGISTER                          (UX_TRACE_DEVICE_STACK_EVENTS_BASE + 21)            /* I1 = class name                                                                                  */
                                                                                                                                                                                                                              
/* Define the USBX device stack events first.  */                                                                                                                                                                             

#define UX_TRACE_DEVICE_CLASS_EVENTS_BASE                               900                                                                                                                                                   
#define UX_TRACE_DEVICE_CLASS_DPUMP_ACTIVATE                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 1)             /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_DPUMP_DEACTIVATE                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 2)             /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_DPUMP_READ                                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 3)             /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_DPUMP_WRITE                               (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 4)             /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_DPUMP_CHANGE                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 4)             /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
                                                                                                                                                                                                                              
#define UX_TRACE_DEVICE_CLASS_CDC_ACM_ACTIVATE                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 10)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_CDC_ACM_DEACTIVATE                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 11)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_CDC_ACM_READ                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 12)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_CDC_ACM_WRITE                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 13)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
                                                                                                                                                                                                                              
#define UX_TRACE_DEVICE_CLASS_HID_ACTIVATE                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 20)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_HID_DEACTIVATE                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 21)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_HID_EVENT_GET                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 22)            /* I1 = class instance  , I2 = hid event                                                            */
#define UX_TRACE_DEVICE_CLASS_HID_EVENT_SET                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 23)            /* I1 = class instance  , I2 = hid event                                                            */
#define UX_TRACE_DEVICE_CLASS_HID_REPORT_GET                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 24)            /* I1 = class instance  , I2 = descriptor type , I3 = request index                                 */
#define UX_TRACE_DEVICE_CLASS_HID_REPORT_SET                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 25)            /* I1 = class instance  , I2 = descriptor type , I3 = request index                                 */
#define UX_TRACE_DEVICE_CLASS_HID_DESCRIPTOR_SEND                       (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 26)            /* I1 = class instance  , I2 = descriptor type , I3 = request index                                 */
                                                                                                                                                                                                                              
#define UX_TRACE_DEVICE_CLASS_PIMA_ACTIVATE                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 30)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_PIMA_DEACTIVATE                           (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 31)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_PIMA_DEVICE_INFO_SEND                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 32)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_PIMA_EVENT_GET                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 33)            /* I1 = class instance  , I2 = pima event                                                           */       
#define UX_TRACE_DEVICE_CLASS_PIMA_EVENT_SET                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 34)            /* I1 = class instance  , I2 = pima event                                                           */       
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_ADD                           (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 35)            /* I1 = class instance  , I2 = object handle                                                        */       
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_DATA_GET                      (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 36)            /* I1 = class instance  , I2 = object handle                                                        */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_DATA_SEND                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 37)            /* I1 = class instance  , I2 = object handle                                                        */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_DELETE                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 38)            /* I1 = class instance  , I2 = object handle                                                        */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_HANDLES_SEND                  (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 39)            /* I1 = class instance  , I2 = storage id      , I3 = object format code, I4 = object association   */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_INFO_GET                      (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 40)            /* I1 = class instance  , I2 = object handle                                                        */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECT_INFO_SEND                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 41)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECTS_NUMBER_SEND                  (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 42)            /* I1 = class instance  , I2 = storage id      , I3 = object format code, I4 = object association   */
#define UX_TRACE_DEVICE_CLASS_PIMA_PARTIAL_OBJECT_DATA_GET              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 43)            /* I1 = class instance  , I2 = object handle   , I3 = offset requested  , I4 = length requested     */
#define UX_TRACE_DEVICE_CLASS_PIMA_RESPONSE_SEND                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 44)            /* I1 = class instance  , I2 = response code   , I3 = number parameter  , I4 = pima parameter 1     */
#define UX_TRACE_DEVICE_CLASS_PIMA_STORAGE_ID_SEND                      (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 45)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_STORAGE_INFO_SEND                    (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 46)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_DEVICE_PROP_DESC_GET             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 47)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_DEVICE_PROP_VALUE                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 48)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_DEVICE_PROP_VALUE_SET            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 49)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_OBJECT_PROP_DESC                 (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 50)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_OBJECT_PROP_VALUE                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 51)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECTS_PROPS_SUPPORTED_GET          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 52)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_GET_OBJECT_REFERENCES                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 53)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_OBJECTS_PROPS_SUPPORTED_SET          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 54)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_SET_OBJECT_REFERENCES                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 55)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_STORAGE_FORMAT                       (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 56)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_DEVICE_RESET                         (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 57)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_PIMA_SET_OBJECT_PROP_VALUE                (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 58)            /* I1 = class instance                                                                              */
                                                                                                                                                                                                                       
#define UX_TRACE_DEVICE_CLASS_RNDIS_ACTIVATE                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 60)            /* I1 = class instance                                                                              */         
#define UX_TRACE_DEVICE_CLASS_RNDIS_DEACTIVATE                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 61)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_RNDIS_PACKET_RECEIVE                      (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 62)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_RNDIS_PACKET_TRANSMIT                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 63)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_RNDIS_MSG_QUERY                           (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 64)            /* I1 = class instance  , I2 = rndis OID                                                            */
#define UX_TRACE_DEVICE_CLASS_RNDIS_MSG_KEEP_ALIVE                      (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 65)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_RNDIS_MSG_RESET                           (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 66)            /* I1 = class instance                                                                              */
#define UX_TRACE_DEVICE_CLASS_RNDIS_MSG_SET                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 67)            /* I1 = class instance  , I2 = rndis OID                                                            */
                                                                                                                                                                                                                       
#define UX_TRACE_DEVICE_CLASS_STORAGE_ACTIVATE                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 70)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_DEACTIVATE                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 71)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_FORMAT                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 72)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_INQUIRY                           (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 73)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_MODE_SELECT                       (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 74)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_MODE_SENSE                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 75)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_PREVENT_ALLOW_MEDIA_REMOVAL       (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 76)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_READ                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 77)            /* I1 = class instance  , I2 = lun             , I3 = sector              , I4 = number sectors     */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_READ_CAPACITY                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 78)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_READ_FORMAT_CAPACITY              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 79)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_READ_TOC                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 80)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_REQUEST_SENSE                     (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 81)            /* I1 = class instance  , I2 = lun             , I3 = sense key           , I4 = code               */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_TEST_READY                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 82)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_START_STOP                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 83)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_VERIFY                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 84)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_WRITE                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 85)            /* I1 = class instance  , I2 = lun             , I3 = sector              , I4 = number sectors     */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_GET_CONFIGURATION                 (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 86)            /* I1 = class instance  , I2 = lun                                                                  */       
#define UX_TRACE_DEVICE_CLASS_STORAGE_SYNCHRONIZE_CACHE                 (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 87)            /* I1 = class instance  , I2 = lun             , I3 = sector              , I4 = number sectors     */
#define UX_TRACE_DEVICE_CLASS_STORAGE_OTHER                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 88)            /* I1 = class instance  , I2 = lun                                                                  */       

#define UX_TRACE_DEVICE_CLASS_CDC_ECM_ACTIVATE                          (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 90)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_DEACTIVATE                        (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 91)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_CHANGE                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 92)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_READ                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 93)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_WRITE                             (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 94)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_PACKET_TRANSMIT                   (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 95)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
#define UX_TRACE_DEVICE_CLASS_CDC_ECM_PACKET_RECEIVE                    (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 96)            /* I1 = class instance  , I2 = buffer          , I3 = requested_length                              */
                                                                                                                                                                                                                              
#define UX_TRACE_DEVICE_CLASS_DFU_ACTIVATE                              (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 97)            /* I1 = class instance                                                                              */       
#define UX_TRACE_DEVICE_CLASS_DFU_DEACTIVATE                            (UX_TRACE_DEVICE_CLASS_EVENTS_BASE + 98)            /* I1 = class instance                                                                              */       

/* Define the USBX Error Event.  */

#define UX_TRACE_ERROR                                                  999


#else
#define UX_TRACE_OBJECT_REGISTER(t,p,n,a,b)                 
#define UX_TRACE_OBJECT_UNREGISTER(o)                       
#define UX_TRACE_IN_LINE_INSERT(i,a,b,c,d,f,g,h)            
#define UX_TRACE_EVENT_UPDATE(e,t,i,a,b,c,d)                
#endif


/* Define the system level for error trapping. */
#define UX_SYSTEM_LEVEL_INTERRUPT                                       1
#define UX_SYSTEM_LEVEL_THREAD                                          2

/* Define the system context for error trapping. */
#define UX_SYSTEM_CONTEXT_HCD                                           1
#define UX_SYSTEM_CONTEXT_DCD                                           2
#define UX_SYSTEM_CONTEXT_INIT                                          3
#define UX_SYSTEM_CONTEXT_ENUMERATOR                                    4
#define UX_SYSTEM_CONTEXT_ROOT_HUB                                      5
#define UX_SYSTEM_CONTEXT_HUB                                           6
#define UX_SYSTEM_CONTEXT_CLASS                                         7
#define UX_SYSTEM_CONTEXT_UTILITY                                       8
#define UX_SYSTEM_CONTEXT_DEVICE_STACK                                  9


/* Defines the number of ThreadX timer ticks per seconds. By default, the ThreadX timer tick is 10ms, 
   so the default value for this constant is 100.  If TX_TIMER_TICKS_PER_SECOND is defined,
   this value is derived from TX_TIMER_TICKS_PER_SECOND.  */

#ifndef UX_PERIODIC_RATE
#ifdef TX_TIMER_TICKS_PER_SECOND
#define UX_PERIODIC_RATE                                                (TX_TIMER_TICKS_PER_SECOND)
#else
#define UX_PERIODIC_RATE                                                100
#endif
#endif

/* Define basic USBX constants.  */

#define UX_NULL                                                         ((void*)0)
#define UX_TRUE                                                         1
#define UX_FALSE                                                        0
#define UX_MAX_TT                                                       8
#define UX_TT_MASK                                                      0x1FF
#define UX_TT_BANDWIDTH                                                 1200
#define UX_SLAVE_ENDPOINT_DEFAULT_BUFFER_SIZE                           256
#define UX_REGULAR_MEMORY                                               0
#define UX_CACHE_SAFE_MEMORY                                            1


/* Define USBX command request constants.  */

#define UX_SETUP_REQUEST_TYPE                                           0
#define UX_SETUP_REQUEST                                                1
#define UX_SETUP_VALUE                                                  2
#define UX_SETUP_INDEX                                                  4
#define UX_SETUP_LENGTH                                                 6
#define UX_SETUP_SIZE                                                   8
                                                                        
                                                                        
/* Define USBX standard commands.  */                                   
                                                                        
#define UX_GET_STATUS                                                   0
#define UX_CLEAR_FEATURE                                                1
#define UX_SET_FEATURE                                                  3 
#define UX_SET_ADDRESS                                                  5
#define UX_GET_DESCRIPTOR                                               6
#define UX_SET_DESCRIPTOR                                               7
#define UX_GET_CONFIGURATION                                            8
#define UX_SET_CONFIGURATION                                            9
#define UX_GET_INTERFACE                                                10
#define UX_SET_INTERFACE                                                11
#define UX_SYNCH_FRAME                                                  12
                                                                        
                                                                        
/* Define USBX command sub constants.  */                               
                                                                        
#define UX_ENDPOINT_HALT                                                0
                                                                        
/* Define USBX feature selector constants.  */
#define UX_REQUEST_FEATURE_ENDPOINT_HALT 0
#define UX_REQUEST_FEATURE_DEVICE_REMOTE_WAKEUP 1
#define UX_REQUEST_FEATURE_TEST_MODE 2

/* Define Generic USBX constants.  */                                   
                                                                        
#define UX_WAIT_FOREVER                                                 0xffffffff
#define UX_UNUSED                                                       0
#define UX_USED                                                         1
#define UX_MEMORY_UNUSED                                                0x12345678
#define UX_MEMORY_USED                                                  0x87654321
#define UX_NO_ALIGN                                                     0
#define UX_ALIGN_16                                                     0x0f
#define UX_ALIGN_MIN                                                    0x0f
#define UX_ALIGN_32                                                     0x1f
#define UX_ALIGN_64                                                     0x3f
#define UX_ALIGN_128                                                    0x7f 
#define UX_ALIGN_256                                                    0xff
#define UX_ALIGN_512                                                    0x1ff
#define UX_ALIGN_1024                                                   0x3ff
#define UX_ALIGN_2048                                                   0x7ff
#define UX_ALIGN_4096                                                   0xfff
#define UX_SAFE_ALIGN                                                   0xffffffff
#define UX_MAX_SCATTER_GATHER_ALIGNMENT                                 4096
                                                                        
#define UX_MAX_USB_DEVICES                                              127
                                                                        
#define UX_ENDPOINT_DIRECTION                                           0x80
#define UX_ENDPOINT_IN                                                  0x80
#define UX_ENDPOINT_OUT                                                 0x00
                                                                        
#define UX_MASK_ENDPOINT_TYPE                                           3
#define UX_CONTROL_ENDPOINT                                             0
#define UX_ISOCHRONOUS_ENDPOINT                                         1
#define UX_BULK_ENDPOINT                                                2
#define UX_INTERRUPT_ENDPOINT                                           3
                                                                        
#define UX_ISOCHRONOUS_ENDPOINT_IN                                      0x81
#define UX_ISOCHRONOUS_ENDPOINT_OUT                                     0x01
#define UX_BULK_ENDPOINT_IN                                             0x82
#define UX_BULK_ENDPOINT_OUT                                            0x02
#define UX_INTERRUPT_ENDPOINT_IN                                        0x83
#define UX_INTERRUPT_ENDPOINT_OUT                                       0x03
                                                                        
#define UX_MAX_PACKET_SIZE_MASK                                         0x7ff
#define UX_MAX_NUMBER_OF_TRANSACTIONS_MASK                              0x1800
#define UX_MAX_NUMBER_OF_TRANSACTIONS_SHIFT                             11

#define UX_REQUEST_DIRECTION                                            0x80
#define UX_REQUEST_IN                                                   0x80
#define UX_REQUEST_OUT                                                  0x00
                                                                        
#define UX_REQUEST_TYPE                                                 0x60
#define UX_REQUEST_TYPE_STANDARD                                        0x00
#define UX_REQUEST_TYPE_CLASS                                           0x20
#define UX_REQUEST_TYPE_VENDOR                                          0x40
                                                                        
#define UX_REQUEST_TARGET                                               0x03
#define UX_REQUEST_TARGET_DEVICE                                        0x00
#define UX_REQUEST_TARGET_INTERFACE                                     0x01
#define UX_REQUEST_TARGET_ENDPOINT                                      0x02
#define UX_REQUEST_TARGET_OTHER                                         0x03
                                                                        
#define UX_DEVICE_RESET                                                 0
#define UX_DEVICE_ATTACHED                                              1
#define UX_DEVICE_ADDRESSED                                             2
#define UX_DEVICE_CONFIGURED                                            3
#define UX_DEVICE_SUSPENDED                                             4
#define UX_DEVICE_RESUMED                                               5
#define UX_DEVICE_SELF_POWERED_STATE                                    6
#define UX_DEVICE_BUS_POWERED_STATE                                     7
#define UX_DEVICE_REMOTE_WAKEUP                                         8
#define UX_DEVICE_BUS_RESET_COMPLETED                                   9
#define UX_DEVICE_REMOVED                                               10
#define UX_DEVICE_FORCE_DISCONNECT                                      11
                                                                        
#define UX_ENDPOINT_RESET                                               0
#define UX_ENDPOINT_RUNNING                                             1
#define UX_ENDPOINT_HALTED                                              2
                                                                        
#define UX_DEVICE_DESCRIPTOR_ITEM                                       1
#define UX_CONFIGURATION_DESCRIPTOR_ITEM                                2
#define UX_STRING_DESCRIPTOR_ITEM                                       3
#define UX_INTERFACE_DESCRIPTOR_ITEM                                    4
#define UX_ENDPOINT_DESCRIPTOR_ITEM                                     5
#define UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM                             6
#define UX_OTHER_SPEED_DESCRIPTOR_ITEM                                  7
#define UX_OTG_DESCRIPTOR_ITEM                                          9
#define UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ITEM                        11
#define UX_DFU_FUNCTIONAL_DESCRIPTOR_ITEM                               0x21
#define UX_HUB_DESCRIPTOR_ITEM                                          0x29
                                                                        

#define UX_CONTROL_TRANSFER_TIMEOUT                                     1000
#define UX_NON_CONTROL_TRANSFER_TIMEOUT                                 5000
#define UX_PORT_ENABLE_WAIT                                             50 
#define UX_DEVICE_ADDRESS_SET_WAIT                                      50
#define UX_HIGH_SPEED_DETECTION_HANDSHAKE_SUSPEND_WAIT                  200
#define UX_ENUMERATION_THREAD_WAIT                                      200


/* USBX 5.8 BACKWARD COMPATIBILITY DEFINITIONS. THESE DEFINITIONS ARE NOW OBSOLETE
   BUT DEFINED HERE FOR COMPATIBILITY REASONS.  */
   
#ifndef UX_CONTROL_TRANSFER_TIMEOUT_IN_MS
#define UX_CONTROL_TRANSFER_TIMEOUT_IN_MS                               10000
#endif 

#ifndef UX_NON_CONTROL_TRANSFER_TIMEOUT_IN_MS
#define UX_NON_CONTROL_TRANSFER_TIMEOUT_IN_MS                           50000
#endif 

#ifndef UX_PORT_ENABLE_WAIT_IN_MS          
#define UX_PORT_ENABLE_WAIT_IN_MS                                       500
#endif

#ifndef UX_DEVICE_ADDRESS_SET_WAIT_IN_MS                         
#define UX_DEVICE_ADDRESS_SET_WAIT_IN_MS                                500
#endif

#ifndef UX_HIGH_SPEED_DETECTION_HANDSHAKE_SUSPEND_WAIT_IN_MS            
#define UX_HIGH_SPEED_DETECTION_HANDSHAKE_SUSPEND_WAIT_IN_MS            2000
#endif

/* END OF 5.8 BACKWARD COMPATIBILITY DEFINITIONS. */
                                                                        
#define UX_TRANSFER_PHASE_SETUP                                         1
#define UX_TRANSFER_PHASE_DATA_IN                                       2
#define UX_TRANSFER_PHASE_DATA_OUT                                      3
#define UX_TRANSFER_PHASE_STATUS_IN                                     4
#define UX_TRANSFER_PHASE_STATUS_OUT                                    5
                                                                        
#define UX_DEVICE_INSERTION                                             1
#define UX_DEVICE_REMOVAL                                               2
#define UX_HID_CLIENT_INSERTION                                         3
#define UX_HID_CLIENT_REMOVAL                                           4
                                                                        
                                                                        
/* Define USBX transfer request status constants.  */                   
                                                                        
#define UX_TRANSFER_STATUS_NOT_PENDING                                  0
#define UX_TRANSFER_STATUS_PENDING                                      1
#define UX_TRANSFER_STATUS_COMPLETED                                    2 
#define UX_TRANSFER_STATUS_ABORT                                        4
                                                                        
/* Define USBX device power constants.  */                              
                                                                        
#define UX_DEVICE_BUS_POWERED                                           1
#define UX_DEVICE_SELF_POWERED                                          2
#define UX_MAX_SELF_POWER                                               (500/2)
#define UX_MAX_BUS_POWER                                                (100/2)
#define UX_CONFIGURATION_DEVICE_BUS_POWERED                             0x80
#define UX_CONFIGURATION_DEVICE_SELF_POWERED                            0x40
#define UX_STATUS_DEVICE_SELF_POWERED                                   1

/* Define USBX OTG constants.  */

#define UX_OTG_BM_ATTRIBUTES                                            2
#define UX_OTG_SRP_SUPPORT                                              1
#define UX_OTG_HNP_SUPPORT                                              2
#define UX_HCD_OTG_CAPABLE                                              1
#define UX_DCD_OTG_CAPABLE                                              1
           
#define UX_OTG_FEATURE_B_HNP_ENABLE                                     3           
#define UX_OTG_FEATURE_A_HNP_SUPPORT                                    4           
#define UX_OTG_FEATURE_A_ALT_HNP_SUPPORT                                5           
#define UX_OTG_STATUS_SELECTOR                                          0xF000
#define UX_OTG_HOST_REQUEST_FLAG                                        0x01
        
#define UX_OTG_IDLE                                                     0
#define UX_OTG_IDLE_TO_HOST                                             1        
#define UX_OTG_IDLE_TO_SLAVE                                            2        
#define UX_OTG_HOST_TO_IDLE                                             3        
#define UX_OTG_HOST_TO_SLAVE                                            4        
#define UX_OTG_SLAVE_TO_IDLE                                            5        
#define UX_OTG_SLAVE_TO_HOST                                            6        
#define UX_OTG_SLAVE_SRP                                                7        
        
#define UX_OTG_MODE_IDLE                                                0        
#define UX_OTG_MODE_SLAVE                                               1        
#define UX_OTG_MODE_HOST                                                2        

#define UX_OTG_DEVICE_IDLE                                              0        
#define UX_OTG_DEVICE_A                                                 1        
#define UX_OTG_DEVICE_B                                                 2        

#define UX_OTG_VBUS_IDLE                                                0        
#define UX_OTG_VBUS_ON                                                  1        
#define UX_OTG_VBUS_OFF                                                 2        

                                                                        
#define UX_OTG_HNP_THREAD_SLEEP_TIME                                    (2 * UX_PERIODIC_RATE)

/* Define USBX device speed constants.  */                              
                                                                        
#define UX_DEFAULT_HS_MPS                                               64
#define UX_DEFAULT_MPS                                                  8
                                                                        
#define UX_LOW_SPEED_DEVICE                                             0
#define UX_FULL_SPEED_DEVICE                                            1
#define UX_HIGH_SPEED_DEVICE                                            2 
                                                                        
                                                                        
/* Define USBX generic port status constants.  */                       
                                                                        
#define UX_PS_CCS                                                       0x01
#define UX_PS_CPE                                                       0x01
#define UX_PS_PES                                                       0x02
#define UX_PS_PSS                                                       0x04
#define UX_PS_POCI                                                      0x08
#define UX_PS_PRS                                                       0x10
#define UX_PS_PPS                                                       0x20
#define UX_PS_DS_LS                                                     0x00
#define UX_PS_DS_FS                                                     0x40
#define UX_PS_DS_HS                                                     0x80
                                                                        
#define UX_PS_DS                                                        6


/* Define USBX Error Code constants. The following format describes 
   their meaning:
                                                                           
        0x1x    : Configuration errors                                        
        0x2x    : USB transport errors                                      
        0x3x    : USB controller errors                                      
        0x4x    : USB topology errors                                        
        0x5x    : USB API errors                                              
        0x6x    : USB Generic Class errors                                           
        0x7x    : USB HID Class errors                                           
        0x8x    : USB Audio Class errors                                           
        0x9x    : USB CDC-ECM Class errors                                           
*/ 

#define UX_SUCCESS                                                      0
#define UX_ERROR                                                        0xff
#define UX_TOO_MANY_DEVICES                                             0x11
#define UX_MEMORY_INSUFFICIENT                                          0x12
#define UX_NO_TD_AVAILABLE                                              0x13
#define UX_NO_ED_AVAILABLE                                              0x14
#define UX_SEMAPHORE_ERROR                                              0x15
#define UX_THREAD_ERROR                                                 0x16
#define UX_MUTEX_ERROR                                                  0x17
#define UX_EVENT_ERROR                                                  0x18
#define UX_MEMORY_CORRUPTED                                             0x19
#define UX_MEMORY_ARRAY_FULL                                            0x1a
#define UX_FATAL_ERROR                                                  0x1b
                                                                        
#define UX_TRANSFER_STALLED                                             0x21
#define UX_TRANSFER_NO_ANSWER                                           0x22
#define UX_TRANSFER_ERROR                                               0x23
#define UX_TRANSFER_MISSED_FRAME                                        0x24
#define UX_TRANSFER_NOT_READY                                           0x25
#define UX_TRANSFER_BUS_RESET                                           0x26
#define UX_TRANSFER_BUFFER_OVERFLOW                                     0x27
#define UX_TRANSFER_APPLICATION_RESET                                   0x28
#define UX_TRANSFER_DATA_LESS_THAN_EXPECTED                             0x29
                                                                        
#define UX_PORT_RESET_FAILED                                            0x31
#define UX_CONTROLLER_INIT_FAILED                                       0x32
#define UX_CONTROLLER_DEAD                                              0x33
                                                                        
#define UX_NO_BANDWIDTH_AVAILABLE                                       0x41
#define UX_DESCRIPTOR_CORRUPTED                                         0x42
#define UX_OVER_CURRENT_CONDITION                                       0x43
#define UX_DEVICE_ENUMERATION_FAILURE                                   0x44
                                                                        
#define UX_DEVICE_HANDLE_UNKNOWN                                        0x50
#define UX_CONFIGURATION_HANDLE_UNKNOWN                                 0x51
#define UX_INTERFACE_HANDLE_UNKNOWN                                     0x52
#define UX_ENDPOINT_HANDLE_UNKNOWN                                      0x53
#define UX_FUNCTION_NOT_SUPPORTED                                       0x54
#define UX_CONTROLLER_UNKNOWN                                           0x55
#define UX_PORT_INDEX_UNKNOWN                                           0x56
#define UX_NO_CLASS_MATCH                                               0x57
#define UX_HOST_CLASS_ALREADY_INSTALLED                                 0x58
#define UX_HOST_CLASS_UNKNOWN                                           0x59
#define UX_CONNECTION_INCOMPATIBLE                                      0x5a
#define UX_HOST_CLASS_INSTANCE_UNKNOWN                                  0x5b
#define UX_TRANSFER_TIMEOUT                                             0x5c
#define UX_BUFFER_OVERFLOW                                              0x5d
#define UX_NO_ALTERNATE_SETTING                                         0x5e
#define UX_NO_DEVICE_CONNECTED                                          0x5f
                                                                        
#define UX_HOST_CLASS_PROTOCOL_ERROR                                    0x60
#define UX_HOST_CLASS_MEMORY_ERROR                                      0x61
#define UX_HOST_CLASS_MEDIA_NOT_SUPPORTED                               0x62
#define UX_CLASS_MALFORMED_PACKET_RECEIVED_ERROR                        0x63

#define UX_HOST_CLASS_HID_REPORT_OVERFLOW                               0x70
#define UX_HOST_CLASS_HID_USAGE_OVERFLOW                                0x71
#define UX_HOST_CLASS_HID_TAG_UNSUPPORTED                               0x72
#define UX_HOST_CLASS_HID_PUSH_OVERFLOW                                 0x73
#define UX_HOST_CLASS_HID_POP_UNDERFLOW                                 0x74
#define UX_HOST_CLASS_HID_COLLECTION_OVERFLOW                           0x75
#define UX_HOST_CLASS_HID_COLLECTION_UNDERFLOW                          0x76
#define UX_HOST_CLASS_HID_MIN_MAX_ERROR                                 0x77
#define UX_HOST_CLASS_HID_DELIMITER_ERROR                               0x78
#define UX_HOST_CLASS_HID_REPORT_ERROR                                  0x79
#define UX_HOST_CLASS_HID_PERIODIC_REPORT_ERROR                         0x7A
#define UX_HOST_CLASS_HID_UNKNOWN                                       0x7B
                                                                        
#define UX_HOST_CLASS_AUDIO_WRONG_TYPE                                  0x80
#define UX_HOST_CLASS_AUDIO_WRONG_INTERFACE                             0x81

#define UX_CLASS_CDC_ECM_LINK_STATE_DOWN_ERROR                          0x90
                                                                        
                                                                        
/* Define USBX HCD API function constants.  */                          
                                                                        
#define UX_HCD_DISABLE_CONTROLLER                                       1
#define UX_HCD_GET_PORT_STATUS                                          2
#define UX_HCD_ENABLE_PORT                                              3
#define UX_HCD_DISABLE_PORT                                             4
#define UX_HCD_POWER_ON_PORT                                            5
#define UX_HCD_POWER_DOWN_PORT                                          6
#define UX_HCD_SUSPEND_PORT                                             7
#define UX_HCD_RESUME_PORT                                              8
#define UX_HCD_RESET_PORT                                               9
#define UX_HCD_GET_FRAME_NUMBER                                         10
#define UX_HCD_SET_FRAME_NUMBER                                         11
#define UX_HCD_TRANSFER_REQUEST                                         12
#define UX_HCD_TRANSFER_ABORT                                           13
#define UX_HCD_CREATE_ENDPOINT                                          14
#define UX_HCD_DESTROY_ENDPOINT                                         15
#define UX_HCD_RESET_ENDPOINT                                           16
#define UX_HCD_PROCESS_DONE_QUEUE                                       17
                                                                        
/* Define USBX DCD API function constants.  */                          
                                                                        
#define UX_DCD_DISABLE_CONTROLLER                                       1
#define UX_DCD_GET_PORT_STATUS                                          2
#define UX_DCD_ENABLE_PORT                                              3
#define UX_DCD_DISABLE_PORT                                             4
#define UX_DCD_POWER_ON_PORT                                            5
#define UX_DCD_POWER_DOWN_PORT                                          6
#define UX_DCD_SUSPEND_PORT                                             7
#define UX_DCD_RESUME_PORT                                              8
#define UX_DCD_RESET_PORT                                               9
#define UX_DCD_GET_FRAME_NUMBER                                         10
#define UX_DCD_SET_FRAME_NUMBER                                         11
#define UX_DCD_TRANSFER_REQUEST                                         12
#define UX_DCD_TRANSFER_ABORT                                           13
#define UX_DCD_CREATE_ENDPOINT                                          14
#define UX_DCD_DESTROY_ENDPOINT                                         15
#define UX_DCD_RESET_ENDPOINT                                           16
#define UX_DCD_SET_DEVICE_ADDRESS                                       17
#define UX_DCD_ISR_PENDING                                              18
#define UX_DCD_CHANGE_STATE                                             19
#define UX_DCD_STALL_ENDPOINT                                           20
#define UX_DCD_ENDPOINT_STATUS                                          21
                                                                        
                                                                        
/* Define USBX generic host controller constants.  */                   
                                                                        
#define UX_HCD_STATUS_HALTED                                            0
#define UX_HCD_STATUS_OPERATIONAL                                       1
#define UX_HCD_STATUS_DEAD                                              2
                                                                        
/* Define USBX generic SLAVE controller constants.  */                  
                                                                        
#define UX_DCD_STATUS_HALTED                                            0
#define UX_DCD_STATUS_OPERATIONAL                                       1
#define UX_DCD_STATUS_DEAD                                              2
                                                                        
/* Define USBX  SLAVE controller VBUS constants.  */                    
                                                                        
#define UX_DCD_VBUS_RESET                                               0
#define UX_DCD_VBUS_SET                                                 1
                                                                        
/* Define USBX class interface constants.  */                           
                                                                        
#define UX_HOST_CLASS_COMMAND_QUERY                                     1
#define UX_HOST_CLASS_COMMAND_ACTIVATE                                  2
#define UX_HOST_CLASS_COMMAND_DEACTIVATE                                3
                                                                        
#define UX_SLAVE_CLASS_COMMAND_QUERY                                    1
#define UX_SLAVE_CLASS_COMMAND_ACTIVATE                                 2
#define UX_SLAVE_CLASS_COMMAND_DEACTIVATE                               3
#define UX_SLAVE_CLASS_COMMAND_REQUEST                                  4
#define UX_SLAVE_CLASS_COMMAND_INITIALIZE                               5
#define UX_SLAVE_CLASS_COMMAND_CHANGE                                   6
#define UX_SLAVE_CLASS_COMMAND_UNINITIALIZE                             7
                                                                        
#define UX_HOST_CLASS_COMMAND_USAGE_PIDVID                              1
#define UX_HOST_CLASS_COMMAND_USAGE_CSP                                 2
                                                                        
#define UX_HOST_CLASS_INSTANCE_FREE                                     0
#define UX_HOST_CLASS_INSTANCE_LIVE                                     1
#define UX_HOST_CLASS_INSTANCE_SHUTDOWN                                 2
#define UX_HOST_CLASS_INSTANCE_MOUNTING                                 3


/* Define USBX root HUB constants.  */                                  
                                                                        
#define UX_RH_ENUMERATION_RETRY                                         3
#define UX_RH_ENUMERATION_RETRY_DELAY                                   100

                                                                        
/* Define USBX PCI driver constants.  */                                
                                                                        
#define UX_PCI_NB_FUNCTIONS                                             7
#define UX_PCI_NB_DEVICE                                                32
#define UX_PCI_NB_BUS                                                   0xff
                                                                        
#define UX_PCI_CMD_IO_ENABLE                                            0x0001
#define UX_PCI_CMD_MEM_ENABLE                                           0x0002
#define UX_PCI_CMD_MASTER_ENABLE                                        0x0004
#define UX_PCI_CMD_MONITOR_ENABLE                                       0x0008
#define UX_PCI_CMD_MEM_WRITE_INV_ENABLE                                 0x0010
#define UX_PCI_CMD_SNOOP_PALETTE_ENABLE                                 0x0020
#define UX_PCI_CMD_PARITY_ERROR_ENABLE                                  0x0040
#define UX_PCI_CMD_WAIT_CYCLE_CTRL_ENABLE                               0x0080
#define UX_PCI_CMD_SERR_ENABLE                                          0x0100
#define UX_PCI_CMD_FBB_ENABLE                                           0x0200
                                                                        
#define UX_PCI_CFG_CTRL_ADDRESS                                         0x0cf8
#define UX_PCI_CFG_DATA_ADDRESS                                         0x0cfc
                                                                        
#define UX_PCI_CFG_VENDOR_ID                                            0x00
#define UX_PCI_CFG_DEVICE_ID                                            0x02
#define UX_PCI_CFG_COMMAND                                              0x04
#define UX_PCI_CFG_STATUS                                               0x06
#define UX_PCI_CFG_REVISION                                             0x08
#define UX_PCI_CFG_PROGRAMMING_IF                                       0x09
#define UX_PCI_CFG_SUBCLASS                                             0x0a
#define UX_PCI_CFG_CLASS                                                0x0b
#define UX_PCI_CFG_CACHE_LINE_SIZE                                      0x0c
#define UX_PCI_CFG_LATENCY_TIMER                                        0x0d
#define UX_PCI_CFG_HEADER_TYPE                                          0x0e
#define UX_PCI_CFG_BIST                                                 0x0f
#define UX_PCI_CFG_BASE_ADDRESS_0                                       0x10
#define UX_PCI_CFG_BASE_ADDRESS_1                                       0x14
#define UX_PCI_CFG_BASE_ADDRESS_2                                       0x18
#define UX_PCI_CFG_BASE_ADDRESS_3                                       0x1c
#define UX_PCI_CFG_BASE_ADDRESS_4                                       0x20
#define UX_PCI_CFG_BASE_ADDRESS_5                                       0x24
#define UX_PCI_CFG_CARDBUS_CIS                                          0x28
#define UX_PCI_CFG_SUB_VENDOR_ID                                        0x2c
#define UX_PCI_CFG_SUB_SYSTEM_ID                                        0x2e
#define UX_PCI_CFG_EXPANSION_ROM_ADDRESS                                0x30
#define UX_PCI_CFG_RESERVED_0                                           0x34
#define UX_PCI_CFG_RESERVED_1                                           0x38
#define UX_PCI_CFG_INT_LINE                                             0x3c
#define UX_PCI_CFG_INT_PIN                                              0x3d
#define UX_PCI_CFG_MIN_GNT                                              0x3e
#define UX_PCI_CFG_MAX_LATENCY                                          0x3f
                                                                        
#define UX_PCI_CFG_SBRN                                                 0x60
#define UX_PCI_CFG_FLADJ                                                0x61
                                                                        
/* Define DFU constants.  */
#define UX_SYSTEM_DFU_STATE_APP_IDLE                                    0
#define UX_SYSTEM_DFU_STATE_APP_DETACH                                  1
#define UX_SYSTEM_DFU_STATE_DFU_IDLE                                    2
#define UX_SYSTEM_DFU_STATE_DFU_DNLOAD_SYNC                             3
#define UX_SYSTEM_DFU_STATE_DFU_DNBUSY                                  4
#define UX_SYSTEM_DFU_STATE_DFU_DNLOAD_IDLE                             5
#define UX_SYSTEM_DFU_STATE_DFU_MANIFEST_SYNC                           6 
#define UX_SYSTEM_DFU_STATE_DFU_MANIFEST                                7
#define UX_SYSTEM_DFU_STATE_DFU_MANIFEST_WAIT_RESET                     8 
#define UX_SYSTEM_DFU_STATE_DFU_UPLOAD_IDLE                             9
#define UX_SYSTEM_DFU_STATE_DFU_ERROR                                   10

/* Define basic class constants.  */                                    
                                                                        
#define UX_HOST_CLASS_PRINTER_NAME_LENGTH                               64


/* Define USBX 2.0 TT Instance structure.  */

typedef struct UX_HUB_TT_STRUCT
{

    ULONG           ux_hub_tt_port_mapping;
    ULONG           ux_hub_tt_max_bandwidth;
} UX_HUB_TT;


/* Define USBX Class calling command structure.  */

typedef struct UX_HOST_CLASS_COMMAND_STRUCT
{

    UINT            ux_host_class_command_request;
    VOID            *ux_host_class_command_container;
    VOID            *ux_host_class_command_instance;
    UINT            ux_host_class_command_usage;
    UINT            ux_host_class_command_pid;
    UINT            ux_host_class_command_vid;
    UINT            ux_host_class_command_class;
    UINT            ux_host_class_command_subclass;
    UINT            ux_host_class_command_protocol;
    UINT            ux_host_class_command_iad_class;
    UINT            ux_host_class_command_iad_subclass;
    UINT            ux_host_class_command_iad_protocol;
    
    struct UX_HOST_CLASS_STRUCT     
                    *ux_host_class_command_class_ptr;
} UX_HOST_CLASS_COMMAND;


/* Define USBX Class container structure.  */

typedef struct UX_HOST_CLASS_STRUCT
{

    UCHAR           ux_host_class_name[UX_MAX_CLASS_NAME_LENGTH + 1]; /* "+1" for string null-terminator */
    UINT            ux_host_class_status;
    UINT            (*ux_host_class_entry_function) (struct UX_HOST_CLASS_COMMAND_STRUCT *) ;
    UINT            ux_host_class_nb_devices_owned;
    VOID            *ux_host_class_first_instance;
    VOID            *ux_host_class_client;
    TX_THREAD       ux_host_class_thread;
    VOID            *ux_host_class_thread_stack;
    VOID            *ux_host_class_media;
} UX_HOST_CLASS;


/* Define USBX transfer request structure.  */

typedef struct UX_TRANSFER_STRUCT
{

    ULONG           ux_transfer_request_status;
    struct UX_ENDPOINT_STRUCT               
                    *ux_transfer_request_endpoint;
    UCHAR *         ux_transfer_request_data_pointer;
    ULONG           ux_transfer_request_requested_length;
    ULONG           ux_transfer_request_actual_length;
    UINT            ux_transfer_request_type;
    UINT            ux_transfer_request_function;
    UINT            ux_transfer_request_value;
    UINT            ux_transfer_request_index;
    VOID            (*ux_transfer_request_completion_function) (struct UX_TRANSFER_STRUCT *);
    TX_SEMAPHORE    ux_transfer_request_semaphore;
    VOID            *ux_transfer_request_class_instance;
    ULONG           ux_transfer_request_maximum_length;
    ULONG           ux_transfer_request_timeout_value;
    UINT            ux_transfer_request_completion_code;
    ULONG           ux_transfer_request_packet_length;
    struct UX_TRANSFER_STRUCT               
                    *ux_transfer_request_next_transfer_request;
    VOID            *ux_transfer_request_user_specific;
    TX_THREAD       *ux_transfer_request_thread_pending;
} UX_TRANSFER;


/* Define USBX Endpoint Descriptor structure.  */

typedef struct UX_ENDPOINT_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bEndpointAddress;
    ULONG           bmAttributes;
    ULONG           wMaxPacketSize;
    ULONG           bInterval;
} UX_ENDPOINT_DESCRIPTOR;

#define UX_ENDPOINT_DESCRIPTOR_ENTRIES                                  6
#define UX_ENDPOINT_DESCRIPTOR_LENGTH                                   7


/* Define USBX Endpoint Container structure.  */

typedef struct UX_ENDPOINT_STRUCT
{

    ULONG           ux_endpoint;
    ULONG           ux_endpoint_state;
    void            *ux_endpoint_ed;    
    struct UX_ENDPOINT_DESCRIPTOR_STRUCT     
                    ux_endpoint_descriptor;
    struct UX_ENDPOINT_STRUCT                
                    *ux_endpoint_next_endpoint;
    struct UX_INTERFACE_STRUCT               
                    *ux_endpoint_interface;
    struct UX_DEVICE_STRUCT                  
                    *ux_endpoint_device;
    struct UX_TRANSFER_STRUCT                
                    ux_endpoint_transfer_request;
} UX_ENDPOINT;


/* Define USBX Device Descriptor structure.  */

typedef struct UX_DEVICE_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bcdUSB;
    ULONG           bDeviceClass;
    ULONG           bDeviceSubClass;
    ULONG           bDeviceProtocol;
    ULONG           bMaxPacketSize0;
    ULONG           idVendor;
    ULONG           idProduct;
    ULONG           bcdDevice;
    ULONG           iManufacturer;
    ULONG           iProduct;
    ULONG           iSerialNumber;
    ULONG           bNumConfigurations;
} UX_DEVICE_DESCRIPTOR;

#define UX_DEVICE_DESCRIPTOR_ENTRIES                                    14
#define UX_DEVICE_DESCRIPTOR_LENGTH                                     18

/* Define USBX Device Qualifier Descriptor structure.  */

typedef struct UX_DEVICE_QUALIFIER_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bcdUSB;
    ULONG           bDeviceClass;
    ULONG           bDeviceSubClass;
    ULONG           bDeviceProtocol;
    ULONG           bMaxPacketSize0;
    ULONG           bNumConfigurations;
    ULONG           bReserved;
} UX_DEVICE_QUALIFIER_DESCRIPTOR;

#define UX_DEVICE_QUALIFIER_DESCRIPTOR_ENTRIES                          9
#define UX_DEVICE_QUALIFIER_DESCRIPTOR_LENGTH                           10


/* Define USBX Other Speed Descriptor structure.  */

typedef struct UX_OTHER_SPEED_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           wTotalLength;
    ULONG           bNumInterfaces;
    ULONG           bConfigurationValue;
    ULONG           iConfiguration;
    ULONG           bmAttributes;
    ULONG           MaxPower;
} UX_OTHER_SPEED_DESCRIPTOR;

#define UX_OTHER_SPEED_DESCRIPTOR_ENTRIES                               8
#define UX_OTHER_SPEED_DESCRIPTOR_LENGTH                                9

/* Define USBX OTG Descriptor structure.  */

typedef struct UX_OTG_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bmAttributes;
    ULONG           bcdOTG;
} UX_OTG_DESCRIPTOR;

#define UX_OTG_DESCRIPTOR_ENTRIES                          4
#define UX_OTG_DESCRIPTOR_LENGTH                           5

/* Define USBX Interface Association Descriptor structure.  */

typedef struct UX_INTERFACE_ASSOCIATION_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bFirstInterface;
    ULONG           bInterfaceCount;
    ULONG           bFunctionClass;
    ULONG           bFunctionSubClass;
    ULONG           bFunctionProtocol;
    ULONG           iFunction;

} UX_INTERFACE_ASSOCIATION_DESCRIPTOR;
                                                            
#define UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ENTRIES         8
#define UX_INTERFACE_ASSOCIATION_DESCRIPTOR_LENGTH          8


/* Define USBX Device Container structure.  */

typedef struct UX_DEVICE_STRUCT
{

    ULONG           ux_device_handle;
    ULONG           ux_device_type;
    ULONG           ux_device_state;
    ULONG           ux_device_address;
    ULONG           ux_device_speed;
    ULONG           ux_device_port_location;
    ULONG           ux_device_max_power;
    ULONG           ux_device_power_source;
    UINT            ux_device_current_configuration;
    TX_SEMAPHORE    ux_device_protection_semaphore;
    struct UX_DEVICE_STRUCT
                    *ux_device_parent;
    struct UX_HOST_CLASS_STRUCT                       
                    *ux_device_class;
    VOID            *ux_device_class_instance;
    struct UX_HCD_STRUCT                         
                    *ux_device_hcd;
    struct UX_CONFIGURATION_STRUCT               
                    *ux_device_first_configuration;
    struct UX_DEVICE_STRUCT                      
                    *ux_device_next_device;
    struct UX_DEVICE_DESCRIPTOR_STRUCT           
                    ux_device_descriptor;
    struct UX_ENDPOINT_STRUCT                    
                    ux_device_control_endpoint;
    struct UX_HUB_TT_STRUCT                      
                    ux_device_hub_tt[UX_MAX_TT];
} UX_DEVICE;


/* Define USBX Configuration Descriptor structure.  */

typedef struct UX_CONFIGURATION_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           wTotalLength;
    ULONG           bNumInterfaces;
    ULONG           bConfigurationValue;
    ULONG           iConfiguration;
    ULONG           bmAttributes;
    ULONG           MaxPower;
} UX_CONFIGURATION_DESCRIPTOR;

#define UX_CONFIGURATION_DESCRIPTOR_ENTRIES                             8
#define UX_CONFIGURATION_DESCRIPTOR_LENGTH                              9


/* Define USBX Configuration Container structure.  */

typedef struct UX_CONFIGURATION_STRUCT
{

    ULONG           ux_configuration_handle;
    ULONG           ux_configuration_state;
    ULONG           ux_configuration_otg_capabilities;
    struct UX_CONFIGURATION_DESCRIPTOR_STRUCT    
                    ux_configuration_descriptor;
    struct UX_INTERFACE_STRUCT                   
                    *ux_configuration_first_interface;
    struct UX_CONFIGURATION_STRUCT               
                    *ux_configuration_next_configuration;
    struct UX_DEVICE_STRUCT                      
                    *ux_configuration_device;
    ULONG           ux_configuration_iad_class;
    ULONG           ux_configuration_iad_subclass;
    ULONG           ux_configuration_iad_protocol;
} UX_CONFIGURATION;


/* Define USBX Interface Descriptor structure.  */

typedef struct UX_INTERFACE_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bInterfaceNumber;
    ULONG           bAlternateSetting;
    ULONG           bNumEndpoints;
    ULONG           bInterfaceClass;
    ULONG           bInterfaceSubClass;
    ULONG           bInterfaceProtocol;
    ULONG           iInterface;
} UX_INTERFACE_DESCRIPTOR;
    
#define UX_INTERFACE_DESCRIPTOR_ENTRIES                                 9
#define UX_INTERFACE_DESCRIPTOR_LENGTH                                  9


/* Define USBX Interface Container structure.  */

typedef struct UX_INTERFACE_STRUCT
{

    ULONG           ux_interface_handle;
    ULONG           ux_interface_state;
    UINT            ux_interface_current_alternate_setting;
    struct UX_INTERFACE_DESCRIPTOR_STRUCT        
                    ux_interface_descriptor;
    struct UX_HOST_CLASS_STRUCT                       
                    *ux_interface_class;
    VOID            *ux_interface_class_instance;
    struct UX_ENDPOINT_STRUCT                    
                    *ux_interface_first_endpoint;
    struct UX_INTERFACE_STRUCT                   
                    *ux_interface_next_interface;
    struct UX_CONFIGURATION_STRUCT               
                    *ux_interface_configuration;
    ULONG           ux_interface_iad_class;
    ULONG           ux_interface_iad_subclass;
    ULONG           ux_interface_iad_protocol;

} UX_INTERFACE;


/* Define USBX String Descriptor structure.  */

typedef struct UX_STRING_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bString[1];
} UX_STRING_DESCRIPTOR;

#define UX_STRING_DESCRIPTOR_ENTRIES                                    3
#define UX_STRING_DESCRIPTOR_LENGTH                                     4


/* Define USBX DFU functional descriptor.  */

typedef struct UX_DFU_FUNCTIONAL_DESCRIPTOR_STRUCT
{

    ULONG           bLength;
    ULONG           bDescriptorType;
    ULONG           bmAttributes;
    ULONG           wDetachTimeOut;
    ULONG           wTransferSize;
    ULONG           bcdDFUVersion;
} UX_DFU_FUNCTIONAL_DESCRIPTOR;
                                                                        
#define UX_DFU_FUNCTIONAL_DESCRIPTOR_ENTRIES                            6
#define UX_DFU_FUNCTIONAL_DESCRIPTOR_LENGTH                             9

/* Define USBX Host Controller structure.  */

typedef struct UX_HCD_STRUCT
{                        

    UCHAR           ux_hcd_name[UX_MAX_HCD_NAME_LENGTH + 1]; /* "+1" for string null-terminator */
    UCHAR           ux_hcd_address[16];
    UINT            ux_hcd_status;
    UINT            ux_hcd_controller_type;
    UINT            ux_hcd_otg_capabilities;
    UINT            ux_hcd_irq;
    UINT            ux_hcd_nb_root_hubs;
    UINT            ux_hcd_root_hub_signal[16];
    UINT            ux_hcd_nb_devices;
    UINT            ux_hcd_power_switch;
    UINT            ux_hcd_thread_signal;
    ULONG           ux_hcd_rh_device_connection;
    ULONG           ux_hcd_io;
    ULONG           ux_hcd_available_bandwidth;
    ULONG           ux_hcd_maximum_transfer_request_size;
    ULONG           ux_hcd_version;
    UINT            (*ux_hcd_entry_function) (struct UX_HCD_STRUCT *, UINT, VOID *);
    void            *ux_hcd_controller_hardware;
} UX_HCD;


/* Define USBX Device Transfer Request structure.  */

typedef struct UX_SLAVE_TRANSFER_STRUCT
{

    ULONG           ux_slave_transfer_request_status;
    ULONG           ux_slave_transfer_request_type;
    struct UX_SLAVE_ENDPOINT_STRUCT           
                    *ux_slave_transfer_request_endpoint;
    UCHAR           *ux_slave_transfer_request_data_pointer;
    UCHAR           *ux_slave_transfer_request_current_data_pointer;
    ULONG           ux_slave_transfer_request_requested_length;
    ULONG           ux_slave_transfer_request_actual_length;
    ULONG           ux_slave_transfer_request_in_transfer_length;
    ULONG           ux_slave_transfer_request_completion_code;
    ULONG           ux_slave_transfer_request_phase;
    VOID            (*ux_slave_transfer_request_completion_function) (struct UX_SLAVE_TRANSFER_STRUCT *);
    TX_SEMAPHORE    ux_slave_transfer_request_semaphore;
    ULONG           ux_slave_transfer_request_timeout;
    ULONG           ux_slave_transfer_request_force_zlp;
    UCHAR           ux_slave_transfer_request_setup[UX_SETUP_SIZE];
    ULONG           ux_slave_transfer_request_status_phase_ignore;
} UX_SLAVE_TRANSFER;


/* Define USBX Device Controller Endpoint structure.  */

typedef struct UX_SLAVE_ENDPOINT_STRUCT
{                        

    ULONG           ux_slave_endpoint_status;
    ULONG           ux_slave_endpoint_state;
    void            *ux_slave_endpoint_ed;  
    struct UX_ENDPOINT_DESCRIPTOR_STRUCT      
                    ux_slave_endpoint_descriptor;
    struct UX_SLAVE_ENDPOINT_STRUCT             
                    *ux_slave_endpoint_next_endpoint;
    struct UX_SLAVE_INTERFACE_STRUCT            
                    *ux_slave_endpoint_interface;
    struct UX_SLAVE_DEVICE_STRUCT               
                    *ux_slave_endpoint_device;
    struct UX_SLAVE_TRANSFER_STRUCT             
                    ux_slave_endpoint_transfer_request;
} UX_SLAVE_ENDPOINT;


/* Define USBX Device Controller Interface structure.  */

typedef struct UX_SLAVE_INTERFACE_STRUCT
{                        
    ULONG           ux_slave_interface_status;
    struct UX_SLAVE_CLASS_STRUCT                       
                    *ux_slave_interface_class;
    VOID            *ux_slave_interface_class_instance;

    struct UX_INTERFACE_DESCRIPTOR_STRUCT        
                    ux_slave_interface_descriptor;
    struct UX_SLAVE_INTERFACE_STRUCT              
                    *ux_slave_interface_next_interface;
    struct UX_SLAVE_ENDPOINT_STRUCT               
                    *ux_slave_interface_first_endpoint;
} UX_SLAVE_INTERFACE;


/* Define USBX Device Controller structure.  */

typedef struct UX_SLAVE_DEVICE_STRUCT
{                        

    ULONG           ux_slave_device_state;   
    struct UX_DEVICE_DESCRIPTOR_STRUCT           
                    ux_slave_device_descriptor;
    struct UX_SLAVE_ENDPOINT_STRUCT               
                    ux_slave_device_control_endpoint;
    ULONG           ux_slave_device_configuration_selected;
    struct UX_CONFIGURATION_DESCRIPTOR_STRUCT    
                    ux_slave_device_configuration_descriptor;
    struct UX_SLAVE_INTERFACE_STRUCT               
                    *ux_slave_device_first_interface;
    struct UX_SLAVE_INTERFACE_STRUCT               
                    *ux_slave_device_interfaces_pool;
    ULONG           ux_slave_device_interfaces_pool_number;
    struct UX_SLAVE_ENDPOINT_STRUCT               
                    *ux_slave_device_endpoints_pool;
    ULONG           ux_slave_device_endpoints_pool_number;
    ULONG           ux_slave_device_power_state;                    
    
} UX_SLAVE_DEVICE;


/* Define USBX Device Controller structure.  */

typedef struct UX_SLAVE_DCD_STRUCT
{                        

    UCHAR           ux_slave_dcd_name[32];
    UINT            ux_slave_dcd_status;
    UINT            ux_slave_dcd_controller_type;
    UINT            ux_slave_dcd_otg_capabilities;
    UINT            ux_slave_dcd_irq;
    ULONG           ux_slave_dcd_io;
    ULONG           ux_slave_dcd_device_address;
    UINT            (*ux_slave_dcd_function) (struct UX_SLAVE_DCD_STRUCT *,UINT, VOID *);
    void            *ux_slave_dcd_controller_hardware;
} UX_SLAVE_DCD;

/* Define USBX Device Class Command container structure.  */

typedef struct UX_SLAVE_CLASS_COMMAND_STRUCT
{

    UINT            ux_slave_class_command_request;
    VOID            *ux_slave_class_command_container;
    VOID            *ux_slave_class_command_interface;
    UINT            ux_slave_class_command_pid;
    UINT            ux_slave_class_command_vid;
    UINT            ux_slave_class_command_class;
    UINT            ux_slave_class_command_subclass;
    UINT            ux_slave_class_command_protocol;
    struct UX_SLAVE_CLASS_STRUCT     
                    *ux_slave_class_command_class_ptr;
    VOID            *ux_slave_class_command_parameter;
    VOID            *ux_slave_class_command_interface_number;
    
} UX_SLAVE_CLASS_COMMAND;


/* Define USBX Device Class container structure.  */

typedef struct UX_SLAVE_CLASS_STRUCT
{

    UCHAR           ux_slave_class_name[UX_MAX_CLASS_NAME_LENGTH + 1]; /* "+1" for string null-terminator */
    UINT            ux_slave_class_status;
    UINT            (*ux_slave_class_entry_function) (struct UX_SLAVE_CLASS_COMMAND_STRUCT *) ;
    VOID            *ux_slave_class_instance;
    VOID            *ux_slave_class_client;
    TX_THREAD       ux_slave_class_thread;
    VOID            *ux_slave_class_thread_stack;
    VOID            *ux_slave_class_interface_parameter;                    
    ULONG           ux_slave_class_interface_number;                    
    ULONG           ux_slave_class_configuration_number;                    
    struct UX_SLAVE_INTERFACE_STRUCT               
                    *ux_slave_class_interface;

} UX_SLAVE_CLASS;

/* Define USBX Memory Management structure.  */

typedef struct UX_MEMORY_BLOCK_STRUCT 
{

    ULONG           ux_memory_block_size;
    ULONG           ux_memory_block_status;
    struct  UX_MEMORY_BLOCK_STRUCT   
                    *ux_memory_block_next;
    struct  UX_MEMORY_BLOCK_STRUCT   
                    *ux_memory_block_previous;
} UX_MEMORY_BLOCK;


typedef struct UX_SYSTEM_STRUCT
{                                        

    UX_MEMORY_BLOCK *ux_system_regular_memory_pool_start;
    ULONG           ux_system_regular_memory_pool_size;
    ULONG           ux_system_regular_memory_pool_free;
    UX_MEMORY_BLOCK *ux_system_cache_safe_memory_pool_start;
    ULONG           ux_system_cache_safe_memory_pool_size;
    ULONG           ux_system_cache_safe_memory_pool_free;
    UINT            ux_system_thread_lowest_priority;
    TX_MUTEX        ux_system_mutex;
    ULONG           ux_system_debug_code;
    ULONG           ux_system_debug_count;
    UINT            ux_system_last_error;
    UINT            ux_system_error_count;
    UCHAR           *ux_system_debug_log_buffer;
    UCHAR           *ux_system_debug_log_head;
    UCHAR           *ux_system_debug_log_tail;
    ULONG           ux_system_debug_log_size;
    VOID            (*ux_system_debug_callback_function) (UCHAR *debug_message, ULONG debug_value) ;
    VOID            (*ux_system_error_callback_function) (UINT system_level, UINT system_context, UINT error_code) ;
} UX_SYSTEM;


/* Define USBX System Host Data structure.  */

typedef struct UX_SYSTEM_HOST_STRUCT
{                                        

    UINT            ux_system_host_max_class;
    UINT            ux_system_host_registered_class;
    UX_HOST_CLASS   *ux_system_host_class_array;
    UINT            ux_system_host_max_hcd;
    UX_HCD          *ux_system_host_hcd_array;
    UINT            ux_system_host_registered_hcd;
    UX_DEVICE       *ux_system_host_device_array;
    ULONG           ux_system_host_max_devices;
    ULONG           ux_system_host_max_ed;
    ULONG           ux_system_host_max_td;
    ULONG           ux_system_host_max_iso_td;
    UINT            ux_system_host_rhsc_hcd;
    UCHAR           *ux_system_host_enum_thread_stack;
    TX_THREAD       ux_system_host_enum_thread;
    TX_SEMAPHORE    ux_system_host_enum_semaphore;
    VOID            (*ux_system_host_enum_hub_function) (VOID);
    UCHAR           *ux_system_host_hcd_thread_stack;
    TX_THREAD       ux_system_host_hcd_thread;
    UCHAR           *ux_system_host_hnp_polling_thread_stack;
    TX_THREAD       ux_system_host_hnp_polling_thread;
    TX_SEMAPHORE    ux_system_host_hcd_semaphore;
    UINT            (*ux_system_host_change_function) (ULONG, UX_HOST_CLASS *, VOID *);
} UX_SYSTEM_HOST;


typedef struct UX_SYSTEM_SLAVE_STRUCT
{                                        

    TX_THREAD       ux_system_slave_enum_thread;
    UCHAR           *ux_system_slave_enum_thread_stack;
    TX_SEMAPHORE    ux_system_slave_enum_semaphore;
    UX_SLAVE_DCD    ux_system_slave_dcd;
    UX_SLAVE_DEVICE ux_system_slave_device;
    UCHAR           *ux_system_slave_device_framework;
    ULONG           ux_system_slave_device_framework_length;
    UCHAR           *ux_system_slave_device_framework_full_speed;
    ULONG           ux_system_slave_device_framework_length_full_speed;
    UCHAR           *ux_system_slave_device_framework_high_speed;
    ULONG           ux_system_slave_device_framework_length_high_speed;
    UCHAR           *ux_system_slave_string_framework;
    ULONG           ux_system_slave_string_framework_length;
    UCHAR           *ux_system_slave_language_id_framework;
    ULONG           ux_system_slave_language_id_framework_length;
    UCHAR           *ux_system_slave_dfu_framework;
    ULONG           ux_system_slave_dfu_framework_length;
    UINT            ux_system_slave_max_class;
    UINT            ux_system_slave_registered_class;
    UX_SLAVE_CLASS  *ux_system_slave_class_array;
    UX_SLAVE_CLASS  *ux_system_slave_interface_class_array[UX_MAX_SLAVE_INTERFACES];
    ULONG           ux_system_slave_speed;
    ULONG           ux_system_slave_power_state;
    ULONG           ux_system_slave_remote_wakeup_capability;
    ULONG           ux_system_slave_remote_wakeup_enabled;
    ULONG           ux_system_slave_device_dfu_capabilities;
    ULONG           ux_system_slave_device_dfu_detach_timeout;
    ULONG           ux_system_slave_device_dfu_transfer_size;
    ULONG           ux_system_slave_device_dfu_state_machine;
    ULONG           ux_system_slave_device_dfu_mode;
    UINT            (*ux_system_slave_change_function) (ULONG);
    ULONG           ux_system_slave_device_vendor_request;
    UINT            (*ux_system_slave_device_vendor_request_function) (ULONG, ULONG, ULONG, ULONG, UCHAR *, ULONG *);

} UX_SYSTEM_SLAVE;

typedef struct UX_SYSTEM_OTG_STRUCT
{                                        

    TX_THREAD       ux_system_otg_thread;
    UCHAR           *ux_system_otg_thread_stack;
    TX_SEMAPHORE    ux_system_otg_semaphore;
    UINT            (*ux_system_otg_function) (ULONG);
    ULONG           ux_system_otg_mode;
    ULONG           ux_system_otg_io;
    ULONG           ux_system_otg_vbus_state;
    ULONG           ux_system_otg_change_mode_event;
    ULONG           ux_system_otg_change_vbus_event;
    ULONG           ux_system_otg_slave_role_swap_flag;
    ULONG           ux_system_otg_slave_set_feature_flag;
    ULONG           ux_system_otg_device_type;
    VOID            (*ux_system_otg_vbus_function) (ULONG);
    VOID            (*ux_system_otg_change_mode_callback) (ULONG);
} UX_SYSTEM_OTG;

/* Define Data Pump Class instance structure.  */


typedef struct UX_HOST_CLASS_DPUMP_STRUCT
{

    struct UX_HOST_CLASS_DPUMP_STRUCT  
                    *ux_host_class_dpump_next_instance;
    UX_HOST_CLASS   *ux_host_class_dpump_class;
    UX_DEVICE       *ux_host_class_dpump_device;
    UX_INTERFACE    *ux_host_class_dpump_interface;
    UX_ENDPOINT     *ux_host_class_dpump_bulk_out_endpoint;
    UX_ENDPOINT     *ux_host_class_dpump_bulk_in_endpoint;
    UX_ENDPOINT     *ux_host_class_dpump_interrupt_endpoint;
    UINT            ux_host_class_dpump_state;
    TX_SEMAPHORE    ux_host_class_dpump_semaphore;
} UX_HOST_CLASS_DPUMP;


/* Define the system API mappings based on the error checking 
   selected by the user.  Note: this section is only applicable to 
   application source code, hence the conditional that turns off this
   stuff when the include file is processed by the ThreadX source. */

#ifndef  UX_SOURCE_CODE


/* Define USBX Services.  */

#define ux_system_initialize                                    _ux_system_initialize
#define ux_system_uninitialize                                  _ux_system_uninitialize

#define ux_host_class_hub_entry                                 _ux_host_class_hub_entry

#define ux_host_class_storage_entry                             _ux_host_class_storage_entry

#define ux_host_stack_class_get                                 _ux_host_stack_class_get
#define ux_host_stack_class_instance_create                     _ux_host_stack_class_instance_create
#define ux_host_stack_class_instance_destroy                    _ux_host_stack_class_instance_destroy
#define ux_host_stack_class_instance_get                        _ux_host_stack_class_instance_get
#define ux_host_stack_class_register                            _ux_host_stack_class_register
#define ux_host_stack_configuration_interface_get               _ux_host_stack_configuration_interface_get
#define ux_host_stack_device_configuration_get                  _ux_host_stack_device_configuration_get
#define ux_host_stack_device_configuration_select               _ux_host_stack_device_configuration_select
#define ux_host_stack_device_get                                _ux_host_stack_device_get
#define ux_host_stack_endpoint_transfer_abort                   _ux_host_stack_endpoint_transfer_abort
#define ux_host_stack_hcd_register                              _ux_host_stack_hcd_register
#define ux_host_stack_initialize                                _ux_host_stack_initialize
#define ux_host_stack_interface_endpoint_get                    _ux_host_stack_interface_endpoint_get
#define ux_host_stack_interface_setting_select                  _ux_host_stack_interface_setting_select
#define ux_host_stack_transfer_request                          _ux_host_stack_transfer_request
#define ux_host_stack_transfer_request_abort                    _ux_host_stack_transfer_request_abort
#define ux_host_stack_hnp_polling_thread_entry                  _ux_host_stack_hnp_polling_thread_entry
#define ux_host_stack_role_swap                                 _ux_host_stack_role_swap
#define ux_host_stack_device_configuration_reset                _ux_host_stack_device_configuration_reset

#define ux_utility_pci_class_scan                               _ux_utility_pci_class_scan
#define ux_utility_pci_read                                     _ux_utility_pci_read
#define ux_utility_pci_write                                    _ux_utility_pci_write

#define ux_device_stack_alternate_setting_get                   _ux_device_stack_alternate_setting_get
#define ux_device_stack_alternate_setting_set                   _ux_device_stack_alternate_setting_set
#define ux_device_stack_class_register                          _ux_device_stack_class_register
#define ux_device_stack_class_unregister                        _ux_device_stack_class_unregister
#define ux_device_stack_configuration_get                       _ux_device_stack_configuration_get
#define ux_device_stack_configuration_set                       _ux_device_stack_configuration_set
#define ux_device_stack_descriptor_send                         _ux_device_stack_descriptor_send
#define ux_device_stack_connect                                 _ux_device_stack_connect
#define ux_device_stack_disconnect                              _ux_device_stack_disconnect
#define ux_device_stack_endpoint_stall                          _ux_device_stack_endpoint_stall
#define ux_device_stack_host_wakeup                             _ux_device_stack_host_wakeup
#define ux_device_stack_initialize                              _ux_device_stack_initialize
#define ux_device_stack_uninitialize                            _ux_device_stack_uninitialize
#define ux_device_stack_interface_delete                        _ux_device_stack_interface_delete
#define ux_device_stack_interface_get                           _ux_device_stack_interface_get
#define ux_device_stack_interface_set                           _ux_device_stack_interface_set
#define ux_device_stack_interface_start                         _ux_device_stack_interface_start
#define ux_device_stack_transfer_request                        _ux_device_stack_transfer_request
#define ux_device_stack_transfer_abort                          _ux_device_stack_transfer_abort

#define ux_hcd_ehci_initialize                                  _ux_hcd_ehci_initialize
#define ux_hcd_isp1161_initialize                               _ux_hcd_isp1161_initialize
#define ux_hcd_ohci_initialize                                  _ux_hcd_ohci_initialize
#define ux_hcd_sim_host_initialize                              _ux_hcd_sim_host_initialize
#define ux_dcd_sim_slave_initialize                             _ux_dcd_sim_slave_initialize

#define ux_network_driver_init                                  _ux_network_driver_init 
#endif


/* Define USBX API prototypes.  */

UINT    ux_system_initialize(VOID *non_cached_memory_pool_start, ULONG non_cached_memory_size, 
                                VOID *cached_memory_pool_start, ULONG cached_memory_size);
UINT    ux_system_uninitialize(VOID);

/* Define USBX Host API prototypes.  */

UINT    ux_hcd_ehci_initialize(UX_HCD *hcd);
UINT    ux_hcd_isp1161_initialize(UX_HCD *hcd);
UINT    ux_hcd_ohci_initialize(UX_HCD *hcd);
UINT    ux_hcd_sim_host_initialize(UX_HCD *hcd);

UINT    ux_host_stack_class_get(UCHAR *class_name, UX_HOST_CLASS **host_class);
UINT    ux_host_stack_class_instance_create(UX_HOST_CLASS *host_class, VOID *class_instance);
UINT    ux_host_stack_class_instance_destroy(UX_HOST_CLASS *host_class, VOID *class_instance);
UINT    ux_host_stack_class_instance_get(UX_HOST_CLASS *host_class, UINT class_index, VOID **class_instance);
UINT    ux_host_stack_class_register(UCHAR *class_name, UINT (*class_entry_function)(struct UX_HOST_CLASS_COMMAND_STRUCT *));
UINT    ux_host_stack_configuration_interface_get(UX_CONFIGURATION *configuration, UINT interface_index,
                                    UINT alternate_setting_index, UX_INTERFACE **interface);
UINT    ux_host_stack_device_configuration_get(UX_DEVICE *device, UINT configuration_index, UX_CONFIGURATION **configuration);
UINT    ux_host_stack_device_configuration_select(UX_CONFIGURATION *configuration);
UINT    ux_host_stack_device_get(ULONG device_index, UX_DEVICE **device);
UINT    ux_host_stack_endpoint_transfer_abort(UX_ENDPOINT *endpoint);
UINT    ux_host_stack_hcd_register(UCHAR *hcd_name, UINT (*hcd_initialize_function)(struct UX_HCD_STRUCT *), ULONG hcd_param1, ULONG hcd_param2);
UINT    ux_host_stack_initialize(UINT (*ux_system_host_change_function)(ULONG, UX_HOST_CLASS *, VOID *));
UINT    ux_host_stack_interface_endpoint_get(UX_INTERFACE *interface, UINT endpoint_index, UX_ENDPOINT **endpoint);
UINT    ux_host_stack_interface_setting_select(UX_INTERFACE *interface);
UINT    ux_host_stack_transfer_request(UX_TRANSFER *transfer_request);
UINT    ux_host_stack_transfer_request_abort(UX_TRANSFER *transfer_request);
VOID    ux_host_stack_hnp_polling_thread_entry(ULONG id);
UINT    ux_host_stack_role_swap(UX_DEVICE *device);
UINT    ux_host_stack_device_configuration_reset(UX_DEVICE *device);


/* Define USBX Device API prototypes.  */

UINT    ux_dcd_at91_initialize(ULONG dcd_io);
UINT    ux_dcd_isp1181_initialize(ULONG dcd_io, ULONG dcd_irq, ULONG dcd_vbus_address);
UINT    ux_dcd_ml6965_initialize(ULONG dcd_io, ULONG dcd_irq, ULONG dcd_vbus_address);
UINT    ux_dcd_sim_slave_initialize(VOID);
                                        
UINT    ux_device_class_storage_entry(UX_SLAVE_CLASS_COMMAND *command);
VOID    ux_device_class_storage_thread(ULONG);
UINT    ux_device_stack_alternate_setting_get(ULONG interface_value);
UINT    ux_device_stack_alternate_setting_set(ULONG interface_value, ULONG alternate_setting_value);
UINT    ux_device_stack_class_register(UCHAR *class_name,
                                    UINT (*class_entry_function)(struct UX_SLAVE_CLASS_COMMAND_STRUCT *),
                                    ULONG configuration_number,
                                    ULONG interface_number,
                                    VOID *parameter);
UINT    ux_device_stack_class_unregister(UCHAR *class_name,
                                    UINT (*class_entry_function)(struct UX_SLAVE_CLASS_COMMAND_STRUCT *));
UINT    ux_device_stack_configuration_get(VOID);
UINT    ux_device_stack_configuration_set(ULONG configuration_value);
UINT    ux_device_stack_descriptor_send(ULONG descriptor_type, ULONG request_index, ULONG host_length);
UINT    ux_device_stack_disconnect(VOID);
UINT    ux_device_stack_endpoint_stall(UX_SLAVE_ENDPOINT *endpoint);
UINT    ux_device_stack_host_wakeup(VOID);
UINT    ux_device_stack_initialize(UCHAR * device_framework_high_speed, ULONG device_framework_length_high_speed,
                                    UCHAR * device_framework_full_speed, ULONG device_framework_length_full_speed,
                                    UCHAR * string_framework, ULONG string_framework_length,
                                    UCHAR * language_id_framework, ULONG language_id_framework_length,
                                    UINT (*ux_system_slave_change_function)(ULONG));
UINT    ux_device_stack_uninitialize(VOID);
UINT    ux_device_stack_interface_delete(UX_SLAVE_INTERFACE *interface);
UINT    ux_device_stack_interface_get(UINT interface_value);
UINT    ux_device_stack_interface_set(UCHAR * device_framework, ULONG device_framework_length,
                                    ULONG alternate_setting_value);
UINT    ux_device_stack_interface_start(UX_SLAVE_INTERFACE *interface);
UINT    ux_device_stack_transfer_request(UX_SLAVE_TRANSFER *transfer_request, ULONG slave_length, ULONG host_length);
UINT    ux_device_stack_transfer_request_abort(UX_SLAVE_TRANSFER *transfer_request, ULONG completion_code);

/* Include USBX utility and system file.  */

#include "ux_utility.h"
#include "ux_system.h"




/* Determine if a C++ compiler is being used.  If so, complete the standard
   C conditional started above.  */
#ifdef   __cplusplus
        }
#endif


#endif


