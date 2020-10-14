Revision History


USBX generic code version 5.8 Service Pack 6 (SP6).  To install SP5, simply copy files in SP6 into the same
directory of your USBX 5.8 distribution and then rebuild the USBX library as well as the application code.

03/15/2019  USBX Service Pack code version 5.8 SP6 This release includes the following  modifications:

            The following files are modified:

            ux_host_class_hid_descriptor_parse.c            fixed the*request index setting.
            ux_device_class_hid_event_set.c                 added support for HID multiple reports
            ux_device_class_hid_report_set.c                fixed an issue that the function returns incorrect value.
            ux_device_class_rndis.h                         added packet allocation timeout value, added compile-time to 
                                                            ensure max RNDIS response length can fit in control transfer buffer, 


`           The following files are modified to enhance memory boundary check to prevent buffer overflow:
            ux_device_stack_descriptor_send.c               
            ux_pictbridge_dpsclient_object_data_send.c      
            ux_host_class_pima_device_info_get.c 
            ux_host_class_pima_object_get.c 
            ux_host_class_pima_object_info_get.c 
            ux_host_class_pima_object_info_send.c 
            ux_host_class_pima_read.c 
            ux_host_class_pima_thumb_get.c
            ux_device_class_hid.h 
            ux_device_class_hid_event_set.c 
            ux_device_class_hid_report_get.c 
            ux_device_class_pima_device_prop_desc_get.c 
            ux_device_class_pima_response_send.c 
            ux_device_class_rndis_bulkin_thread.c 
            ux_device_class_rndis_bulkout_thread.c 
            ux_device_class_storage_mode_sense.c 
            ux_device_class_storage_thread.c
            ux_pictbridge_dpsclient_object_data_send.c



Copyright(c) 1996-2019 Express Logic, Inc.


Express Logic, Inc.
11423 West Bernardo Court
San Diego, CA  92127

www.expresslogic.com

